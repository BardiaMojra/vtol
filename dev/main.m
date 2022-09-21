%% koopman main
% todo: 
% - impliment DP
% - port in DIP LQR controller and compare results
%% init sys 

%warning('off','all')
close all; clear; clc;
cfg  = cfg_class(TID    = ['T000','000','_koop_',''], ...
                 brief  = ["."], ...
                 btype  = "VanDerPol", ...
                 bnum   = 1, ...
                 nTrials=10, nSamps=200, ...
                 end_frame  = 200);
dlgr  = dlgr_class(); dlgr.load_cfg(cfg);
%% gen dat 
vp    = VanDerPol_class(); vp.load_cfg(cfg) %
%% init app modules
kp    = koopman_class(); kp.load_cfg(cfg); % also loads dat 
%% gen data 
% https://www.mathworks.com/help/simulink/ug/using-the-sim-command.html#mw_630580a7-20cd-43f3-aa36-2b5b0064daf4
% 

%% run
%gt_m    = model_class(mthd = "ground truth", rec = pi.dat); % gt

vp_m = kp.get_model(vp); kp.get_optCont(vp_m);
trj  = kp.run_cont(vp_m,vp);
plot(trj);
legend("on")
%kp.Phi = kp.get_Phi_model();




%% results
%dlgr.add_mdl(gt_m);
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


