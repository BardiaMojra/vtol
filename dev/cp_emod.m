classdef cp_emod < matlab.System 
  properties
    %% class
    cName       = "cp_emod" % cart-pend
    desc        = "cart pendulum explicit model class"
    credit      = ""
    %% cfg (argin)
    toutDir         
    nTrials    
    nSamps    
    %datDir            
    %st_frame      
    %end_frame    
    btype       = "cp_emod"
    %bnum
    %% settings
    nx      = 4 % num of state variables 
    nu      = 1 % num of cont. inputs
    nz      = 7
    nv      = 2
    eps     = 1.0
    %dt      = 0.01 % todo: add assert for dt and hz
    hz      = 60.0
    xband   = [6.24, 1.0, 2.0, 2.0] % x (state) var range 
    uband   = [1] % u (input) var range 
    sat     = 5.0
    xi      = [3.14, 0., 0., 0.] %sim.ransamp_x();
    ui      = [.1, .1] %u = sim.ransamp_u();
    Q       = diag([20, .2, 0, 0.05, 0, 0, 0])
    Qf      = diag([20., 0.2, 0., 0., 0., 0.,0.])
    R       = diag([0.001])
    %% opt
    x
    u
    xdot
  end
  methods 
    function obj = cp_emod(varargin) 
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
      x = -(obj.xband/2) + obj.xband*rand(obj.nx,1);
    end 

    function u = ransamp_u(obj) % rand cont. input 
      u = obj.uband*rand(obj.nu,1);
    end 

    function xdot = get_f(obj,x,u)
      xdot3 = 9.81*sin(x(1))/1.0 + obj.sat*u(1)*cos(x(1))/1.0 - 0.2*x(3); 
      xdot4 = obj.sat*u(1)-0.1*x(4);
      xdot = [ x(3), x(4), xdot3, xdot4];
      xdot = x + xdot/obj.hz;
    end 


    %% lift mappings and respetive derivatives  
    function z = get_z(~,x) % ----------------------->> state lift basis: x->z
      %z = [x(1), x(2), x(1)^2, (x(1)^2)*x(2), u(1)]; % Van Der Pol 
      z = [x(1), x(2), x(3), x(4), sin(x(1)), cos(x(1)), 1.]'; % cart-pend
    end % get_z()
    
    function v = get_v(~,x,u) % ----------------->> input lift basis: (x,u)->v
      % note: state (x, not z) and input (u) are used to lift the input space 
      % so that the lifted input space can be differentiated wrt input (u).
      % This allows formulating differentiable control solution in lifted space.
      v = [u(1), cos(x(1))*u(1)]'; % cart-pend
      % assert(isequal(obj.nuObs,size(v,1)), ...
      % "[kpcp.get_v()]->> basis do not match lifted input size");
    end % get_v()
    
    function dvdu = get_dvdu(~,x,u)
      dvdu = [1.0, cos(x(1))]';
    end 

    function dvdz = get_dvdz(obj,x,u)
      dvdz = zeros(obj.nv,obj.nz);
      dvdz(:,1) = [0., -sin(x(1)) * u(1)]';
    end 

    %% lifted space losses 
    function l = get_l(obj,z) % ------------------>> l(z,u): running cost of z
      z(1) = deg2rad(z(1));
      l = z * obj.Q * z;
    end

    function ldz = get_ldz(obj,z) % ----------->> ldz(z,u): running cost of dz
      z(1) = deg2rad(z(1));
      ldz = 2 * obj.Q*z;
    end

    function m = get_m(obj,z) % ------------------->> m(z): terminal cost of z
      z(1) = deg2rad(z(1));
      m = z * obj.Qf * z;
    end

    function mdz = get_mdz(obj,z) % ------------>> mdz(z): terminal cost of dz
      z(1) = deg2rad(z(1));
      mdz = 2 * obj.Qf * z;
    end    
  end 

  methods  (Access = private)
    function init(obj)
      obj.ransamp_x();
    end
    
  end % private methods
end
 



  
  