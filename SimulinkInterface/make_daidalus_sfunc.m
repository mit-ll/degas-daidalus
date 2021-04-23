function make_daidalus_sfunc( )
% Copyright 2015 - 2020, MIT Lincoln Laboratory
% SPDX-License-Identifier: X11

% Get path to DAIDALUS root directory
path2Daidalus = input('Please enter the absolute path to DAIDALUS root directory: ', 's');
if any(isspace(path2Daidalus))
    error('Path to DAIDALUS root directory cannot have whitespaces.');
end

% Get name of DAIDALUS library
daidLibName = input('Please enter the name of the DAIDALUS library (Example: Daidalus2.a or daidalusv201c.lib): ', 's');
if any(isspace(daidLibName))
    error('Name of the DAIDALUS library cannot have whitespaces.');
end

% Setup include and library paths for mexing
includePath = fullfile(path2Daidalus,'C++','include');
libPath = fullfile(path2Daidalus,'C++','lib',daidLibName);

% Mex DAIDALUS s-function 
eval(sprintf('mex -I%s sfnc_daidalus_alertingV201.cpp DaidalusAlertAndGuidance.cpp %s',includePath, libPath));