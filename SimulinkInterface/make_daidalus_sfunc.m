function make_daidalus_sfunc( )
% Copyright 2015 - 2020, MIT Lincoln Laboratory
% SPDX-License-Identifier: X11

path2Daidalus = input('Please enter the absolute path to DAIDALUS root directory: ', 's');
daidLibName = input('Please enter the name of the DAIDALUS library (Example: Daidalus2.a or daidalusv201c.lib): ', 's');

includePath = fullfile(path2Daidalus,'C++','include');
libPath = fullfile(path2Daidalus,'C++','lib',daidLibName);

eval(sprintf('mex -I%s sfnc_daidalus_alertingV201.cpp DaidalusAlertAndGuidance.cpp %s',includePath, libPath));
