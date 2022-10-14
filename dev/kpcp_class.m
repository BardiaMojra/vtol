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
      m.Am = zeros(obj.nObs); m.Gm = zeros(obj.nObs); cnt = 0;
      for k = 1:obj.nTrials % gen dat
        x = sim.ransamp_x();
        %u = sim.ransamp_u(); % const input bias
        for t = 1:obj.nSamps
          %xo = sim.stepX(u); 
          u = sim.ransamp_u();
          xo = sim.get_f(x,u);
          uo = u; % ?
          %disp("xo"); disp(xo)
          %disp("uo"); disp(uo)
          z1 = cat(2,sim.get_z(x),sim.get_v(x,u));
          z2 = cat(2,sim.get_z(xo),sim.get_v(xo,u));
          %disp("z1"); disp(z1)
          %disp("z2"); disp(z2)
          cnt = cnt+1;
          m.Am = m.Am + obj.OuterProduct(z2,z1)/cnt;
          m.Gm = m.Gm + obj.OuterProduct(z1,z1)/cnt;
          %disp("m.A"); disp(m.A)
          %disp("m.G"); disp(m.G)
          %if obj.en_log_train_dat
          %  train_log(name="training data")
          %end
          x  = xo; u = uo;% ?    % propagate x n u
        end
      end
      m.K = m.Am * pinv(m.Gm);
      m.Ac = m.K(1:obj.nxObs,1:obj.nxObs);
      m.Bc = m.K(1:obj.nxObs,obj.nxObs:end);
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
        disp("zt"); disp(zt);



        
        zot = cat(zot,zt);
        zt = dot(m.Ac,zt) + dot(m.Bc, sim.get_v(zt(1:obj.nx), u(t)));
        disp("zt"); disp(zt);
        disp("zot"); disp(zot);
      end 
      rho = np.zeros(size(zt));
      for t = T:1
        Bdz = dot(m.Bc, sim.get_dvdz(zot(t,1:obj.nx), u(t)));
        m.rho = sim.get_ldx(zot(t)) + dot((m.Ac+Bdz)', rho);
        Beff = dot(B, sim.get_dvdu(zot(t), u(t)));
        %u[t] = np.clip(-Rinv.dot(Beff.T.dot(rho)), -1., 1.)
        du = dot(Beff',rho) + 2.0 * dot(obj.R,u(t));
        u(t) = obj.clip(u(t)-0.1*du,-1,1);
        disp("m.rho"); disp(m.rho);
        disp("du"); disp(du);
        disp("u(t)"); disp(u(t));
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
        u = obj.update_u(sim,m,xt,u);
        u1 = u(1);
        disp("u"); dip(u);
        disp("u1"); dip(u1);
        xtpo = sim.get_f(xt,u1);
        disp("xtpo"); dip(xtpo);
        z1 = cat(sim.get_z(xt), sim.get_v(xt,u1));
        z2 = cat(sim.get_z(xtpo), sim.get_v(xtpo,u1));
        m.Am = m.Am + obj.OuterProduct(z2,z1)/cnt;
        m.Gm = m.Gm + obj.OuterProduct(z1,z1)/cnt;
        m.K = m.Ac * pinv(m.Gm);
        m.Ac = m.Kc(1:obj.nxObs,1:obj.nxObs);
        m.Bc = m.Kc(1:obj.nxObs,obj.nxObs:end);
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
 



  
  