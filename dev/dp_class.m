classdef dp_class < matlab.System 
  properties
    %% class
    cName       = "dp_class" % 
    desc        = ["Double pendulum simulation class"]
    %credit      = ""
    %% features 
    en_sav_dat
    en_sav_sim
    %% cfg (argin)
    simDir
    toutDir 
    btype       = "dp" % double pendulum
    %bnum    
    soutDir
    %datDir            
    nTrials     = 5 % num of trials, dat is concat of nTrials
    nSamps      = 200 % disc length of each trial 
    %% settings
    nx      = 2 % num of state variables 
    nu      = 2 % num of cont. inputs
    eps     = 1.0
    dt      = 0.01
    stRange = 6
    uRange = 0.1
    %% opt
    x
    u
    xdot
    %f   % function 
    %dfdx not vars, fpntr
    %dfdu not vars, fpntr
    %% 
    %dat % dat 
    %nVars % same as nx
    %nSamps
  end
  methods 
    function obj = dp_class(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
      obj.check_deps();
    end 
  end % methods 
  methods (Access = public) 
    
    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.simDir      = cfg.simDir;
      %obj.btype       = cfg.btype;
      %obj.nTrials     = cfg.nTrials;
      %obj.nSamps      = cfg.nSamps;
      %cfg.sim         = obj; 

      obj.init();
    end

    function x = ransamp_x(obj) % reset st to rand IC
      obj.x = -(obj.stRange/2) + obj.stRange*rand(obj.nx,1);
      x = obj.x;
    end 

    function u = ransamp_u(obj) % rand cont. input 
      obj.u = -(obj.uRange/2) + obj.uRange*rand(obj.nx,1);
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
    
    function jac = dfdx(obj,x,u)
      jac = jacobian(obj.f(x,u),x);
    end 

    function jac = dfdu(obj,x,u)
      jac = jacobian(obj.f(x,u),u);
    end 

    function x = stepX(obj,u) % RK4 step-------------- ?
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
      obj.set_soutDir();% setup soutDir

    end

    function set_soutDir(obj)
      obj.soutDir = strcat(obj.simDir,"/",obj.btype,'/');
      if not(isfolder(obj.soutDir)) % create soutDir
        disp("[config]->> soutDir does NOT exist: ");
        disp(obj.soutDir);
        mkdir(obj.soutDir);
        disp("[config]->> directory was created!");
      else 
        disp("[config]->> soutDir exists and will be removed: ");
        disp(obj.soutDir);
        rmdir(obj.soutDir, 's');
        mkdir(obj.soutDir);
        disp("[config]->> directory was created!");
      end 
    end % set_soutDir()

    function check_deps(~)
      if ~mpcchecktoolboxinstalled('simulink')
        disp('Simulink is required to run this example.')
        return
      end
      if ~mpcchecktoolboxinstalled('simulinkcoder')
        disp('Simulink Coder is required to run this example.');
        return
      end
    end % check_deps()
    
  end % private methods
end
 



  
  