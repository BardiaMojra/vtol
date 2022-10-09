classdef kp_class < matlab.System 
  properties
    %% class
    cName       = "kp_class" % kp
    desc        = "Koopman operator controller class"
    credit      = ""
    %% cfg (argin)
    toutDir
    %% dat (argin)
    dat % dat 
    dt
    %nVars % x and dx from raw data
    nSamps
    %st_frame
    %end_frame
    nTrials
    sim
    %% koopman
    x_o   = [1, 1] %sim.ransamp_x();
    u_o   = [.1, .1] %u = sim.ransamp_u();
    nxObs = 4 % num of x observables  
    nuObs = 2 % num of u observables 
    Q     = diag([1.0, 1.0, 0., 0.]) % note: no weights on lifted space dims
    R     = diag([1.0])* 1e-2 
    % private
    nObs % num of x+u observables 
  end
  methods % constructor
    function obj = kp_clss(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
    end 
  end % methods % constructor
  methods (Access = public) 
    
    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.dt          = cfg.sim.dt;  
      obj.nTrials     = cfg.sim.nTrials;
      obj.nSamps      = cfg.sim.nSamps;
      obj.sim         = cfg.sim;
      %obj.Q           = cfg.sim.Q;
      %obj.R           = cfg.sim.R;
      %obj.get_z       = cfg.sim.get_z;

      obj.nObs        = obj.nxObs + obj.nuObs;
      %obj.init();
      obj.get_model(cfg.sim);
    end

    function m = get_model(obj, sim)
      m = model_class(cons = "none", ...
                      mthd = "koopman", ...
                      label = "test");
      M = obj.nTrials * obj.nSamps;      
      A = zeros(obj.nObs); G = zeros(obj.nObs);
      for k = 1:obj.nTrials % gen dat
        x = sim.ransamp_x();
        u = sim.ransamp_u();
        for t = 1:obj.nSamps
          xo = sim.stepX(u);
          uo = u;
          zo = obj.get_z(xo,uo);
          z  = obj.get_z(x,u);
          Au = obj.OuterProduct(zo,z);
          A  = A + Au;
          Gu = obj.OuterProduct(z ,z);
          G  = G + Gu;
          x  = xo; u  = uo; % propagate x n u
        end
      end
      A       = A / M;
      G       = G / M;
      m.ko    = A*pinv(G);
      m.cko   = logm(m.ko)/sim.dt;
      m.A     = m.cko(1:obj.nxObs,        1:obj.nxObs);
      m.B     = m.cko(1:obj.nxObs,obj.nxObs:end      );
    end % get_model()

    function z = get_z(~,x,u) % ----------------------------------->> basis func
    % move this to sim or dat class 
      z = [x(1), x(2), x(1)^2, (x(1)^2)*x(2), u(1)]; % Van Der Pol 
    end % get_z()

    function C = OuterProduct(~,A,B) % version 5
      C = A(:)*B(:).';
    end

    function m = get_optCont(obj,m)
      m.Q     = obj.Q;
      m.R     = obj.R;
      m.P     = care(m.A, m.B, m.Q, m.R); % Ricatti solution 
      m.Klqr  = m.R\(m.B'*m.P);
    end % get_optCont()
  
    function trajectory = run_cont(obj,m,sim)
      x = obj.x_o; %sim.ransamp_x();
      u = obj.u_o; %u = sim.ransamp_u();
      ztar = obj.get_z(0.*x, u);
      ztar = ztar(1:obj.nxObs);
      %nt = 1000;%  simulation time
      trajectory = zeros(obj.nSamps, sim.nx*3);
      for t = 1:obj.nSamps
        zest = obj.get_z(x,u);
        zest = zest(1:obj.nxObs);
        u = - m.Klqr * (ztar-zest)';
        x = sim.stepX(u);
        trajectory(t,:) = cat(1,x,zest(1:2)',ztar(1:2)');
      end
    end
      

  end 
  methods  (Access = private)
    %function init(obj)
    %end

  end % private methods
end
 



  
  