%% vtol main
%% init sys 
%warning('off','all')
close all; clear; clc;
cfg  = cfg_class(TID    = ['T000','000','_koop_',''], ...
                 brief  = ["."], ...
                 btype  = "vtol", ...
                 bnum   = 1, ...
                 end_frame  = 200);
dlgr  = dlgr_class(); dlgr.load_cfg(cfg);
%% init app modules
kp    = koopman_class(); kp.load_cfg(cfg); % also loads dat 

%% run
gt_m    = model_class(mthd = "ground truth", rec = pi.dat); % gt

kp.gen_dset(kp.X, kp.Y, nSets); % 
kp.get_Phi();



%% results
dlgr.add_mdl(gt_m);
dlgr.add_mdl(kp_m); % 

%% post processing 
dlgr.get_errs(); 
dlgr.get_tab(); % get res table
%dlgr.plt_recons_grid();
%dlgr.plt_A_roots(); % overlay in one fig
%dlgr.plt_A_roots_sep(); % separate figs 
%dlgr.plt_A_bmaps_sep(); % separate figs 
%dlgr.plt_A_surfs_sep(); % separate figs 
%dlgr.plt_A_hmaps_sep(); % separate figs 

%% report
%rpt.gen_plots(cfg.dat, dlog, piDMD);
%rpt.gen_report(piDMD);
disp("end of process...");


