/*
Interface to DAIDALUS v2.0.1c alerting and suggestive guidance

Copyright 2015 - 2020, MIT Lincoln Laboratory
SPDX-License-Identifier: X11

Input:
   6-element ownship state vector relative to current ownship horizontal position, ENU in [nm, nm, ft, kt, kt, fpm]
   6-element ownship state vector relative to current ownship horizontal position, ENU in [nm, nm, ft, kt, kt, fpm]
   Conflict region definition (DTHR (ft), ZTHR (ft), TTHR (s), TCOA (s), lookahead time (s))
   Preventive alert definition (DTHR (ft), ZTHR (ft), TTHR (s), TCOA (s), lookahead time (s))
   Corrective alert definition (DTHR (ft), ZTHR (ft), TTHR (s), TCOA (s), lookahead time (s))
   Warning alert definition (DTHR (ft), ZTHR (ft), TTHR (s), TCOA (s), lookahead time (s))
   Ownship maximum turn rate (deg/s)
   Ownship maximum vertical rate (fpm)

Output:
   312-element integer array:
       Element 0: current alert level (0=None, 1=Preventive, 2=Corrective, 3=Warning)
       Elements 1-271: track band states from -135 to +135 deg from ownship current heading
       Elements 272-285: pairs of altitude (in ft) and altitude band state
       Elements 286-311: pairs of vertical speeds (in fpm) and vs band state
   Horizontal recovery direction (integer, 0=Left, 1=Right)
   Vertical recovery direction (integer, 0=Down, 1=Up)

Band states are:
   0 - no conflict
   1 - recovery
   4 - conflict

*/

#include "Daidalus.h"
#include "interf_daidalus.h"
#include "WCV_TAUMOD.h"
#include "WCVTable.h"
#include "Alerter.h"
#include "AlertThresholds.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace larcfm;

int toLevel(std::string region) {

    if (region.compare("NONE") == 0)
        return 0;
    else if (region.compare("RECOVERY") == 0)
        return 1;
    else if (region.compare("MID") == 0)
        return 3;
    else if (region.compare("NEAR") == 0)
        return 4;
    else if (region.compare("UNKNOWN") == 0)
        return 4;
    else
        return -1;
}

#ifdef _WIN32
double round(double v)  {
  return v < 0.0 ? std::ceil(v - 0.5) : std::floor(v + 0.5);
}
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
                     double* CAFactor) {

    // Create main DAIDALUS object
    Daidalus daa;

    // Set default parameters
    daa.set_Buffered_WC_DO_365(true);
    
    // Set alerting thresholds
    WCVTable preventive = WCVTable();
    preventive.setDTHR(*prevDTHR,"nmi");
    preventive.setZTHR(*prevZTHR,"ft");
    preventive.setTTHR(*prevTTHR);
    preventive.setTCOA(*prevTCOA);

    WCVTable corrective = WCVTable();
    corrective.setDTHR(*corrDTHR,"nmi");
    corrective.setZTHR(*corrZTHR,"ft");
    corrective.setTTHR(*corrTTHR);
    corrective.setTCOA(*corrTCOA);

    WCVTable warning = WCVTable();
    warning.setDTHR(*warnDTHR,"nmi");
    warning.setZTHR(*warnZTHR,"ft");
    warning.setTTHR(*warnTTHR);
    warning.setTCOA(*warnTCOA);

    Alerter alerter = Alerter();
    alerter.addLevel(AlertThresholds(&WCV_TAUMOD(preventive),*prevLookTime,*prevEarly,BandsRegion::NONE));
    alerter.addLevel(AlertThresholds(&WCV_TAUMOD(corrective),*corrLookTime,*corrEarly,BandsRegion::MID));
    alerter.addLevel(AlertThresholds(&WCV_TAUMOD(warning),*warnLookTime,*warnEarly,BandsRegion::NEAR));    
    
    daa.clearAlerters();
    daa.addAlerter(alerter);
    
    // Set other options
    daa.setTurnRate(*turnRate, "deg/s");
    daa.setVerticalRate(*vertRate, "fpm");
    daa.setMinAltitude(*MinimumAltitude, "ft");
    daa.setRecoveryStabilityTime(*RecoveryStabilityTime, "s");
    daa.setMinHorizontalRecovery(*MinimumHorizontalRecovery, "nmi");
    daa.setCollisionAvoidanceBandsFactor(*CAFactor);        

    // Get aircraft state information for ownship and intruder and set in DAIDALUS
    Position so = Position::makeXYZ(xOwn[0], xOwn[1], xOwn[2]);
    Velocity vo = Velocity::makeVxyz(xOwn[3], xOwn[4], xOwn[5]);
    Position si = Position::makeXYZ(xInt[0], xInt[1], xInt[2]);
    Velocity vi = Velocity::makeVxyz(xInt[3], xInt[4], xInt[5]);
    daa.setOwnshipState("ownship",so,vo,0.0);
    daa.addTrafficState("intruder",si,vi);

    // Set wind information -- assume no wind
    Velocity wind = Velocity::makeTrkGsVs(0,"deg", 0,"knot", 0,"fpm");
    daa.setWindVelocityTo(wind);

    // Initialize band output array
    for (int i=0; i<312; i++)
        bandsOut[i] = 0;

    // Fill temporary array with track band output
    int tmpBands[361];
    for (int i=0; i<361;i++)
        tmpBands[i] = 999;
    
    // Get alert level and store in first element of output array (assumes single intruder)
    bandsOut[0] = daa.alertLevel(1);
        
    // Get band data
    for (int i=0; i < daa.horizontalDirectionBandsLength(); ++i) {
        Interval intrv = daa.horizontalDirectionIntervalAt(i,"deg");
        std::string lvl_str = BandsRegion::to_string(daa.horizontalDirectionRegionAt(i));
        int lvl = toLevel(lvl_str);

        int lo = static_cast<int>(std::floor(intrv.low + 0.5));
        int hi = static_cast<int>(std::floor(intrv.up + 0.5));

        for (int j=lo; j<=hi; j++) {
            tmpBands[j] = std::min(lvl, tmpBands[j]);
        }
    }

    // Fill in track band output for +/- 135 degrees from current ownship heading
    int ownHdg = static_cast<int>(round(vo.track("deg")));
    for (int i=1; i<272; i++) {
        int j = ownHdg + (i-136);
        j = j < 0 ? j + 360 : j;
        j = j > 360 ? j - 360 : j;
        bandsOut[i] = tmpBands[j];
    }

    // Fill in altitude band output
    int currAlt = static_cast<int>(std::floor(xOwn[2]/500)*500);
    int altLvls[7] = {currAlt - 1500, currAlt - 1000, currAlt - 500, currAlt, currAlt + 500, currAlt + 1000, currAlt + 1500};

    for (int j=0; j<7; j++) {
        bandsOut[272 + 2*j + 1] = 999;
        for (int i=0; i < daa.altitudeBandsLength(); ++i) {
            Interval intrv = daa.altitudeIntervalAt(i,"ft");
            std::string lvl_str = BandsRegion::to_string(daa.altitudeRegionAt(i));
            int lvl = toLevel(lvl_str);

            if (altLvls[j] >= intrv.low && altLvls[j] <= intrv.up) {
                bandsOut[272 + 2*j] = altLvls[j];
                bandsOut[272 + 2*j + 1] = std::min(lvl, bandsOut[272 + 2*j + 1]);
            }
            // Note: if altitude level is below the DAIDALUS minimum altitude, band level will be 999
        }
    }
    // Fill in vertical speed band output
    // The vertical rate is not used in DEGAS
    
    int vsLvls[13] = {-3000, -2500, -2000, -1500, -1000, -500, 0, 500, 1000, 1500, 2000, 2500, 3000};
    
    for (int j=0; j<13; j++) {
        bandsOut[286 + 2*j + 1] = 999;
        for (int i=0; i < daa.verticalSpeedBandsLength(); ++i) {
            Interval intrv = daa.verticalSpeedIntervalAt(i,"ft");
            std::string lvl_str = BandsRegion::to_string(daa.verticalSpeedRegionAt(i));
            int lvl = toLevel(lvl_str);

            if (vsLvls[j] >= intrv.low && vsLvls[j] <= intrv.up) { 
                bandsOut[286 + 2*j] = vsLvls[j];
                bandsOut[286 + 2*j + 1] = std::min(lvl, bandsOut[286 + 2*j + 1]);
            }
            // note: if altitude level is below the DAIDALUS minimum altitude, band level will be 999
        }
    }

    *recoverRight = static_cast<int>(daa.preferredHorizontalDirectionRightOrLeft());    // true = right
    *recoverUp = static_cast<int>(daa.preferredAltitudeUpOrDown());   // true = up
    
    return 0;
}

