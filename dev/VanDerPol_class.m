classdef VanDerPol_class < matlab.System 
  properties
    %% class
    cName       = "VanDerPol" % Physics-informed dynamic mode decompositions
    desc        = [""]
    credit      = ""
    %% cfg (argin)
    toutDir         
    datDir            
    st_frame      
    end_frame    
    btype         
    bnum
    %% settings
    esp   = 1.0
    dt    = 0.01
    stRange = 6
    %% opt
    f   % function 
    nStates
    nActions
    dfdx
    dfdu
    %% 
    dat % dat 
    nVars % x and dx from raw data
    nSamps
  end
  methods 
    function obj = VanDerPol_class(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
    end 
  end % methods 
  methods (Access = public) 
    
    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.dt          = cfg.dt;  
      
      obj.nSamps      = cfg.nSamps;       


      
      obj.init();
    end

    function x = reset(obj) % reset st to rand IC
      obj.x = -(obj.stRange/2) + obj.stRange*rand(obj.nx,1);
      x = obj.x;
    end 

    function u = ransamp_u(obj)
      obj.u = -(obj.stRange/2) + obj.stRange*rand(obj.nx,1);
      u = obj.u;
    end 

    function xdot = f(obj,x,u)
      xdot = [x(2);
             -x(1) + obj.eps * (1-x(1)^2) * x(2)+u(1)];
      obj.xdot = xdot;
    end 

    function [dfdx,dfdu] = get_linearization(obj,x,u)
      dfdx = obj.dfdx(x,u);
      dfdu = obj.dfdu(x,u);
      
    end 
    
    function x = step(obj,u) % RK4 step
      k1 = obj.f(obj.x , u) * obj.dt;
      k2 = obj.f(obj.x + k1/2.0, u) * obj.dt;
      k3 = obj.f(obj.x + k2/2.0, u) * obj.dt;
      k4 = obj.f(obj.x + k3, u) * obj.dt;
      obj.x = obj.x + (k1 + 2 * (k2 + k3) + k4)/6;
      x = obj.x;
    end 
  end 

  methods  (Access = private)
    function init(obj)
      obj.dfdx = jacobian(obj.f, 0); %%
      obj.dfdu = jacobian(obj.f, 1); %%
      obj.num_states = 2
      obj.num_actions = 2
      obj.reset()
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
 



  
  