classdef cp_class < matlab.System 
  properties
    %% class
    cName       = "cp" % cart-pend
    desc        = ["Cart Pendulum Model Class"]
    credit      = ""
    %% cfg (argin)
    toutDir         
    nTrials    
    nSamps    
    %datDir            
    %st_frame      
    %end_frame    
    btype       = "cart-pole"
    %bnum
    %% settings
    nx      = 4 % num of state variables 
    nu      = 1 % num of cont. inputs
    eps     = 1.0
    %dt      = 0.01 % todo: add assert for dt and hz
    hz      = 60.0
    xband   = [6.24, 1.0, 2.0, 2.0] % x (state) var range 
    uband   = [1.] % u (input) var range 
    sat     = 5.0
    %% opt
    x
    u
    xdot
  end
  methods 
    function obj = cp_class(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
    end 
  end % methods 
  methods (Access = public) 
    
    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.nTrials     = cfg.nTrials;
      obj.nSamps      = cfg.nSamps;
      cfg.sim         = obj; 
      obj.init();
    end

    function x = ransamp_x(obj) % reset st to rand IC
      obj.x = -(obj.xband/2) + obj.xband*rand(obj.nx,1);
      x = obj.x;
    end 

    function u = ransamp_u(obj) % rand cont. input 
      obj.u = -(obj.uband/2) + obj.uband*rand(obj.nx,1);
      u = obj.u;
    end 

    function xdot = f(obj,x,u)
      xdot = [ x(3), x(4), ...
               9.81*sin(x(1))/1.0 + obj.sat*u(1)*cos(x(1))/1.0 - 0.2*x(3), ...
               obj.sat*u(1) -0.1*x(4) ];
      xdot = x + xdot/obj.hz;
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
 



  
  