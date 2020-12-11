function [alertOut] = testDaidalus(timeLimit, ownshipValues, intruderValues, daidalusDir, singleDirRecoverBands)
% Copyright 2015 - 2020, MIT Lincoln Laboratory
% SPDX-License-Identifier: X11
%
%TESTDAIDALUS  Tests the DAIDALUS s-function interface by running the
%test_dadalus_sfunc_block simulation using DAIDALUS parameters set in the
%DaidalusV201 wrapper class.  Allows override of the singleDirRecovery 
%parameter by including a logical flag as an argument. Aircraft states are 
%set within the simulation.  Output can be compared with the output of 
%DaidalusExample.cpp.

if nargin < 5
  singleDirRecoverBands = false;
end

% Fill this out

% encounterTypeAndNumber = 'H11';
% currDir = ['~\Test_Vectors\MOPS_Test_Vectors\headon\' encounterTypeAndNumber];
% testDir = '~\DAIDALUSv201\SimulinkInterface';

% [timeLimit,ownshipValues,intruderValues] = crudeReadTestVector(encounterTypeAndNumber,currDir,testDir);

feval(@()assignin('base','timeLimit',timeLimit));
feval(@()assignin('base','ownshipValues',ownshipValues));
feval(@()assignin('base','intruderValues',intruderValues));

cd(daidalusDir)

bus_definitions;
blk = DaidalusV201('daa_');
blk.singleDirRecovery = singleDirRecoverBands;
blk.prepareSim;

% sim('test_daidalus_sfunc_block');

sim('test_vector_test_daidalus_sfunc_block');

% fprintf('Current alert level is %d\n', alertOut);

% disp(length(alertOut));

alertOut = alertOut';

figure;
plot(alertOut)

% figure; 
% set(gcf, 'Position', [503, 684, 946, 420]);
% 
% subplot(1,2,1);
% plot(-135:135, guidanceOut(1:271), 'LineWidth', 2);
% xlabel('Heading');
% ylabel('Guidance Level');
% set(gca, 'YLim', [0,5])
% 
% subplot(1,2,2);
% bar(guidanceOut(273:2:283));
% xlabel('Altitude');
% ylabel('Guidance Level');
% set(gca, 'YLim', [0, 5]);
% set(gca, 'XTickLabel', arrayfun(@(x){num2str(x)}, guidanceOut(272:2:282)));

end