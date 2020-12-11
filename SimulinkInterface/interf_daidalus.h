/*
 * Copyright 2015 - 2020, MIT Lincoln Laboratory
 * SPDX-License-Identifier: X11
 */

#ifndef daidalus_interf_h
#define daidalus_interf_h

#ifdef __cplusplus
   extern "C"
   {
#endif

int getDaidalusBands(double* xOwn, 
                     double* xInt, 
                     double* DTHR, 
                     double* ZTHR, 
                     double* TTHR, 
                     double* TCOA, 
                     double* lookTime,
                     double* prevDTHR, 
                     double* prevZTHR, 
                     double* prevTTHR, 
                     double* prevTCOA, 
                     double* prevLookTime,
                     double* prevEarly,
                     double* corrDTHR, 
                     double* corrZTHR, 
                     double* corrTTHR, 
                     double* corrTCOA, 
                     double* corrLookTime,
                     double* corrEarly,
                     double* warnDTHR, 
                     double* warnZTHR, 
                     double* warnTTHR, 
                     double* warnTCOA, 
                     double* warnLookTime,
                     double* warnEarly,
                     double* turnRate, 
                     double* vertRate, 
                     int* bandsOut,
                     int* recoverRight,
                     int* recoverUp,
                     double* MinimumAltitude,
                     double* RecoveryStabilityTime,
                     double* MinimumHorizontalRecovery,
                     double* CAFactor);

#ifdef __cplusplus
   }
#endif

#endif
