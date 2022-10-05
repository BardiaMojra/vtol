classdef dp_sim < matlab.System 
  properties
    %% class
    % @link https://www.mathworks.com/help/mpc/ug/code-generation-with-simulink-coder.html
    cName       = "dp_class" % 
    desc        = ["Double pendulum simulation class"]
    %credit      = ""
    %% features 
    en_shw_sim  = true 
    en_sav_dat
    en_sav_sim

    %% cfg (argin)
    btype       = "dp" % double pendulum
    %bnum    
    simDir
    toutDir 
    soutDir
    %datDir            
    nTrials     = 5 % num of trials, dat is concat of nTrials
    nSamps      = 200 % disc length of each trial 

    %% settings
    nIn         = 3 % num of inputs
    inNames     = {'Mass Flow';'Heat Flow';'Pressure'} % input labels 
    inUnits     = {'kg/s', 'J/s', 'Pa'} % input units 

    nOut        = 2 % num of outputs 
    outNames    = {'Temperature';'Level'} % output labels 
    outUnits    = {'K', 'm'} % output units 

    eps     = 1.0
    dt      = 0.01
    stRange = 6
    uRange  = 0.1
    %% opt
    sim % sim obj
    x   % state 
    u   % input 
    xdot % state derivative 
    %f   % function 
    %dfdx not vars, fpntr
    %dfdu not vars, fpntr
    %% 
    %dat % dat 
    %nVars % same as nx
    %nSamps
  end
  methods 
    function obj = dp_sim(varargin) 
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
      obj.check_deps();
    end 
  end % methods 
  methods (Access = public) 
    


    function load_cfg(obj, cfg) 
      obj.toutDir     = cfg.toutDir;
      obj.simDir      = cfg.simDir;
      obj.btype       = cfg.btype;
      %obj.nTrials     = cfg.nTrials;
      %obj.nSamps      = cfg.nSamps;
      cfg.sim       = obj; 
      obj.init();
    end
  end % methods (Access = public)
  
  methods  (Access = private)
    function init(obj)
      obj.set_soutDir();% setup soutDir
      obj.load_sim();

    end

    function check_deps(~)
      if ~mpcchecktoolboxinstalled('simulink')
        disp('Simulink is required to run this example.')
        return
      end
    end % check_deps()
    
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

    function load_sim(obj)
       simFile = strcat(obj.simDir,"/",obj.btype);
       if obj.en_shw_sim
         open(simFile)
       end
       obj.sim = linearize(simFile);

    end 

  end % private methods
end
 



  
  