open_system("dp"); % open simulation 
% Configure model: Under Modelling tab, Config Parameters, select "Generate Code Only"
% Generate code: Use Simulink Coder to generate C code ---->> this C source code
% Config C/C++ compiler
mex -setup