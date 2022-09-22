
%% Model Predictive Control of a Multi-Input Multi-Output Nonlinear Plant
% https://www.mathworks.com/help/mpc/gs/control-of-a-multi-input-multi-output-nonlinear-plant.html
%% check deps 
if ~mpcchecktoolboxinstalled('simulink')
    disp('Simulink is required to run this example.')
    return
end
if ~mpcchecktoolboxinstalled('simulinkcoder')
    disp('Simulink Coder is required to run this example.');
    return
end
if ~mpcchecktoolboxinstalled('slcontrol')
    disp('Simulink Control Design(R) is required to run this example.')
    return
end
%% WS init
%warning('off','all')
close all; clear; clc; addpath(genpath('./'));

cwd = pwd;
tmpdir = [pwd '/sim/dp'];
mkdir(tmpdir);
%cd(tmpdir);

%% cfg sim 
%plant = ss(tf([3 1],[1 0.6 1]));
%plant = dp;
open("dp");

plant = dp; % ??


plant.InputName = {'Mass Flow';'Heat Flow';'Pressure'};
plant.OutputName = {'Temperature';'Level'};
plant.InputUnit = {'kg/s' 'J/s' 'Pa'};
plant.OutputUnit = {'K' 'm'};

Ts = 0.1;   %Sample time
p = 10;     %Prediction horizon
m = 2;      %Control horizon
Weights = struct('MV',0,'MVRate',0.01,'OV',1); % Weights
MV = struct('Min',-Inf,'Max',Inf,'RateMin',-100,'RateMax',100); % Input constraints
OV = struct('Min',-2,'Max',2); % Output constraints
mpcobj = mpc(plant,Ts,p,m,Weights,MV,OV);
x_init = [1 1 1 1];



cd(cwd);