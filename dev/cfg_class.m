classdef cfg_class < matlab.System 
  properties
    %% class
    class       = 'cfg'
    note        = ''
    %% features
    sav_cfg_en  = true % sav cfg as txt file
    %% configs --->> write to other modules
    TID         = '_test_'
    brief       = '' % test brief 
    projDir     =  pwd 
    outDir      = [pwd '/out']   
    simDir      = [pwd '/sim']   
    datDir      = '~/data/vtol'   
    ttag        % test tag [TID]_[btype]_[bnum]% dset
    toutDir     % outDir+ttag
    % benchmark cfg  
    bmode       = "sim" % or "dat"
    btype       % usr input e.g. "dp"
    btypes      = {"sp","dp","vtol"}
    bnum        = nan % btype subset
    st_frame    = nan % start frame index
    end_frame   = nan % end frame index
    nTrials     = nan % start frame index
    nSamps      = nan % end frame index
    %% 
    dat % dataset
    sim % sim model - generates dat
  end
  methods  % constructor
    function obj = cfg_class(varargin)
      setProperties(obj,nargin,varargin{:}) % init obj w name-value args
      addpath(genpath('./'));
      init(obj);
    end
  end 
  methods (Access = private)
  
    function init(obj)
      assert(~isempty(obj.btype),'[cfg]->> cfg.btype is empty: %s',obj.btype)
      obj.set_ttag();
      obj.set_toutDir();
      %obj.load_dat(); % 
      %obj.load_sim(); % 
      obj.sav_cfg(); % sav cfg to file
    end

%     function load_sim(obj)
%       if strcmp(obj.btype, 'VanDerPol') % --------->>> 
%         obj.sim       = VanDerPol_class(); obj.sim.load_cfg(obj); % load sim
%       else
%         error('[cfg]->> simulation dataset...');
%       end    
%     end
    
    function load_dat(obj)
      obj.dat       = dat_class(); obj.dat.load_cfg(obj); % load data
      obj.st_frame  = obj.dat.st_frame;
      obj.end_frame = obj.dat.end_frame;
    end

    function sav_cfg(obj)
      if ~isempty(obj.brief) || obj.sav_cfg_en
        fname = strcat(obj.toutDir,"cfg.txt"); 
        file = fopen(fname,"wt");
        fprintf(file, strcat("TID:      ", obj.TID, "\n"));
        fprintf(file, strcat("brief:    ", obj.brief, "\n"));
        fprintf(file, strcat("projDir:  ", obj.projDir, "\n"));
        fprintf(file, strcat("outDir:   ", obj.outDir, "\n"));
        fprintf(file, strcat("datDir:   ", obj.datDir, "\n"));
        fprintf(file, strcat("ttag:     ", obj.ttag, "\n"));
        fprintf(file, strcat("toutDir:  ", obj.toutDir, "\n"));
        fprintf(file, strcat("btype:    ", obj.btype, "\n"));
        fprintf(file, strcat("bnum:     ", num2str(obj.bnum), "\n"));
        fprintf(file, strcat("st_frame: ", num2str(obj.st_frame), "\n"));
        fprintf(file, strcat("end_frame:", num2str(obj.end_frame),"\n"));
        fclose(file);
      end
    end % sav_cfg()

    function set_ttag(obj)
      if isnan(obj.bnum) % get test tag and toutDir
        obj.ttag  = strcat(obj.TID,'_',obj.btype);
      else 
        obj.ttag  = strcat(obj.TID );% ,'_', obj.btype,'_', num2str(obj.bnum,'%02.f'));
      end      
      obj.ttag = strrep(obj.ttag,' ','_');
      %obj.ttag = strrep(obj.ttag,'-','_');

    end % set_ttag()
    
    function set_toutDir(obj)
      obj.toutDir = strcat(obj.outDir,'/',obj.ttag,'/');
      if not(isfolder(obj.toutDir)) % create toutDir
        disp("[config]->> test_toutDir does NOT exist: ");
        disp(obj.toutDir);
        mkdir(obj.toutDir);
        disp("[config]->> directory was created!");
      else 
        disp("[config]->> test_toutDir exists and will be removed: ");
        disp(obj.toutDir);
        rmdir(obj.toutDir, 's');
        mkdir(obj.toutDir);
        disp("[config]->> directory was created!");
      end 
    end % set_toutDir()
  end % methods (Access = private)
end
