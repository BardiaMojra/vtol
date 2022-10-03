%% MPC sim example 
% @link https://www.mathworks.com/help/mpc/gs/control-of-a-multi-input-multi-output-nonlinear-plant.html


% Check that both Simulink and Simulink Control Design are installed,
% otherwise display a message and return
if ~mpcchecktoolboxinstalled('simulink')
    disp('Simulink(R) is required to run this example.')
    return
end
if ~mpcchecktoolboxinstalled('slcontrol')
    disp('Simulink Control Design(R) is required to run this example.')
    return
end


%warning('off','all')
close all; clear; clc; addpath(genpath('./'));

%% plant 
open('mpc_nonlinmodel')

plant = linearize('mpc_nonlinmodel');

plant.InputName = {'Mass Flow';'Heat Flow';'Pressure'};
plant.OutputName = {'Temperature';'Level'};
plant.InputUnit = {'kg/s' 'J/s' 'Pa'};
plant.OutputUnit = {'K' 'm'};

%% design MPC controller 

mpcobj = mpc(plant,0.2,5,2);
mpcobj.MV = struct('Min',{-3;-2;-2},'Max',{3;2;2},'RateMin',{-1000;-1000;-1000});
mpcobj.Weights = struct('MV',[0 0 0],'MVRate',[.1 .1 .1],'OV',[1 1]);

mpcobj % shw mpc obj


mdl1 = 'mpc_nonlinear';
open_system(mdl1)

sim(mdl1) % run closed loop simulation


%% modify MPC design to track ramp signals 
outdistmodel = tf({1 0;0 1},{[1 0 0 0],1;1,[1 0 0 0]});
setoutdist(mpcobj,'model',outdistmodel);

mdl2 = 'mpc_nonlinear_setoutdist';
open_system(mdl2)









