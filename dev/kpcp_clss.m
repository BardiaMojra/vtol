classdef kpcp_clss < matlab.System 
  properties
    %% class
    cName       = "kpcp" % 
    desc        = ["koopman cart-pendulum"]
    credit      = ""
    %% cfg (argin)
    toutDir
    %% dat (argin)
    dat % dat 
    sim
    %mod
    dt
    nSamps
    nTrials
    %% koopman
    nxObs = 7 % num of x observables  
    nuObs = 2 % num of u observables
    x_o   = [1, 1] %sim.ransamp_x();
    u_o   = [.1, .1] %u = sim.ransamp_u();
    hz    = 60.0
    sat   = 5.0
    Q     = diag([10, .2, 0, 0.05, 0, 0, 0])
    Qf    = diag([20., 0.2, 0., 0., 0., 0.,0.])
    R     = diag([0.01])

    %
    nObs % num of x+u observables 
  end
  methods % constructor
    function obj = kpcp_clss(varargin) 
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
      %obj.hz           = cfg.sim.hz;
      obj.nObs        = obj.nxObs + obj.nuObs;
      %obj.init();
      obj.get_model(cfg.sim);
    end

    %% lift mappings and respetive derivatives  
    function z = get_z(~,x) % ----------------------->> state lift basis: x->z
      %z = [x(1), x(2), x(1)^2, (x(1)^2)*x(2), u(1)]; % Van Der Pol 
      z = [x(1), x(2), x(3), x(4), sin(x(1)), cos(x(1)), 1.]; % cart-pend
    end % get_z()
    
    function v = get_v(~,x,u) % ----------------->> input lift basis: (x,u)->v
      % note: state (x, not z) and input (u) are used to lift the input space 
      % so that the lifted input space can be differentiated wrt input (u).
      % This allows formulating differentiable control solution in lifted space.
      v = [u(1), cos(x(1))*u(1)]; % cart-pend
      % assert(isequal(obj.nuObs,size(v,1)), ...
      % "[kpcp.get_v()]->> basis do not match lifted input size");
    end % get_v()
    
    function dvdu = get_dvdu(~,x,u)
      dvdu = [1.0, cos(x(1))]';
    end 

    function dvdz = get_dvdz(~,x,u)
      dvdz = zeros(obj.nuObs,obj.nxObs);
      dvdz(:,1) = [0., -sin(x(1)) * u(1)];
    end 

    %% lifted space losses 
    function l = get_l(obj,z) % ------------------>> l(z,u): running cost of z
      z(1) = deg2rad(z(1));
      l = dot(z, dot(obj.Q, z));
    end

    function ldz = get_ldz(obj,z) % ----------->> ldz(z,u): running cost of dz
      z(1) = deg2rad(z(1));
      ldz = 2 * dot(obj.Q, z);
    end

    function m = get_m(obj,z) % ------------------->> m(z): terminal cost of z
      z(1) = deg2rad(z(1));
      m = dot(z, dot(obj.Qf, z));
    end

    function mdz = get_mdz(obj,z) % ------------>> mdz(z): terminal cost of dz
      z(1) = deg2rad(z(1));
      mdz = 2 * dot(obj.Qf, z);
    end     
      

    %% gen funcs   
    function m = get_optCont(obj,m)
      m.Q     = obj.Q;
      m.R     = obj.R;
      m.P     = care(m.A, m.B, m.Q, m.R); % Ricatti solution 
      m.Klqr  = m.R\(m.B'*m.P);
    end % get_optCont()

    function mod = get_mod(obj,sim)
      mod = model_class(cons = "none", mthd = "koopman", label = "test");
      A = zeros(obj.nObs); G = zeros(obj.nObs);
      for k = 1:obj.nTrials % gen dat
        x = sim.ransamp_x();
        %u = sim.ransamp_u(); % const input bias
        for t = 1:obj.nSamps
          %xo = sim.stepX(u); 
          u = sim.ransamp_u();
          xo = sim.f(x,u);
          uo = u; 
          z1 = cat(1,obj.get_z(x),obj.get_v(x,u));
          z2 = cat(1,obj.get_z(xo),obj.get_v(xo,u));
          A = A + obj.OuterProduct(z2,z1)/k;
          G = G + obj.OuterProduct(z1,z1)/k;
          x  = xo; u = uo; % propagate x n u
        end
      end
      mod.K = dot(A, pinv(G));
      mod.A = mod.K(1:obj.nxObs,1:obj.nxObs);
      mod.B = mod.K(1:obj.nxObs,obj.nxObs:end);
    end % get_mod()

    function C = OuterProduct(~,A,B) % version 5
      C = A(:)*B(:).';
    end

    function update_u(obj,x,u,A,B)
      T = int(1.5*obj.hz);
      u = zeros(T,1);
      zt = obj.get_z(x);
      zot = [];
      for t in range(T):
        zt = z(zt[:state_dim])
        zot.append(zt.copy())
        zt = np.dot(A, zt) + np.dot(B, v(zt[:state_dim], u[t]))
      end 
      rho = np.zeros_like(zt)
      for t =1:reversed(range(T))
        Bdz = np.dot(B, dvdz(zot[t][:state_dim], u[t]))
        rho = ldx(zot[t].copy()) + np.dot((A+Bdz).T, rho)
        Beff = np.dot(B, dvdu(zot[t], u[t]))
        %u[t] = np.clip(-Rinv.dot(Beff.T.dot(rho)), -1., 1.)
        du = Beff.T.dot(rho) + 2.0 * R.dot(u[t])
        u[t] = np.clip(u[t] - 0.1 * du, -1, 1)
      end 
    end 
    
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
 



  
  