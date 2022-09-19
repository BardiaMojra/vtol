classdef koopman_class < matlab.System 
  properties
    %% class
    cName       = "koopman" % 
    desc        = [""]
    credit      = ""
    %% cfg (argin)
    toutDir
    %% dat (argin)
    dat % dat 
    dt
    nVars % x and dx from raw data
    nSamps
    st_frame
    end_frame
    %% dat n state 
    nss % x state vars (dont include dx)
    x_cols
    xd_cols
    x % states
    xd % state derivative 
    ndat % dat normalized 
    nTrain % num training samps
    tspan
    X % state in ss 
    Y % state est 
    %% piDMD methods (const)
    constrains   = [ ...
      "exact", "exactSVDS", ...
      "orthogonal", ...
      "uppertriangular", "lowertriangular" , ... % 
      "diagonal", "diagonalpinv", "diagonaltls", "symtridiagonal", ... 
      "circulant", "circulantTLS", "circulantunitary", "circulantsymmetric","circulantskewsymmetric", ...
      "BCCB", "BCCBtls", "BCCBskewsymmetric", "BCCBunitary", "hankel", "toeplitz", ...
      "symmetric", "skewsymmetric"]
  end
  methods % constructor
    
    function obj = piDMD_class(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
    end 

  end % methods % constructor
  methods (Access = public) 
    
    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.dt          = cfg.dat.dt;  
      obj.nVars       = cfg.dat.nVars;  
      obj.nSamps      = cfg.dat.nSamps;       
      obj.st_frame    = cfg.dat.st_frame;   
      obj.end_frame   = cfg.dat.end_frame; 

      obj.init();
      obj.load_dat(cfg.dat.dat);
    end

    function m = get_model(obj, X, Y, cons, label, varargin)
      m = model_class(cons = cons, ...
                      mthd = "piDMD", ...
                      label = label);
      [nx, nt] = size(X); 
      if strcmp(m.cons,'exact') || strcmp(m.cons,'exactSVDS')
        if nargin>5
          m.r = varargin{1};
        else
          m.r = min(nx,nt);
        end
        if strcmp(cons,'exact')
          [m.Ux,m.Sx,m.Vx] = svd(X,0);
          m.Ux = m.Ux(:,1:m.r); m.Sx = m.Sx(1:m.r,1:m.r); m.Vx = m.Vx(:,1:m.r);
        elseif strcmp(cons,'exactSVDS')
          [m.Ux,m.Sx,m.Vx] = svds(X,m.r);
        end
        m.Atilde = (m.Ux'*Y)*m.Vx*pinv(m.Sx);
        m.A = @(v) m.Ux*(m.Atilde*(m.Ux'*v));
        [m.eVecs, m.eVals] = eig(m.Atilde);
        m.eVals = diag(m.eVals); 
        m.eVecs = Y*m.Vx*pinv(m.Sx)*m.eVecs./m.eVals.';
      elseif strcmp(m.cons,'orthogonal')
        if nargin>5
          m.r = varargin{1}; 
        else 
          m.r = min(nx,nt);
        end
        [m.Ux,~,~] = svd(X,0); m.Ux = m.Ux(:,1:m.r);
        m.Yproj = m.Ux'*Y; m.Xproj = m.Ux'*X; % Project X and Y onto principal components
        [m.Uyx, ~, m.Vyx] = svd(m.Yproj*m.Xproj',0);
        m.Aproj = m.Uyx*m.Vyx';    
        m.A = @(x) m.Ux*(m.Aproj*(m.Ux'*x));
        [m.eVecs, m.eVals] = eig(m.Aproj);
      elseif strcmp(m.cons,'uppertriangular')
        [m.R,m.Q] = obj.rq(X); % Q*Q' = I
        m.Ut = triu(Y*m.Q');
        m.A = m.Ut/m.R;
      elseif strcmp(m.cons,'lowertriangular')  
        m.A = rot90(obj.get_model(flipud(X),flipud(Y),'uppertriangular').A,2);
% The codes allows for matrices of variable banded width. The fourth input,
% a 2xn matrix called d, specifies the upper and lower bounds of the
% indices of the non-zero elements. The first column corresponds to the width of
% the band below the diagonal and the second column is the width of the
% band above. For example, a diagonal matrix would have d = ones(nx,2) and 
% a tridiagonal matrix would have d = [2 2]+zeros(nx,2). If you only specify
% d as a scalar then the algorithm converts the input to obtain a banded 
% diagonal matrix of width d. 
      elseif startsWith(m.cons,'diagonal') 
        if nargin>5
          m.d = varargin{1}; % arrange d into an nx-by-2 matrix
          if numel(m.d) == 1
            m.d = m.d*ones(nx,2);
          elseif numel(m.d) == nx
            m.d = repmat(m.d,[1,2]);
          elseif any(size(m.d)~=[nx,2])
            error('Diagonal number is not in an allowable format.')
          end
        else 
          m.d = ones(nx,2); % default is for a diagonal matrix
        end
        % Allocate cells to build sparse matrix
        Icell = cell(1,nx); Jcell = cell(1,nx); Rcell = cell(1,nx);
        for j = 1:nx
          l1 = max(j-(m.d(j,1)-1),1); l2 = min(j+(m.d(j,2)-1),nx);
          C = X(l1:l2,:); b = Y(j,:); % preparing to solve min||Cx-b|| along each row
          if strcmp(m.cons,'diagonal')
            sol = b/C;
          elseif strcmp(m.cons,'diagonalpinv')
            sol = b*pinv(C);
          elseif strcmp(m.cons,'diagonaltls')
            sol = obj.tls(C.',b.').';
          end
          Icell{j} = j*ones(1,1+l2-l1); Jcell{j} = l1:l2; Rcell{j} = sol;
        end
        Imat = cell2mat(Icell); Jmat = cell2mat(Jcell); Rmat = cell2mat(Rcell);
        m.Asparse = sparse(Imat,Jmat,Rmat,nx,nx);
        m.A = @(v) m.Asparse*v;
        [m.eVecs, m.eVals] = eigs(m.Asparse,nx);
      elseif strcmp(m.cons,'symmetric') || strcmp(m.cons,'skewsymmetric')
        [m.Ux,m.S,m.V] = svd(X,0);
        C = m.Ux'*Y*m.V;
        C1 = C;
        if nargin>5; m.r = varargin{1}; else; m.r = rank(X); end
        m.Ux = m.Ux(:,1:m.r);
        Yf = zeros(m.r);
        if strcmp(m.cons,'symmetric') 
          for i = 1:m.r
            Yf(i,i) = real(C1(i,i))/m.S(i,i);
            for j = i+1:m.r
              Yf(i,j) = (m.S(i,i)*conj(C1(j,i)) + m.S(j,j)*C1(i,j)) / (m.S(i,i)^2 + m.S(j,j)^2);
            end
          end
          Yf = Yf + Yf' - diag(diag(real(Yf)));
        elseif strcmp(m.cons,'skewsymmetric')
          for i = 1:m.r
            Yf(i,i) = 1i*imag(C1(i,i))/m.S(i,i);
            for j = i+1:nx
              Yf(i,j) = (-m.S(i,i)*conj(C1(j,i)) + m.S(j,j)*(C1(i,j))) / (m.S(i,i)^2 + m.S(j,j)^2);
            end
          end
          Yf = Yf - Yf' - 1i*diag(diag(imag(Yf)));
        end

        m.A = @(v) m.Ux*Yf*(m.Ux'*v);
        m.YF = Yf;
        [m.eVecs,m.eVals] = eig(Yf);
        m.eVals = diag(m.eVals);
        m.eVecs = m.Ux*m.eVecs;
      elseif strcmp(m.cons,'toeplitz') || strcmp(m.cons,'hankel')
        if  strcmp(m.cons,'toeplitz'); J = eye(nx); 
        elseif strcmp(m.cons,'hankel'); J = fliplr(eye(nx)); end
        Am = fft([eye(nx) zeros(nx)].',[],1)'/sqrt(2*nx); % Define the left matrix
        B = fft([(J*X)' zeros(nt,nx)].',[],1)'/sqrt(2*nx); % Define the right matrix
        BtB = B'*B; 
        AAt = ifft(fft([eye(nx) zeros(nx); zeros(nx,2*nx)]).').'; % Fast computation of A*A'
        y = diag(Am'*conj(Y)*B)'; % Construct the RHS of the linear system
        L = (AAt.*BtB.')'; % Construct the matrix for the linear system
        m.d = [y(1:end-1)/L(1:end-1,1:end-1) 0]; % Solve the linear system
        newA = ifft(fft(diag(m.d)).').'; % Convert the eigenvalues into the circulant matrix
        m.A = newA(1:nx,1:nx)*J; % Extract the Toeplitz matrix from the circulant matrix
      elseif startsWith(m.cons,'circulant')
        fX = fft(X); fY = fft(conj(Y));
        m.d = zeros(nx,1);
        if endsWith(cons,'TLS') % Solve in the total least squares sense     
          for j = 1:nx
            m.d(j) = obj.tls(fX(j,:)',fY(j,:)');
          end
        elseif ~endsWith(m.cons,'TLS') % Solve the other cases
          m.d = diag(fX*fY')./vecnorm(fX,2,2).^2;
          if endsWith(m.cons,'unitary'); m.d = exp(1i*angle(m.d));
          elseif endsWith(m.cons,'symmetric'); m.d = real(m.d);
          elseif endsWith(m.cons,'skewsymmetric'); m.d = 1i*imag(m.d);
          end
        end
        m.eVals = m.d; % These are the eigenvalues
        m.eVecs = fft(eye(nx)); % These are the eigenvectors
        if nargin>5
          m.r = varargin{1}; % Rank constraint
          res = diag(abs(fX*fY'))./vecnorm(fX')'; % Identify least important eigenvalues
          [~,idx] = mink(res,nx-m.r); % Remove least important eigenvalues
          m.d(idx) = 0; m.eVals(idx) = []; m.eVecs(:,idx) = [];
        end
        m.A = @(v) fft(m.d.*ifft(v)); % Reconstruct the operator in terms of FFTs
      elseif strcmp(m.cons,'BCCB') || strcmp(m.cons,'BCCBtls') || ...
        strcmp(m.cons,'BCCBskewsymmetric') || strcmp(m.cons,'BCCBunitary')
        if isempty(varargin); error('Need to specify size of blocks.'); end
        m.s = varargin{1}; m.p = prod(m.s);
        % Equivalent to applying the block-DFT matrix F 
        % defined by F = kron(dftmtx(M),dftmtx(N)) to the matrix X 
        aF =  @(x) reshape(fft2(reshape(x,[m.s,size(x,2)])),[m.p,size(x,2)])/sqrt(m.p);
        %aF =  @(x) x*kron(dftmtx(s(1)),dftmtx(s(2)));
        aFt = @(x) conj(aF(conj(x)));
        fX = aF(conj(X)); fY = aF(conj(Y));
        m.d = zeros(m.p,1);
        if strcmp(m.cons,'BCCB') 
          for j = 1:m.p; m.d(j) = conj(fX(j,:)*fY(j,:)')/norm(fX(j,:)').^2; end
          elseif strcmp(cons,'BCCBtls')
          for j = 1:m.p; m.d(j) = tls(fX(j,:)',fY(j,:)')'; end
          elseif strcmp(cons,'BCCBskewsymmetric')
          for j = 1:m.p; m.d(j) = 1i*imag(fY(j,:)/fX(j,:)); end
          elseif strcmp(cons,'BCCBsymmetric')
          for j = 1:m.p; m.d(j) = real(fY(j,:)/fX(j,:)); end
          elseif strcmp(cons,'BCCBunitary')
          for j = 1:m.p; m.d(j) = exp(1i*angle(fY(j,:)/fX(j,:))); end
        end
        % Returns a function handle that applies A
        if nargin>6
          m.r = varargin{2};
          res = diag(abs(fX*fY'))./vecnorm(fX')';
          [~,idx] = mink(res,nx-r);
          m.d(idx) = 0;
        end
        m.A = @(x) aF((conj(m.d).*aFt(x)));
        m.eVals = m.d; % Eigenvalues are given by d
      elseif strcmp(m.cons,'BC') || strcmp(m.cons,'BCtri') || strcmp(m.cons,'BCtls')
        m.s = varargin{1}; m.p = prod(m.s);
        m.M = m.s(2); m.N = m.s(1);
        if isempty(m.s); error('Need to specify size of blocks.'); end
        % Equivalent to applying the block-DFT matrix F 
        % defined by F = kron(dftmtx(M),eye(N)) to the 
        % matrix X
        aF  =  @(x) reshape(fft(reshape(x,[m.s,size(x,2)]),[],2) ,[m.p,size(x,2)])/sqrt(m.M);
        aFt =  @(x) conj(aF(conj(x)));
        fX = aF(X); fY = aF(Y);
        m.d = cell(m.M,1);
        for j = 1:m.M
          ls = (j-1)*m.N + (1:m.N);
          if strcmp(m.cons,'BC')
            m.d{j} = fY(ls,:)/fX(ls,:);
          elseif strcmp(m.cons,'BCtri')
            m.d{j} = obj.get_model(fX(ls,:),fY(ls,:),'diagonal',2);
          elseif strcmp(m.cons,'BCtls')
            m.d{j} = obj.tls(fX(ls,:)',fY(ls,:)')';
          end
        end 
        BD = blkdiag(m.d{:});
        m.A = @(v) aFt(BD*aF(v));           
      elseif strcmp(m.cons,'symtridiagonal')
        T1e = vecnorm(X,2,2).^2; % Compute the entries of the first block
        T1 = spdiags(T1e,0,nx,nx); % Form the leading block
        T2e = dot(X(2:end,:),X(1:end-1,:),2); % Compute the entries of the second block
        T2 = spdiags([T2e T2e],-1:0,nx,nx-1); % Form the second and third blocks
        T3e = [0; dot(X(3:end,:),X(1:end-2,:),2)]; % Compute the entries of the final block
        T3 = spdiags(T1e(1:end-1) + T1e(2:end),0,nx-1,nx-1) ...
             + spdiags(T3e,1,nx-1,nx-1) + spdiags(T3e,1,nx-1,nx-1)'; % Form the final block
        m.T = [T1 T2; T2' T3]; % Form the block tridiagonal matrix
        m.d = [dot(X,Y,2); dot(X(1:end-1,:),Y(2:end,:),2) + dot(X(2:end,:),Y(1:end-1,:),2)]; % Compute the RHS vector
        c = real(m.T)\real(m.d); % Take real parts then solve linear system
        m.A = spdiags(c(1:nx),0,nx,nx) + spdiags([0;c(nx+1:end)],1,nx,nx) + ...
                spdiags([c(nx+1:end); 0],-1,nx,nx); % Form the solution matrix
      else
        error('The selected method doesn''t exist.');
      end 
      obj.get_rec(m); % get data reconstruction
      m.get_eigModel();
      m.sav(); 
    end % get_model()

    function get_rec(obj, m)
      m.rec = zeros(obj.nVars, obj.nSamps); % reconstruct dat
      m.rec(:,1) = obj.dat(:,1);       
      for j = 2:obj.nSamps
        m.rec(:,j) = m.A(m.rec(:,j-1));
      end
    end % get_rec()
  
  end 
  methods  (Access = private)
    function init(obj)
      obj.nss       = obj.nVars/2;
      obj.nTrain    = obj.nSamps - 1; 
      obj.x_cols    = 1:obj.nss; 
      obj.xd_cols   = obj.nss+1:obj.nVars; 
      obj.tspan     = obj.dt*obj.nSamps;
    end
    
    function load_dat(obj, dat)
      assert(isequal(mod(size(dat,2),2),0), ...
        "-->>> odd num of state vars: %d", size(dat,2));
      obj.x       = dat(:,obj.x_cols); % state vars 
      obj.xd      = dat(:,obj.xd_cols); % state vars time derivative (vel)
      obj.dat     = [obj.x'; obj.xd']; % reorganize data in state space (ss) formulation 
      obj.ndat    = obj.dat + 1e-1*std(obj.dat,[],2); % norm dat
      obj.X       = obj.dat(:,1:obj.nTrain);
      obj.Y       = obj.dat(:,2:obj.nTrain+1);
    end

    function trajPlot(~,j) % Nice plot of trajectories
      yticks([-pi/4,0,pi/4]); yticklabels([{"$-\pi/4$"},{"0"},{"$\pi/4$"}])
      set(gca,"TickLabelInterpreter","Latex","FontSize",20);grid on
      ylim([-1,1])
      ylabel(j,"Interpreter","latex","FontSize",20)
    end

    function [R,Q,varargout] = rq(~,A,varargin) % Performs RQ decomposition
      n = size(A,1);
      if nargout<3
        [Q,R] = qr(flipud(A)',0);
      else
        [Q,R,P1] = qr(flipud(A)',0);
        P(n+1-P1) = n:-1:1; % arrange permutation in right way
        varargout{1} = P;
      end
      R = rot90(R',2);
      Q = flipud(Q');
      [n,m] = size(A);
      if n>m
        R = [zeros(n,n-m), R];
        Q = [zeros(n-m,m); Q];
      end  
    end % rq()
      
    function [Xhat] = tls(obj,A,B,varargin)
      n = size(A,2);
      if size(A,1)~=size(B,1); error('Matrices are not conformant.'); end
      R1 = [A B];
      [~,~,V] = svd(R1,0);
      r = size(A,2);
      R = obj.rq(V(:,r+1:end));Gamma = R(n+1:end,n-r+1:end);
      Z = R(1:n,n-r+1:end);
      Xhat = -Z/Gamma;
    end % tls

    function c = redblue(~,m,varargin)
      %REDBLUE    Shades of red and blue color map
      %  REDBLUE(M), is an M-by-3 matrix that defines a colormap.
      %  The colors begin with bright blue, range through shades of
      %  blue to white, and then through shades of red to bright red.
      %  REDBLUE, by itself, is the same length as the current figure's
      %  colormap. If no figure exists, MATLAB creates one.
      %  For example, to reset the colormap of the current figure:
      %            colormap(redblue)
      %  See also HSV, GRAY, HOT, BONE, COPPER, PINK, FLAG, 
      %  COLORMAP, RGBPLOT.
      %  Adam Auton, 9th October 2009
      if nargin < 1, m = size(get(gcf,'colormap'),1); end
      if (mod(m,2) == 0)
        % From [0 0 1] to [1 1 1], then [1 1 1] to [1 0 0];
        m1 = m*0.5;
        r = (0:m1-1)'/max(m1-1,1);
        g = r;
        r = [r; ones(m1,1)];
        g = [g; flipud(g)];
        b = flipud(r);
      else
        % From [0 0 1] to [1 1 1] to [1 0 0];
        m1 = floor(m*0.5);
        r = (0:m1-1)'/max(m1,1);
        g = r;
        r = [r; ones(m1+1,1)];
        g = [g; 1; flipud(g)];
        b = flipud(r);
      end
      c = [r g b]; 
    end % redblue()

  end % private methods
end
 



  
  