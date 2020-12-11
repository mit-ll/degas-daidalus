classdef DaidalusV201 < Block
% Copyright 2015 - 2020, MIT Lincoln Laboratory
% SPDX-License-Identifier: X11
%
%DaidalusV201
%Wrapper class for the DAIDALUS v2.0.1 block.

  properties        
      
    guideLookahead = 180
    guideDTHR = 4000
    guideZTHR = 450
    guideTTHR = 35
    guideTCOA = 0
    
    prevLookahead = 60
    prevEarly = 75
    prevDTHR = 1.0
    prevZTHR = 750
    prevTTHR = 35
    prevTCOA = 20
    
    corrLookahead = 60
    corrEarly = 75
    corrDTHR = 1.0
    corrZTHR = 450
    corrTTHR = 35
    corrTCOA = 20
    
    warnLookahead = 30
    warnEarly = 55
    warnDTHR = 1.0
    warnZTHR = 450
    warnTTHR = 35
    warnTCOA = 20
    
    singleDirRecovery = false;
    
    % Conflict Bands Parameters
    minAlt = 100 % ft
    
    % Recovery Bands Parameters
    recStabTime = 2.0 % s
    minHorRec = 1.0 % nm
    caFactor = 0.2 % unitless
    
    % Daidalus Ownship Assumptions
    turnRate_dps = 3.0; % deg/s
    vertRate_fpm = 500.0; % fpm
    
  end
  
  
  methods % constructor
    function obj = DaidalusV201(tunableParameterPrefix,varargin)
      if( nargin < 1 )
        tunableParameterPrefix = '';
      end

      p = inputParser;
      addRequired(p,'tunableParameterPrefix',@ischar);
      addOptional(p, 'guideLookahead', obj.guideLookahead, @isnumeric);
      addOptional(p, 'guideDTHR', obj.guideDTHR, @isnumeric);
      addOptional(p, 'guideZTHR', obj.guideZTHR, @isnumeric);
      addOptional(p, 'guideTTHR', obj.guideTTHR, @isnumeric);
      addOptional(p, 'guideTCOA', obj.guideTCOA, @isnumeric);
      addOptional(p, 'prevLookahead', obj.prevLookahead, @isnumeric);
      addOptional(p, 'prevEarly', obj.prevEarly, @isnumeric);
      addOptional(p, 'prevDTHR', obj.prevDTHR, @isnumeric);
      addOptional(p, 'prevZTHR', obj.prevZTHR, @isnumeric);
      addOptional(p, 'prevTTHR', obj.prevTTHR, @isnumeric);
      addOptional(p, 'prevTCOA', obj.prevTCOA, @isnumeric);
      addOptional(p, 'corrLookahead', obj.corrLookahead, @isnumeric);
      addOptional(p, 'corrEarly', obj.corrEarly, @isnumeric);
      addOptional(p, 'corrDTHR', obj.corrDTHR, @isnumeric);
      addOptional(p, 'corrZTHR', obj.corrZTHR, @isnumeric);
      addOptional(p, 'corrTTHR', obj.corrTTHR, @isnumeric);
      addOptional(p, 'corrTCOA', obj.corrTCOA, @isnumeric);
      addOptional(p, 'warnLookahead', obj.warnLookahead, @isnumeric);
      addOptional(p, 'warnEarly', obj.warnEarly, @isnumeric);
      addOptional(p, 'warnDTHR', obj.warnDTHR, @isnumeric);
      addOptional(p, 'warnZTHR', obj.warnZTHR, @isnumeric);
      addOptional(p, 'warnTTHR', obj.warnTTHR, @isnumeric);
      addOptional(p, 'warnTCOA', obj.warnTCOA, @isnumeric);
      addOptional(p, 'singleDirRecovery', obj.singleDirRecovery, @islogical);
      addOptional(p, 'minAlt', obj.minAlt, @isnumeric);
      addOptional(p, 'recStabTime', obj.recStabTime, @isnumeric);
      addOptional(p, 'minHorRec', obj.minHorRec, @isnumeric);
      addOptional(p, 'caFactor', obj.caFactor, @isnumeric);      
      addOptional(p, 'turnRate_dps', obj.turnRate_dps, @isnumeric);
      addOptional(p, 'vertRate_fpm', obj.vertRate_fpm, @isnumeric);        
      
      parse(p,tunableParameterPrefix,varargin{:});

      fieldsSet = intersect( fieldnames(p.Results), fieldnames(obj) );
      for i = 1:1:numel(fieldsSet)
        obj.(fieldsSet{i}) = p.Results.(fieldsSet{i});
      end
      
    end % constructor method
    
    function setDaidalusToNoncoop(this)
        
        this.guideLookahead = 180;
        
        this.prevLookahead = 60;
        this.prevEarly = 75;
        this.prevDTHR = 0.55002;
        this.prevZTHR = 750;
        this.prevTTHR = 0;
        this.prevTCOA = 0;
        
        this.corrLookahead = 60;
        this.corrEarly = 75;
        this.corrDTHR = 0.55002;
        this.corrZTHR = 450;
        this.corrTTHR = 0;
        this.corrTCOA = 0;
        
        this.warnLookahead = 30;
        this.warnEarly = 55;
        this.warnDTHR = 0.55002;
        this.warnZTHR = 450;
        this.warnTTHR = 0;
        this.warnTCOA = 0;
        
        this.minAlt = 0;
        this.recStabTime = 3;
        this.minHorRec = 0.55002;
        this.caFactor = 0.1;        
        
    end
    
    function setDaidalusToDefault(this)
        
        this.guideLookahead = 180;
        this.guideDTHR = 4000;
        this.guideZTHR = 450;
        this.guideTTHR = 35;
        this.guideTCOA = 0;

        this.prevLookahead = 60;
        this.prevEarly = 75;
        this.prevDTHR = 1.0;
        this.prevZTHR = 750;
        this.prevTTHR = 35;
        this.prevTCOA = 20;

        this.corrLookahead = 60;
        this.corrEarly = 75;
        this.corrDTHR = 1.0;
        this.corrZTHR = 450;
        this.corrTTHR = 35;
        this.corrTCOA = 20;

        this.warnLookahead = 30;
        this.warnEarly = 55;
        this.warnDTHR = 1.0;
        this.warnZTHR = 450;
        this.warnTTHR = 35;
        this.warnTCOA = 20;

        this.singleDirRecovery = false;

        % Conflict Bands Parameters
        this.minAlt = 100; % ft

        % Recovery Bands Parameters
        this.recStabTime = 2.0; % s
        this.minHorRec = 1.0; % nm
        this.caFactor = 0.2; % unitless
        
    end    
    
  end 

  methods (Access='protected')
  
        function [ incPaths, srcFiles, libFiles ] = getSourceAndLibs( ~ )
          
          incPaths = {'./DAIDALUSv201/DAIDALUS/C++/include'};
          srcFiles = {'./DAIDALUSv201/SimulinkInterface/DaidalusAlertAndGuidance.cpp', ...
                      './DAIDALUSv201/SimulinkInterface/sfnc_daidalus_alertingV201.cpp'};
          libFiles = {'./DAIDALUSv201/DAIDALUS/C++/lib/daidalus.lib'};
          
        end
  end
  
end % classdef