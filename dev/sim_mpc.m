
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

%cwd = pwd;
%tmpdir = [pwd '/sim/dp'];
%mkdir(tmpdir);
%cd(tmpdir);

%% cfg sim
% 1- Create a specification for the operating point using opSpec = operspec(plantModel);
% 2- adjust your opSpec to select known/non-steady state variables. more info here.
% 3- Find the operating point using [opPoint, opReport] = findop(plantModel, opSpec) 
% 4- Perofrm lineraization [sys, ~, info] = linearize(plantModel, opPoint)
%plant = ss(tf([3 1],[1 0.6 1]));
%plant = dp;
sim = "dp"; 
open_system(sim);  % open dp in simScape 

opSpec = operspec(sim); 
disp(opSpec);
% https://www.mathworks.com/help/mpc/ug/code-generation-with-simulink-coder.html#d124e33620
% https://www.mathworks.com/help/rtw/ug/generate-code-and-simulate-models-in-project.html
% https://www.mathworks.com/help/sm/ug/how-to-build-a-model.html
% https://www.mathworks.com/help/slcontrol/ug/operspec.html?s_tid=srchtitle 
% https://www.mathworks.com/help/slcontrol/ug/addoutputspec.html
% https://www.mathworks.com/help/slcontrol/ug/findop.html
opSpec.States(1).x(1) = 1;
%opSpec.States(1).x(2) = 1;
%opSpec.States(1).x(3) = 1;
%opSpec.States(1).x(4) = 1;

disp(opSpec);



sim.InputName = {'Mass Flow';'Heat Flow';'Pressure'};
sim.OutputName = {'Temperature';'Level'};
sim.InputUnit = {'kg/s' 'J/s' 'Pa'};
sim.OutputUnit = {'K' 'm'};

Ts = 0.1;   %Sample time
p = 10;     %Prediction horizon
m = 2;      %Control horizon
Weights = struct('MV',0,'MVRate',0.01,'OV',1); % Weights
MV = struct('Min',-Inf,'Max',Inf,'RateMin',-100,'RateMax',100); % Input constraints
OV = struct('Min',-2,'Max',2); % Output constraints
mpcobj = mpc(plant,Ts,p,m,Weights,MV,OV);
x_init = [1 1 1 1];



cd(cwd);