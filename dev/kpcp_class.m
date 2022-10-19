classdef kpcp_class < matlab.System 
  properties
    %% class
    cName       = "kpcp_class" % 
    desc        = "koopman cart-pendulum input controller class"
    credit      = ""
    plt_train_sav_en     = true % sav dat n fig
    plt_train_shw_en     = false 
    %% koopman
    %% cfg (argin)
    toutDir
    dat 
    nSamps
    nTrials
    nx
    nu
    nz % num of x observables  
    nv % num of u observables
    nzv % num of x_obs (nz) + u_obs (nv)
    xi  
    ui  
    Q   
    Qf  
    R   
    eps
    hz
    xband
    uband
    sat  
    %% plt
    font_style   = "Times"
    txt_FS       = "12pt"
    tab_FS       = "10pt"
    num_format   = "%1.4f"
    fig_U        = "inches"
    fig_FS       = 10
    fig_pos      = [0 0 10 10]
    fig_leg_U    = "inches"
    fig_leg_pos  = [8.5 8.5 .8 .8] % [left bottom width height]
    fig_leg_FS   = 14
    fig_LW       = 1.5
    fig_ylim     = "auto" %= [-2 2] 
    fig_Cr       = ["#A2142F", "#77AC30", "#0072BD", "#c451db", ...
                    "#EDB120", "#4DBEEE", "#D95319", "#77AC30", ...
                    "#FF0000", "#00FF00", "#000000", ...
                    ] % unique per alg
    fig_LS       = ["-", "--", ":", "-.","-", "--", ":", "-.","-", "--", ":", "-."]
    fig_MK       = ["o", "+", "*", ".", ...
                    "x", "s", "d", "^", ...
                    "v", ">", "<", "h"]
    fig_PT       = ["bo:", "gx:", "r+:", "c*:", ...
                    "ms:", "kd:", "b^", ...
                    "g<:"]
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
      obj.nz          = cfg.sim.nz;
      obj.nv          = cfg.sim.nv;
      obj.xi          = cfg.sim.xi;
      obj.ui          = cfg.sim.ui;
      obj.Q           = cfg.sim.Q ;
      obj.Qf          = cfg.sim.Qf;
      obj.R           = cfg.sim.R;
      obj.eps         = cfg.sim.eps;
      obj.hz          = cfg.sim.hz;
      obj.xband       = cfg.sim.xband;
      obj.uband       = cfg.sim.uband;
      obj.sat         = cfg.sim.sat;

      obj.nzv        = obj.nv+obj.nz;
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
      m = model_class(cons = "none", mthd = "koopman", label = "test");
      m.Am = zeros(obj.nzv); m.Gm = zeros(obj.nzv); cnt = 0;
      m.x_hist  = zeros(obj.nTrials*obj.nSamps, obj.nx);
      m.u_hist  = zeros(obj.nTrials*obj.nSamps, obj.nu);
      m.z1_hist = zeros(obj.nTrials*obj.nSamps, obj.nzv);
      m.z2_hist = zeros(obj.nTrials*obj.nSamps, obj.nzv);
      for k = 1:obj.nTrials % gen dat
        x = sim.ransamp_x();
        %u = sim.ransamp_u(); % const input bias
        for t = 1:obj.nSamps 
          u = sim.ransamp_u();
          xo = sim.get_f(x,u);
          uo = u; 
          z1v = cat(1,sim.get_z(x),sim.get_v(x,u));
          z2v = cat(1,sim.get_z(xo),sim.get_v(xo,u));
          cnt = cnt+1;
          m.Am = m.Am + obj.OuterProduct(z2v,z1v)/cnt;
          m.Gm = m.Gm + obj.OuterProduct(z1v,z1v)/cnt;
          x  = xo; u = uo;  % propagate x n u
          m.x_hist(((k-1)*obj.nSamps)+t,:) = x;
          m.u_hist(((k-1)*obj.nSamps)+t,:) = u;
          m.z1_hist(((k-1)*obj.nSamps)+t,:) = z1v;
          m.z2_hist(((k-1)*obj.nSamps)+t,:) = z2v;
        end
      end
      m.K = m.Am * pinv(m.Gm);
      m.Ac = m.K(1:obj.nz,1:obj.nz);
      m.Bc = m.K(1:obj.nz,obj.nz+1:end);
    end % train()

    function C = OuterProduct(~,A,B) % version 5
      C = A(:)*B(:).';
    end

    function u = update_u(obj,sim,m,x,u)
      uHorzn = round(1.5*obj.hz); % move to properties 
      z = sim.get_z(x);
      zo = zeros(uHorzn,size(z,1));
      %disp("z (7,1)"); disp(z);
      %disp("zo (7,1)"); disp(zo);
      for t = 1:uHorzn
        z = sim.get_z(z(1:obj.nx));
        zo(t,:) = z';
        aa = m.Ac*z;
        vv = sim.get_v(z(1:obj.nx),u(t));
        bb = m.Bc * vv;
        z =  aa + bb;
        %disp("Bc (7,2)"); disp(m.Bc); 
        %disp("Ac (7,7)"); disp(m.Ac); 
        %disp("vv (2,1)"); disp(vv); 
        %disp("aa (7,1)"); disp(aa);
        %disp("bb (7,1)"); disp(bb);
        %disp("z (7,1)"); disp(bb);
      end 
      m.rho = zeros(size(z));
      for t = uHorzn:-1:1
        %disp("zo (90,z)"); disp(zo);
        zzoo = zo(t,1:obj.nx);
        %disp("zzoo (4,1)"); disp(zzoo);
        dvdzoo = sim.get_dvdz(zzoo,u(t));
        %disp("dvdzoo (2,7)"); disp(dvdzoo);
        Bdz = m.Bc * dvdzoo;
        %disp("Bdz (7,7)"); disp(Bdz);
        m.rho = sim.get_ldz(zo(t,:)') + (m.Ac+Bdz)'*m.rho;
        %disp("m.rho (7,1)"); disp(m.rho);
        Beff = m.Bc * sim.get_dvdu(zo(t,:),u(t));
        %disp("Beff (7,1)"); disp(Beff);
        %u[t] = np.clip(-Rinv.dot(Beff.T.dot(m.rho)), -1., 1.)
        du = Beff'*m.rho + 2.0 * (obj.R*u(t));
        u(t) = obj.clip(u(t)-0.1*du,-1,1);
        %disp("du (1,1)"); disp(du);
        %disp("u(t) (1,1)"); disp(u(t) );
      end 
    end  % update_u() 

    function a = clip(~,a,amin,amax) % clip arr
      a = min(a,amax); a = max(a,amin); 
    end
    
    function traj = run_cont(obj,sim,m,x,u,nSamps)
      traj = x; % out = cat(1,xt,u); 
      for t = 1:nSamps
        u(1:end-1) = u(2);
        u(end) = zeros(size(u(end))); %% ---  ??
        u = obj.update_u(sim,m,x,u);
        u1 = u(1);

        xp = sim.get_f(x,u1);
        
        z1x = sim.get_z(x);
        vxu = sim.get_v(x,u1);
        z2xp = sim.get_z(xp);
        vxpu = sim.get_v(xp,u1);
        z1 = cat(1,z1x,vxu);
        z2 = cat(1,z2xp,vxpu);

        
        m.Am = m.Am + obj.OuterProduct(z2,z1)/t;
        m.Gm = m.Gm + obj.OuterProduct(z1,z1)/t;
        m.K = m.Am/m.Gm;
        m.Ac = m.K(1:obj.nz,1:obj.nz);
        m.Bc = m.K(1:obj.nz,obj.nz:end);  
        

        disp("x"); disp(x);        
        disp("xp"); disp(xp);
        disp("z1x"); disp(z1x);
        disp("vxu"); disp(vxu);
        disp("z1"); disp(z1);
        disp("z2xp"); disp(z2xp);
        disp("vxpu"); disp(vxpu);
        disp("z2"); disp(z2);
        disp("cnt"); disp(t);
        disp("m.Am"); disp(m.Am);
        disp("m.Gm"); disp(m.Gm);
        disp("m.K "); disp(m.K );
        disp("m.Ac"); disp(m.Ac);
        disp("m.Bc"); disp(m.Bc);
        x = xp;
        cat(1,traj,x);
      end 
    end % run_cont()

    function plt_train_Z2(obj, m)
      figTitle = "Training Data: Lifted State Posterior $Z_{post}$ and Lifted Control Input $U$";
      fileName = "plt_training_Z2";
      varNames = ["$z_{1}= \theta$","$z_{2}=x$","$z_{3}=\dot{\theta}$",...
        "$z_{4}=\dot{x}$", "$z_{5}=sin(\theta)$","$z_{6}=cos(\theta)$","$z_{7}=1$", ...
        "$v_{1}=u_{1}$", "$v_{2}=cos(\theta)*u_{1}$"];
      data = m.z2_hist; % cat(2,m.x_hist,m.u_hist);
      assert(isequal(size(data,2), length(varNames)), ...
        "[kpcp.plt_train_Z2()]->> varNames label and data lengths do not match...\n\n")
      obj.plt_dat(figTitle,fileName,varNames,data);
    end % plt_train_Z2()

    function plt_train_Z1(obj, m)
      figTitle = "Training Data: Lifted State Prior $Z_{prior}$ and Lifted Control Input $U$";
      fileName = "plt_training_Z1";
      varNames = ["$z_{1} = \theta$","$z_{2}= x$","$z_{3}= \dot{\theta}$",...
        "$z_{4}= \dot{x}$", "$z_{5}=sin(\theta)$","$z_{6}=cos(\theta)$","$z_{7}=1$", ...
        "$v_{1}= u_{1}$", "$v_{2}=cos( \theta)*u_{1}$"];
      data = m.z1_hist; % cat(2,m.x_hist,m.u_hist);
      assert(isequal(size(data,2), length(varNames)), ...
        "[kpcp.plt_train_Z1()]->> varNames label and data lengths do not match...\n\n")
      obj.plt_dat(figTitle,fileName,varNames,data);
    end % plt_train_Z1()

    function plt_train_XU(obj, m)
      figTitle = "Training Data: State & Control Input";
      fileName = "plt_training_XU";
      varNames = ["$\theta$","$x$","$\dot{\theta}$","$\dot{x}$","$u$"];
      data = cat(2,m.x_hist,m.u_hist);
      assert(isequal(size(data,2), length(varNames)), ...
        "[kpcp.plt_train_XU()]->> varNames label and data lengths do not match...\n\n")
      obj.plt_dat(figTitle,fileName,varNames,data);
    end % plt_train_XU()
    
    function plt_dat(obj,figTitle,fileName,varNames,dat)
      % keep generic
      t = 1:size(dat,1);
      nVars = size(dat,2);
      IN="Interpreter";LT="latex";MK="Marker";LS="LineStyle";
      FS="fontsize";Cr="Color";LW ="LineWidth";
      fig = figure(); 
      title(figTitle,IN,LT);
      fig.Units   = obj.fig_U; fig.Position = obj.fig_pos; hold on
      for v = 1:nVars
        plot(t,dat(:,v),Cr,obj.fig_Cr(v),LW,obj.fig_LW,LS,obj.fig_LS(v));
      end
      lg          = legend(varNames,IN,LT); 
      lg.Units    = obj.fig_leg_U;
      lg.Position = obj.fig_leg_pos;
      lg.FontSize = obj.fig_leg_FS;
      if obj.plt_train_sav_en
        figname = strcat(obj.toutDir,fileName);
        saveas(fig, figname); % sav as fig file
        saveas(fig, strcat(figname,".png")); % sav as png file
      end
      if ~obj.plt_train_shw_en
        close(fig);
      end
    end % plt_train_XU

  end 

  methods  (Access = private)
    %function init(obj)
    %end

  end % private methods
end
 



  
  