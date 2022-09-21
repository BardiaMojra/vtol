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
    %% koopman
    nxObs % num of x observables  
    nuObs % num of u observables 
    nObs % num of x+u observables 
  end
  methods % constructor
    function obj = koopman_class(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
    end 
  end % methods % constructor
  methods (Access = public) 
    
    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.dt          = cfg.sim.dt;  
      %obj.nVars       = cfg.sim.nVars;  
      %obj.nSamps      = cfg.sim.nSamps;       
      %obj.st_frame    = cfg.sim.st_frame;   
      %obj.end_frame   = cfg.sim.end_frame; 
      obj.nTrials     = cfg.sim.nTrials;
      obj.nSamps      = cfg.sim.nSamps;
      obj.sim         = cfg.sim;
      obj.init();
      obj.get_model(cfg.sim);
    end

    function m = get_model(obj, sim)
      m = model_class(cons = "none", ...
                      mthd = "koopman", ...
                      label = "test");
      M = obj.nTrials * obj.nSamps;      
      A = zeros(obj.nObs);
      G = zeros(obj.nObs);
      
      for k = 1:nTrials % gen dat
        x = sim.reset();
        u = sim.ransamp_u();
        for t = 1:obj.nSamps
          xo = sim.step(u);
          uo = u;
          A = A + obj.OuterProduct(obj.z(xo,uo), obj.z(xo,uo));
          G = G + obj.OuterProduct(obj.z(x ,u ), obj.z(x ,u ));
          x = xo; u = uo; % propagate x n u
        end
      end
      m.datA  = A / M;
      m.datG  = G / M;
      m.ko    = dot(A,pinv(G));
      m.cko   = logm(m.kp_opt)/sim.dt;
      m.A     = ckp_opt(1:obj.nxObs,1:obj.nxObs);
      m.B     = ckp_opt(1:obj.nxObs,obj.nxObs:end);
    end % get_model()

    function C = OuterProduct(A, B)  % version 5
      C = reshape(A(:) * B(:).', [size(A), size(B)]);
    end

    function get_optCont(~, m)
      m.Q     = diag([1.0, 1.0, 0., 0.]);
      m.R     = diag([1.0]) * 1e-2;
      m.P     = care(m.A, m.B, m.Q, m.R);
      m.Klqr  = m.R\(m.B'*m.P);
    end % get_KO_optCont()
  
    function trajectory = run_cont(obj,m,sim)
      x = sim.reset();
      u = sim.ransamp_u();
      ztar = obj.get_z(0.*x, u);
      ztar = ztar(1:obj.nxObs);
      nt = 500;%  simulation time
      trajectory = zeros(nt, sim.nx);
      for t = 1:nt
        zest = obj.get_z(x,u);
        zest = zest(1:obj.nxObs);
        u = - m.Klqr * (zest-ztar);
        x = sim.step(u);
        trajectory(t,:) = x;
      end
    end
      
    function z = get_z(~,x,u) % this is the basis function 
      z = [x(1), x(2), x(1)^2, (x(1)^2)*x(2), u(1)];
    end % get_lifted_rep()
  end 
  methods  (Access = private)
    function init(obj)
    end
    
    %function load_dat(obj, dat)
    %end


   

  end % private methods
end
 



  
  