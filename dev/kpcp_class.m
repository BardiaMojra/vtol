classdef kpcp_class < matlab.System 
  properties
    %% class
    cName       = "kpcp_class" % 
    desc        = "koopman cart-pendulum input controller class"
    credit      = ""
    %% koopman
    nxObs = 7 % num of x observables  
    nuObs = 2 % num of u observables
    xi   = [3.14, 0., 0., 0.] %sim.ransamp_x();
    ui   = [.1, .1] %u = sim.ransamp_u();
    Q     = diag([10, .2, 0, 0.05, 0, 0, 0])
    Qf    = diag([20., 0.2, 0., 0., 0., 0.,0.])
    R     = diag([0.01])
    %% cfg (argin)
    toutDir
    dat 
    nSamps
    nTrials
    nx
    nu
    eps
    hz
    xband
    uband
    sat  
    % private
    nObs % num of x+u observables 
  end
  methods % constructor
    function obj = kpcp_class(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
    end 
  end % methods % constructor
  methods (Access = public) 
    
    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.nTrials     = cfg.sim.nTrials;
      obj.nSamps      = cfg.sim.nSamps;
      obj.nx          = cfg.sim.nx;
      obj.nu          = cfg.sim.nu;
      obj.eps         = cfg.sim.eps;
      obj.hz          = cfg.sim.hz;
      obj.xband       = cfg.sim.xband;
      obj.uband       = cfg.sim.uband;
      obj.sat         = cfg.sim.sat;
      obj.nObs        = obj.nxObs + obj.nuObs;
      %obj.init();
      %obj.train(cfg.sim);
    end


    %% gen funcs   
    function m = get_optCont(obj,m)
      m.Q     = obj.Q;
      m.R     = obj.R;
      m.P     = care(m.A, m.B, m.Q, m.R); % Ricatti solution 
      m.Klqr  = m.R\(m.B'*m.P);
    end % get_optCont()

    function m = train(obj,sim)
      %if obj.en_log_train_dat
      %  train_log = obj.dlgr.new_log(name="training data");
      %end
      m = model_class(cons = "none", mthd = "koopman", label = "test");
      A = zeros(obj.nObs); G = zeros(obj.nObs); cnt = 0;
      for k = 1:obj.nTrials % gen dat
        x = sim.ransamp_x();
        %u = sim.ransamp_u(); % const input bias
        for t = 1:obj.nSamps
          %xo = sim.stepX(u); 
          u = sim.ransamp_u();
          xo = sim.get_f(x,u);
          uo = u; % ?
          z1 = cat(2,sim.get_z(x),sim.get_v(x,u));
          z2 = cat(2,sim.get_z(xo),sim.get_v(xo,u));
          A = A + obj.OuterProduct(z2,z1)/cnt;
          G = G + obj.OuterProduct(z1,z1)/cnt;
          %if obj.en_log_train_dat
          %  train_log(name="training data")
          %end
          x  = xo; u = uo;% ?    % propagate x n u
        end
      end
      K = A * pinv(G);
      A = K(1:obj.nxObs,1:obj.nxObs);
      B = K(1:obj.nxObs,obj.nxObs:end);
      m.G = G;
    end % train()

    function C = OuterProduct(~,A,B) % version 5
      C = A(:)*B(:).';
    end

    function u = update_u(obj,sim,m,xt,u)
      T = round(1.5*obj.hz);
      zt = sim.get_z(xt);
      zot = [];
      for t = 1:T
        zt = sim.get_z(zt(1:obj.nx));
        zot.append(zt);
        zt = dot(A,zt) + dot(B, sim.get_v(zt(1:obj.nx), u(t)));
      end 
      rho = np.zeros(size(zt));
      for t = T:1
        Bdz = dot(B, sim.get_dvdz(zot(t,1:obj.nx), u(t)));
        rho = sim.get_ldx(zot(t)) + dot((A+Bdz)', rho);
        Beff = dot(B, sim.get_dvdu(zot(t), u(t)));
        %u[t] = np.clip(-Rinv.dot(Beff.T.dot(rho)), -1., 1.)
        du = dot(Beff',rho) + 2.0 * dot(obj.R,u(t));
        u(t) = obj.clip(u(t)-0.1*du,-1,1);
      end 
    end 

    function a = clip(a,amin,amax) % clip arr
      a = min(a,amax); a = max(a,amin); 
    end
    
    function traj = run_cont(obj,sim,m,xt,u)
      traj = xt; % out = cat(1,xt,u); 
      for t = 1:round(40*obj.hz)
        u(1:end-1) = u(2);
        u(end) = zeros(size(u(end))); %% ---  ??
        u = obj.update_u(xt,u,m.A,m.B);
        u1 = u(1);
        xtpo = sim.get_f(xt,u1);
        z1 = cat(sim.get_z(xt), sim.get_v(xt,u1));
        z2 = cat(sim.get_z(xtpo), sim.get_v(xtpo,u1));
        m.A = m.A + obj.OuterProduct(z2,z1)/cnt;
        m.G = m.G + obj.OuterProduct(z1,z1)/cnt;
        m.K = m.A * pinv(m.G);
        m.A = m.K(1:obj.nxObs,1:obj.nxObs);
        m.B = m.K(1:obj.nxObs,obj.nxObs:end);
        xt = xtpo;
        cat(2,traj,xt);
      end 
    end 
      

  end 

  methods  (Access = private)
    %function init(obj)
    %end

  end % private methods
end
 



  
  