classdef dp_simCls < matlab.System 
  properties
    %% class
    cName       = "dp_simCls" % Physics-informed dynamic mode decompositions
    desc        = ["Double pendulum simulation class"]
    %credit      = ""
    %% cfg (argin)
    toutDir         
    nTrials    % = cfg.sim.nTrials;
    nSamps    %  = cfg.sim.nSamps;    
    %datDir            
    %st_frame      
    %end_frame    
    btype       = "dp" % double pendulum
    %bnum
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
    function obj = dp_simCls(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
    end 
  end % methods 
  methods (Access = public) 
    

% https://www.mathworks.com/help/mpc/ug/code-generation-with-simulink-coder.html

    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.nTrials     = cfg.nTrials;
      obj.nSamps      = cfg.nSamps;
      cfg.sim         = obj; 

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
      %obj.dfdx = jacobian(obj.f, 0); %%
      %obj.dfdu = jacobian(obj.f, 1); %%
      %obj.nx = 2;
      %obj.nu = 2;
      obj.ransamp_x();
    end
    
  end % private methods
end
 



  
  