%% koopman main
% todo: 
% - impliment CP explicit mod
% - gen data
% - on hold: in code simScape
% -- https://www.mathworks.com/help/mpc/ug/code-generation-with-simulink-coder.html 
% https://www.mathworks.com/help/simulink/ug/using-the-sim-command.html#mw_630580a7-20cd-43f3-aa36-2b5b0064daf4
% - port in DIP LQR controller and compare results
%% init sys 

%warning('off','all')
close all; clear; clc; addpath(genpath('./'));

cfg  = cfg_class(TID    = ['T000','000',''], ...
                 brief  = ("."), ...
                 btype  = "cp_emod", ...
                 nTrials=10, nSamps=200);
%% util
dlgr  = dlgr_class(); dlgr.load_cfg(cfg);
%% dat/sim
%vp    = VanDerPol_class(); vp.load_cfg(cfg); %
cp    = cp_emod(); cp.load_cfg(cfg); % cart-pend
%dp    = dp_sim(); dp.load_cfg(cfg);
%% init app modules
%kp    = koopman_class(); kp.load_cfg(cfg); 
kpc    = kpcp_class(); kpc.load_cfg(cfg); 

%% run
%gt_m    = model_class(mthd = "ground truth", rec = pi.dat); % gt

kpc_m = kpc.get_mod(cp); 
%kp.get_optCont(vp_m);
trj  = kpc.run_cont(vp_m,vp);
plot(trj);
legend("cart","pend")
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


