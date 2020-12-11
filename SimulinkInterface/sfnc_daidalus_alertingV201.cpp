/*
 * File: sfnc_daidalus_alerting.cpp
 *
 * S-function interface to DaidulusAlertAndGuidance.cpp
 * DAIDALUS version 2.0.1c
 *
 * Copyright 2015 - 2020, MIT Lincoln Laboratory
 * SPDX-License-Identifier: X11
 *
 * S-function takes 24 input signals: 
 *      - 6x1 ENU ownship state vector (horizontal position 0,0)
 *      - 6x1 ENU intruder state vector (horizontal position relative to ownship)
 *      - Conflict region definition (DTHR, ZTHR, TTHR, TCOA, lookahead time)
 *      - Preventive alert definition (DTHR, ZTHR, TTHR, TCOA, lookahead time)
 *      - Corrective alert definition (DTHR, ZTHR, TTHR, TCOA, lookahead time)
 *      - Warning alert definition (DTHR, ZTHR, TTHR, TCOA, lookahead time)
 *      - Ownship max turn rate
 *      - Ownship max vertical rate
 *
 * S-function takes no parameters.
 *
 * S-function outputs 5 signals:
 *      - Status flag (0=OK, 1=No guidance)
 *      - 283x1 guidance vector 
 *              Elements 1-271: alert level for turns +/-135 current ownship heading
 *              Elements 272-283: [altitude, alert level] pairs
 *              Alert levels are 0=clear (green), 1=recovery (dashed green), 4=conflict (red)
 *      - Alert Level (0=None, 1=Preventive, 2=Corrective, 3=Warning)
 *      - Horizontal recovery direction (0=Left, 1=Right)
 *      - Vertical recovery direction (0=Down, 1=Up)
 *
 */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME sfnc_daidalus_alertingV201

#define NUM_INPUTS          31
/* Input Port  0 */
#define IN_PORT_0_NAME      OwnshipStateVector
#define INPUT_0_WIDTH       6
#define INPUT_DIMS_0_COL    1
#define INPUT_0_DTYPE       real_T
#define INPUT_0_COMPLEX     COMPLEX_NO
#define IN_0_FRAME_BASED    FRAME_NO
#define IN_0_BUS_BASED      0
#define IN_0_BUS_NAME       
#define IN_0_DIMS           1-D
#define INPUT_0_FEEDTHROUGH 1
#define IN_0_ISSIGNED        0
#define IN_0_WORDLENGTH      8
#define IN_0_FIXPOINTSCALING 1
#define IN_0_FRACTIONLENGTH  9
#define IN_0_BIAS            0
#define IN_0_SLOPE           0.125
/* Input Port  1 */
#define IN_PORT_1_NAME      IntruderStateVector
#define INPUT_1_WIDTH       6
#define INPUT_DIMS_1_COL    1
#define INPUT_1_DTYPE       real_T
#define INPUT_1_COMPLEX     COMPLEX_NO
#define IN_1_FRAME_BASED    FRAME_NO
#define IN_1_BUS_BASED      0
#define IN_1_BUS_NAME       
#define IN_1_DIMS           1-D
#define INPUT_1_FEEDTHROUGH 1
#define IN_1_ISSIGNED        0
#define IN_1_WORDLENGTH      8
#define IN_1_FIXPOINTSCALING 1
#define IN_1_FRACTIONLENGTH  9
#define IN_1_BIAS            0
#define IN_1_SLOPE           0.125
/* Input Port  2 */
#define IN_PORT_2_NAME      ConflictDTHR
#define INPUT_2_WIDTH       1
#define INPUT_DIMS_2_COL    1
#define INPUT_2_DTYPE       real_T
#define INPUT_2_COMPLEX     COMPLEX_NO
#define IN_2_FRAME_BASED    FRAME_NO
#define IN_2_BUS_BASED      0
#define IN_2_BUS_NAME       
#define IN_2_DIMS           1-D
#define INPUT_2_FEEDTHROUGH 1
#define IN_2_ISSIGNED        0
#define IN_2_WORDLENGTH      8
#define IN_2_FIXPOINTSCALING 1
#define IN_2_FRACTIONLENGTH  9
#define IN_2_BIAS            0
#define IN_2_SLOPE           0.125
/* Input Port  3 */
#define IN_PORT_3_NAME      ConflictZTHR
#define INPUT_3_WIDTH       1
#define INPUT_DIMS_3_COL    1
#define INPUT_3_DTYPE       real_T
#define INPUT_3_COMPLEX     COMPLEX_NO
#define IN_3_FRAME_BASED    FRAME_NO
#define IN_3_BUS_BASED      0
#define IN_3_BUS_NAME       
#define IN_3_DIMS           1-D
#define INPUT_3_FEEDTHROUGH 1
#define IN_3_ISSIGNED        0
#define IN_3_WORDLENGTH      8
#define IN_3_FIXPOINTSCALING 1
#define IN_3_FRACTIONLENGTH  9
#define IN_3_BIAS            0
#define IN_3_SLOPE           0.125
/* Input Port  4 */
#define IN_PORT_4_NAME      ConflictTTHR
#define INPUT_4_WIDTH       1
#define INPUT_DIMS_4_COL    1
#define INPUT_4_DTYPE       real_T
#define INPUT_4_COMPLEX     COMPLEX_NO
#define IN_4_FRAME_BASED    FRAME_NO
#define IN_4_BUS_BASED      0
#define IN_4_BUS_NAME       
#define IN_4_DIMS           1-D
#define INPUT_4_FEEDTHROUGH 1
#define IN_4_ISSIGNED        0
#define IN_4_WORDLENGTH      8
#define IN_4_FIXPOINTSCALING 1
#define IN_4_FRACTIONLENGTH  9
#define IN_4_BIAS            0
#define IN_4_SLOPE           0.125
/* Input Port  5 */
#define IN_PORT_5_NAME      ConflictTCOA
#define INPUT_5_WIDTH       1
#define INPUT_DIMS_5_COL    1
#define INPUT_5_DTYPE       real_T
#define INPUT_5_COMPLEX     COMPLEX_NO
#define IN_5_FRAME_BASED    FRAME_NO
#define IN_5_BUS_BASED      0
#define IN_5_BUS_NAME       
#define IN_5_DIMS           1-D
#define INPUT_5_FEEDTHROUGH 1
#define IN_5_ISSIGNED        0
#define IN_5_WORDLENGTH      8
#define IN_5_FIXPOINTSCALING 1
#define IN_5_FRACTIONLENGTH  9
#define IN_5_BIAS            0
#define IN_5_SLOPE           0.125
/* Input Port  6 */
#define IN_PORT_6_NAME      GuidanceLookahead
#define INPUT_6_WIDTH       1
#define INPUT_DIMS_6_COL    1
#define INPUT_6_DTYPE       real_T
#define INPUT_6_COMPLEX     COMPLEX_NO
#define IN_6_FRAME_BASED    FRAME_NO
#define IN_6_BUS_BASED      0
#define IN_6_BUS_NAME       
#define IN_6_DIMS           1-D
#define INPUT_6_FEEDTHROUGH 1
#define IN_6_ISSIGNED        0
#define IN_6_WORDLENGTH      8
#define IN_6_FIXPOINTSCALING 1
#define IN_6_FRACTIONLENGTH  9
#define IN_6_BIAS            0
#define IN_6_SLOPE           0.125
/* Input Port  7 */
#define IN_PORT_7_NAME      PreventiveAlertDTHR
#define INPUT_7_WIDTH       1
#define INPUT_DIMS_7_COL    1
#define INPUT_7_DTYPE       real_T
#define INPUT_7_COMPLEX     COMPLEX_NO
#define IN_7_FRAME_BASED    FRAME_NO
#define IN_7_BUS_BASED      0
#define IN_7_BUS_NAME       
#define IN_7_DIMS           1-D
#define INPUT_7_FEEDTHROUGH 1
#define IN_7_ISSIGNED        0
#define IN_7_WORDLENGTH      8
#define IN_7_FIXPOINTSCALING 1
#define IN_7_FRACTIONLENGTH  9
#define IN_7_BIAS            0
#define IN_7_SLOPE           0.125
/* Input Port  8 */
#define IN_PORT_8_NAME      PreventiveAlertZTHR
#define INPUT_8_WIDTH       1
#define INPUT_DIMS_8_COL    1
#define INPUT_8_DTYPE       real_T
#define INPUT_8_COMPLEX     COMPLEX_NO
#define IN_8_FRAME_BASED    FRAME_NO
#define IN_8_BUS_BASED      0
#define IN_8_BUS_NAME       
#define IN_8_DIMS           1-D
#define INPUT_8_FEEDTHROUGH 1
#define IN_8_ISSIGNED        0
#define IN_8_WORDLENGTH      8
#define IN_8_FIXPOINTSCALING 1
#define IN_8_FRACTIONLENGTH  9
#define IN_8_BIAS            0
#define IN_8_SLOPE           0.125
/* Input Port  9 */
#define IN_PORT_9_NAME      PreventiveAlertTTHR
#define INPUT_9_WIDTH       1
#define INPUT_DIMS_9_COL    1
#define INPUT_9_DTYPE       real_T
#define INPUT_9_COMPLEX     COMPLEX_NO
#define IN_9_FRAME_BASED    FRAME_NO
#define IN_9_BUS_BASED      0
#define IN_9_BUS_NAME       
#define IN_9_DIMS           1-D
#define INPUT_9_FEEDTHROUGH 1
#define IN_9_ISSIGNED        0
#define IN_9_WORDLENGTH      8
#define IN_9_FIXPOINTSCALING 1
#define IN_9_FRACTIONLENGTH  9
#define IN_9_BIAS            0
#define IN_9_SLOPE           0.125
/* Input Port  10 */
#define IN_PORT_10_NAME      PreventiveAlertTCOA
#define INPUT_10_WIDTH       1
#define INPUT_DIMS_10_COL    1
#define INPUT_10_DTYPE       real_T
#define INPUT_10_COMPLEX     COMPLEX_NO
#define IN_10_FRAME_BASED    FRAME_NO
#define IN_10_BUS_BASED      0
#define IN_10_BUS_NAME       
#define IN_10_DIMS           1-D
#define INPUT_10_FEEDTHROUGH 1
#define IN_10_ISSIGNED        0
#define IN_10_WORDLENGTH      8
#define IN_10_FIXPOINTSCALING 1
#define IN_10_FRACTIONLENGTH  9
#define IN_10_BIAS            0
#define IN_10_SLOPE           0.125
/* Input Port  11 */
#define IN_PORT_11_NAME      PreventiveAlertLookahead
#define INPUT_11_WIDTH       1
#define INPUT_DIMS_11_COL    1
#define INPUT_11_DTYPE       real_T
#define INPUT_11_COMPLEX     COMPLEX_NO
#define IN_11_FRAME_BASED    FRAME_NO
#define IN_11_BUS_BASED      0
#define IN_11_BUS_NAME       
#define IN_11_DIMS           1-D
#define INPUT_11_FEEDTHROUGH 1
#define IN_11_ISSIGNED        0
#define IN_11_WORDLENGTH      8
#define IN_11_FIXPOINTSCALING 1
#define IN_11_FRACTIONLENGTH  9
#define IN_11_BIAS            0
#define IN_11_SLOPE           0.125
/* Input Port  12 */
#define IN_PORT_12_NAME      CorrectiveAlertDTHR
#define INPUT_12_WIDTH       1
#define INPUT_DIMS_12_COL    1
#define INPUT_12_DTYPE       real_T
#define INPUT_12_COMPLEX     COMPLEX_NO
#define IN_12_FRAME_BASED    FRAME_NO
#define IN_12_BUS_BASED      0
#define IN_12_BUS_NAME       
#define IN_12_DIMS           1-D
#define INPUT_12_FEEDTHROUGH 1
#define IN_12_ISSIGNED        0
#define IN_12_WORDLENGTH      8
#define IN_12_FIXPOINTSCALING 1
#define IN_12_FRACTIONLENGTH  9
#define IN_12_BIAS            0
#define IN_12_SLOPE           0.125
/* Input Port  13 */
#define IN_PORT_13_NAME      CorrectiveAlertZTHR
#define INPUT_13_WIDTH       1
#define INPUT_DIMS_13_COL    1
#define INPUT_13_DTYPE       real_T
#define INPUT_13_COMPLEX     COMPLEX_NO
#define IN_13_FRAME_BASED    FRAME_NO
#define IN_13_BUS_BASED      0
#define IN_13_BUS_NAME       
#define IN_13_DIMS           1-D
#define INPUT_13_FEEDTHROUGH 1
#define IN_13_ISSIGNED        0
#define IN_13_WORDLENGTH      8
#define IN_13_FIXPOINTSCALING 1
#define IN_13_FRACTIONLENGTH  9
#define IN_13_BIAS            0
#define IN_13_SLOPE           0.125
/* Input Port  14 */
#define IN_PORT_14_NAME      CorrectiveAlertTTHR
#define INPUT_14_WIDTH       1
#define INPUT_DIMS_14_COL    1
#define INPUT_14_DTYPE       real_T
#define INPUT_14_COMPLEX     COMPLEX_NO
#define IN_14_FRAME_BASED    FRAME_NO
#define IN_14_BUS_BASED      0
#define IN_14_BUS_NAME       
#define IN_14_DIMS           1-D
#define INPUT_14_FEEDTHROUGH 1
#define IN_14_ISSIGNED        0
#define IN_14_WORDLENGTH      8
#define IN_14_FIXPOINTSCALING 1
#define IN_14_FRACTIONLENGTH  9
#define IN_14_BIAS            0
#define IN_14_SLOPE           0.125
/* Input Port  15 */
#define IN_PORT_15_NAME      CorrectiveAlertTCOA
#define INPUT_15_WIDTH       1
#define INPUT_DIMS_15_COL    1
#define INPUT_15_DTYPE       real_T
#define INPUT_15_COMPLEX     COMPLEX_NO
#define IN_15_FRAME_BASED    FRAME_NO
#define IN_15_BUS_BASED      0
#define IN_15_BUS_NAME       
#define IN_15_DIMS           1-D
#define INPUT_15_FEEDTHROUGH 1
#define IN_15_ISSIGNED        0
#define IN_15_WORDLENGTH      8
#define IN_15_FIXPOINTSCALING 1
#define IN_15_FRACTIONLENGTH  9
#define IN_15_BIAS            0
#define IN_15_SLOPE           0.125
/* Input Port  16 */
#define IN_PORT_16_NAME      CorrectiveAlertLookahead
#define INPUT_16_WIDTH       1
#define INPUT_DIMS_16_COL    1
#define INPUT_16_DTYPE       real_T
#define INPUT_16_COMPLEX     COMPLEX_NO
#define IN_16_FRAME_BASED    FRAME_NO
#define IN_16_BUS_BASED      0
#define IN_16_BUS_NAME       
#define IN_16_DIMS           1-D
#define INPUT_16_FEEDTHROUGH 1
#define IN_16_ISSIGNED        0
#define IN_16_WORDLENGTH      8
#define IN_16_FIXPOINTSCALING 1
#define IN_16_FRACTIONLENGTH  9
#define IN_16_BIAS            0
#define IN_16_SLOPE           0.125
/* Input Port  17 */
#define IN_PORT_17_NAME      WarningAlertDTHR
#define INPUT_17_WIDTH       1
#define INPUT_DIMS_17_COL    1
#define INPUT_17_DTYPE       real_T
#define INPUT_17_COMPLEX     COMPLEX_NO
#define IN_17_FRAME_BASED    FRAME_NO
#define IN_17_BUS_BASED      0
#define IN_17_BUS_NAME       
#define IN_17_DIMS           1-D
#define INPUT_17_FEEDTHROUGH 1
#define IN_17_ISSIGNED        0
#define IN_17_WORDLENGTH      8
#define IN_17_FIXPOINTSCALING 1
#define IN_17_FRACTIONLENGTH  9
#define IN_17_BIAS            0
#define IN_17_SLOPE           0.125
/* Input Port  18 */
#define IN_PORT_18_NAME      WarningAlertZTHR
#define INPUT_18_WIDTH       1
#define INPUT_DIMS_18_COL    1
#define INPUT_18_DTYPE       real_T
#define INPUT_18_COMPLEX     COMPLEX_NO
#define IN_18_FRAME_BASED    FRAME_NO
#define IN_18_BUS_BASED      0
#define IN_18_BUS_NAME       
#define IN_18_DIMS           1-D
#define INPUT_18_FEEDTHROUGH 1
#define IN_18_ISSIGNED        0
#define IN_18_WORDLENGTH      8
#define IN_18_FIXPOINTSCALING 1
#define IN_18_FRACTIONLENGTH  9
#define IN_18_BIAS            0
#define IN_18_SLOPE           0.125
/* Input Port  19 */
#define IN_PORT_19_NAME      WarningAlertTTHR
#define INPUT_19_WIDTH       1
#define INPUT_DIMS_19_COL    1
#define INPUT_19_DTYPE       real_T
#define INPUT_19_COMPLEX     COMPLEX_NO
#define IN_19_FRAME_BASED    FRAME_NO
#define IN_19_BUS_BASED      0
#define IN_19_BUS_NAME       
#define IN_19_DIMS           1-D
#define INPUT_19_FEEDTHROUGH 1
#define IN_19_ISSIGNED        0
#define IN_19_WORDLENGTH      8
#define IN_19_FIXPOINTSCALING 1
#define IN_19_FRACTIONLENGTH  9
#define IN_19_BIAS            0
#define IN_19_SLOPE           0.125
/* Input Port  20 */
#define IN_PORT_20_NAME      WarningAlertTCOA
#define INPUT_20_WIDTH       1
#define INPUT_DIMS_20_COL    1
#define INPUT_20_DTYPE       real_T
#define INPUT_20_COMPLEX     COMPLEX_NO
#define IN_20_FRAME_BASED    FRAME_NO
#define IN_20_BUS_BASED      0
#define IN_20_BUS_NAME       
#define IN_20_DIMS           1-D
#define INPUT_20_FEEDTHROUGH 1
#define IN_20_ISSIGNED        0
#define IN_20_WORDLENGTH      8
#define IN_20_FIXPOINTSCALING 1
#define IN_20_FRACTIONLENGTH  9
#define IN_20_BIAS            0
#define IN_20_SLOPE           0.125
/* Input Port  21 */
#define IN_PORT_21_NAME      WarningAlertLookahead
#define INPUT_21_WIDTH       1
#define INPUT_DIMS_21_COL    1
#define INPUT_21_DTYPE       real_T
#define INPUT_21_COMPLEX     COMPLEX_NO
#define IN_21_FRAME_BASED    FRAME_NO
#define IN_21_BUS_BASED      0
#define IN_21_BUS_NAME       
#define IN_21_DIMS           1-D
#define INPUT_21_FEEDTHROUGH 1
#define IN_21_ISSIGNED        0
#define IN_21_WORDLENGTH      8
#define IN_21_FIXPOINTSCALING 1
#define IN_21_FRACTIONLENGTH  9
#define IN_21_BIAS            0
#define IN_21_SLOPE           0.125
/* Input Port  22 */
#define IN_PORT_22_NAME      TurnRate
#define INPUT_22_WIDTH       1
#define INPUT_DIMS_22_COL    1
#define INPUT_22_DTYPE       real_T
#define INPUT_22_COMPLEX     COMPLEX_NO
#define IN_22_FRAME_BASED    FRAME_NO
#define IN_22_BUS_BASED      0
#define IN_22_BUS_NAME       
#define IN_22_DIMS           1-D
#define INPUT_22_FEEDTHROUGH 1
#define IN_22_ISSIGNED        0
#define IN_22_WORDLENGTH      8
#define IN_22_FIXPOINTSCALING 1
#define IN_22_FRACTIONLENGTH  9
#define IN_22_BIAS            0
#define IN_22_SLOPE           0.125
/* Input Port  23 */
#define IN_PORT_23_NAME      VerticalRate
#define INPUT_23_WIDTH       1
#define INPUT_DIMS_23_COL    1
#define INPUT_23_DTYPE       real_T
#define INPUT_23_COMPLEX     COMPLEX_NO
#define IN_23_FRAME_BASED    FRAME_NO
#define IN_23_BUS_BASED      0
#define IN_23_BUS_NAME       
#define IN_23_DIMS           1-D
#define INPUT_23_FEEDTHROUGH 1
#define IN_23_ISSIGNED        0
#define IN_23_WORDLENGTH      8
#define IN_23_FIXPOINTSCALING 1
#define IN_23_FRACTIONLENGTH  9
#define IN_23_BIAS            0
#define IN_23_SLOPE           0.125
/* Input Port  24 */
#define IN_PORT_24_NAME      PrevEarly
#define INPUT_24_WIDTH       1
#define INPUT_DIMS_24_COL    1
#define INPUT_24_DTYPE       real_T
#define INPUT_24_COMPLEX     COMPLEX_NO
#define IN_24_FRAME_BASED    FRAME_NO
#define IN_24_BUS_BASED      0
#define IN_24_BUS_NAME       
#define IN_24_DIMS           1-D
#define INPUT_24_FEEDTHROUGH 1
#define IN_24_ISSIGNED        0
#define IN_24_WORDLENGTH      8
#define IN_24_FIXPOINTSCALING 1
#define IN_24_FRACTIONLENGTH  9
#define IN_24_BIAS            0
#define IN_24_SLOPE           0.125
/* Input Port  25 */
#define IN_PORT_25_NAME      CorrEarly
#define INPUT_25_WIDTH       1
#define INPUT_DIMS_25_COL    1
#define INPUT_25_DTYPE       real_T
#define INPUT_25_COMPLEX     COMPLEX_NO
#define IN_25_FRAME_BASED    FRAME_NO
#define IN_25_BUS_BASED      0
#define IN_25_BUS_NAME       
#define IN_25_DIMS           1-D
#define INPUT_25_FEEDTHROUGH 1
#define IN_25_ISSIGNED        0
#define IN_25_WORDLENGTH      8
#define IN_25_FIXPOINTSCALING 1
#define IN_25_FRACTIONLENGTH  9
#define IN_25_BIAS            0
#define IN_25_SLOPE           0.125
/* Input Port  26 */
#define IN_PORT_26_NAME      WarnEarly
#define INPUT_26_WIDTH       1
#define INPUT_DIMS_26_COL    1
#define INPUT_26_DTYPE       real_T
#define INPUT_26_COMPLEX     COMPLEX_NO
#define IN_26_FRAME_BASED    FRAME_NO
#define IN_26_BUS_BASED      0
#define IN_26_BUS_NAME       
#define IN_26_DIMS           1-D
#define INPUT_26_FEEDTHROUGH 1
#define IN_26_ISSIGNED        0
#define IN_26_WORDLENGTH      8
#define IN_26_FIXPOINTSCALING 1
#define IN_26_FRACTIONLENGTH  9
#define IN_26_BIAS            0
#define IN_26_SLOPE           0.125
/* Input Port  27 */
#define IN_PORT_27_NAME      MinimumAltitude
#define INPUT_27_WIDTH       1
#define INPUT_DIMS_27_COL    1
#define INPUT_27_DTYPE       real_T
#define INPUT_27_COMPLEX     COMPLEX_NO
#define IN_27_FRAME_BASED    FRAME_NO
#define IN_27_BUS_BASED      0
#define IN_27_BUS_NAME       
#define IN_27_DIMS           1-D
#define INPUT_27_FEEDTHROUGH 1
#define IN_27_ISSIGNED        0
#define IN_27_WORDLENGTH      8
#define IN_27_FIXPOINTSCALING 1
#define IN_27_FRACTIONLENGTH  9
#define IN_27_BIAS            0
#define IN_27_SLOPE           0.125
/* Input Port  28 */
#define IN_PORT_28_NAME      RecoveryStabilityTime
#define INPUT_28_WIDTH       1
#define INPUT_DIMS_28_COL    1
#define INPUT_28_DTYPE       real_T
#define INPUT_28_COMPLEX     COMPLEX_NO
#define IN_28_FRAME_BASED    FRAME_NO
#define IN_28_BUS_BASED      0
#define IN_28_BUS_NAME       
#define IN_28_DIMS           1-D
#define INPUT_28_FEEDTHROUGH 1
#define IN_28_ISSIGNED        0
#define IN_28_WORDLENGTH      8
#define IN_28_FIXPOINTSCALING 1
#define IN_28_FRACTIONLENGTH  9
#define IN_28_BIAS            0
#define IN_28_SLOPE           0.125
/* Input Port  29 */
#define IN_PORT_29_NAME      MinimumHorizontalRecovery
#define INPUT_29_WIDTH       1
#define INPUT_DIMS_29_COL    1
#define INPUT_29_DTYPE       real_T
#define INPUT_29_COMPLEX     COMPLEX_NO
#define IN_29_FRAME_BASED    FRAME_NO
#define IN_29_BUS_BASED      0
#define IN_29_BUS_NAME       
#define IN_29_DIMS           1-D
#define INPUT_29_FEEDTHROUGH 1
#define IN_29_ISSIGNED        0
#define IN_29_WORDLENGTH      8
#define IN_29_FIXPOINTSCALING 1
#define IN_29_FRACTIONLENGTH  9
#define IN_29_BIAS            0
#define IN_29_SLOPE           0.125
/* Input Port  30 */
#define IN_PORT_30_NAME      CAFactor
#define INPUT_30_WIDTH       1
#define INPUT_DIMS_30_COL    1
#define INPUT_30_DTYPE       real_T
#define INPUT_30_COMPLEX     COMPLEX_NO
#define IN_30_FRAME_BASED    FRAME_NO
#define IN_30_BUS_BASED      0
#define IN_30_BUS_NAME       
#define IN_30_DIMS           1-D
#define INPUT_30_FEEDTHROUGH 1
#define IN_30_ISSIGNED        0
#define IN_30_WORDLENGTH      8
#define IN_30_FIXPOINTSCALING 1
#define IN_30_FRACTIONLENGTH  9
#define IN_30_BIAS            0
#define IN_30_SLOPE           0.125

#define NUM_OUTPUTS          5
/* Output Port  0 */
#define OUT_PORT_0_NAME      StatusFlag
#define OUTPUT_0_WIDTH       1
#define OUTPUT_DIMS_0_COL    1
#define OUTPUT_0_DTYPE       real_T
#define OUTPUT_0_COMPLEX     COMPLEX_NO
#define OUT_0_FRAME_BASED    FRAME_NO
#define OUT_0_BUS_BASED      0
#define OUT_0_BUS_NAME       
#define OUT_0_DIMS           1-D
#define OUT_0_ISSIGNED        1
#define OUT_0_WORDLENGTH      8
#define OUT_0_FIXPOINTSCALING 1
#define OUT_0_FRACTIONLENGTH  3
#define OUT_0_BIAS            0
#define OUT_0_SLOPE           0.125
/* Output Port  1 */
#define OUT_PORT_1_NAME      AlertLevel
#define OUTPUT_1_WIDTH       1
#define OUTPUT_DIMS_1_COL    1
#define OUTPUT_1_DTYPE       real_T
#define OUTPUT_1_COMPLEX     COMPLEX_NO
#define OUT_1_FRAME_BASED    FRAME_NO
#define OUT_1_BUS_BASED      0
#define OUT_1_BUS_NAME       
#define OUT_1_DIMS           1-D
#define OUT_1_ISSIGNED        1
#define OUT_1_WORDLENGTH      8
#define OUT_1_FIXPOINTSCALING 1
#define OUT_1_FRACTIONLENGTH  3
#define OUT_1_BIAS            0
#define OUT_1_SLOPE           0.125
/* Output Port  2 */
#define OUT_PORT_2_NAME      Bands
#define OUTPUT_2_WIDTH       311
#define OUTPUT_DIMS_2_COL    1
#define OUTPUT_2_DTYPE       real_T
#define OUTPUT_2_COMPLEX     COMPLEX_NO
#define OUT_2_FRAME_BASED    FRAME_NO
#define OUT_2_BUS_BASED      0
#define OUT_2_BUS_NAME       
#define OUT_2_DIMS           1-D
#define OUT_2_ISSIGNED        1
#define OUT_2_WORDLENGTH      8
#define OUT_2_FIXPOINTSCALING 1
#define OUT_2_FRACTIONLENGTH  3
#define OUT_2_BIAS            0
#define OUT_2_SLOPE           0.125

#define NPARAMS              0

#define SAMPLE_TIME_0        INHERITED_SAMPLE_TIME
#define NUM_DISC_STATES      0
#define DISC_STATES_IC       [0,0]
#define NUM_CONT_STATES      0
#define CONT_STATES_IC       [0]

#define SFUNWIZ_GENERATE_TLC 1
#define SOURCEFILES "__SFB__DaidalusInterface.cpp"
#define PANELINDEX           6
#define USE_SIMSTRUCT        0
#define SHOW_COMPILE_STEPS   0                   
#define CREATE_DEBUG_MEXFILE 0
#define SAVE_CODE_ONLY       0
#define SFUNWIZ_REVISION     3.0

#include "simstruc.h"
#include <stdlib.h>
#include <string.h>

#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

#include "interf_daidalus.h"
#define u_width 6
#define y_width 1

void sfnc_daidalus_Outputs_wrapper(const real_T *OwnshipStateVector,
                          const real_T *IntruderStateVector,
                          const real_T *DTHR,
                          const real_T *ZTHR,
                          const real_T *TTHR,
                          const real_T *TCOA,
                          const real_T *Look,
                          const real_T *prevDTHR,
                          const real_T *prevZTHR,
                          const real_T *prevTTHR,
                          const real_T *prevTCOA,
                          const real_T *prevLook,
                          const real_T *prevEarly,
                          const real_T *corrDTHR,
                          const real_T *corrZTHR,
                          const real_T *corrTTHR,
                          const real_T *corrTCOA,
                          const real_T *corrLook,
                          const real_T *corrEarly,
                          const real_T *warnDTHR,
                          const real_T *warnZTHR,
                          const real_T *warnTTHR,
                          const real_T *warnTCOA,
                          const real_T *warnLook,
                          const real_T *warnEarly,
                          const real_T *TurnRate,
                          const real_T *VertRate,
                          real_T *StatusFlag,
                          real_T *AlertLvl,
                          real_T *Bands,
                          real_T *recoverRight,
                          real_T *recoverUp,
                          const real_T *MinimumAltitude,
                          const real_T *RecoveryStabilityTime,
                          const real_T *MinimumHorizontalRecovery,
                          const real_T *CAFactor)
{
    
    int* bandsOut = new int[312];
    int recovRgt;
    int recovUp;
    
    *StatusFlag = getDaidalusBands( (double*) OwnshipStateVector, 
                                    (double*) IntruderStateVector, 
                                    (double*) DTHR, 
                                    (double*) ZTHR, 
                                    (double*) TTHR, 
                                    (double*) TCOA,
                                    (double*) Look,
                                    (double*) prevDTHR, 
                                    (double*) prevZTHR, 
                                    (double*) prevTTHR, 
                                    (double*) prevTCOA,
                                    (double*) prevLook,
                                    (double*) prevEarly,
                                    (double*) corrDTHR, 
                                    (double*) corrZTHR, 
                                    (double*) corrTTHR, 
                                    (double*) corrTCOA,
                                    (double*) corrLook,
                                    (double*) corrEarly,
                                    (double*) warnDTHR, 
                                    (double*) warnZTHR, 
                                    (double*) warnTTHR, 
                                    (double*) warnTCOA,
                                    (double*) warnLook,
                                    (double*) warnEarly,
                                    (double*) TurnRate,
                                    (double*) VertRate,
                                    bandsOut,
                                    &recovRgt,
                                    &recovUp,
                                    (double*) MinimumAltitude,
                                    (double*) RecoveryStabilityTime,
                                    (double*) MinimumHorizontalRecovery,
                                    (double*) CAFactor);

    *AlertLvl = static_cast<real_T>(bandsOut[0]);
    for (int i=1; i<312; i++) {
        Bands[i-1] = static_cast<real_T>(bandsOut[i]);
    }
    
    *recoverRight = static_cast<real_T>(recovRgt);
    *recoverUp = static_cast<real_T>(recovUp);
    
    delete [] bandsOut;

}


static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, NPARAMS);
     if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
     return; /* Parameter mismatch will be reported by Simulink */
     }

    ssSetNumContStates(S, NUM_CONT_STATES);
    ssSetNumDiscStates(S, NUM_DISC_STATES);

    if (!ssSetNumInputPorts(S, NUM_INPUTS)) return;
    /*Input Port 0 */
    ssSetInputPortWidth(S,  0, INPUT_0_WIDTH); /* */
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  0, INPUT_0_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 0, INPUT_0_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/

    /*Input Port 1 */
    ssSetInputPortWidth(S,  1, INPUT_1_WIDTH); /* */
    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  1, INPUT_1_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 1, INPUT_1_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/

    /*Input Port 2 */
    ssSetInputPortWidth(S,  2, INPUT_2_WIDTH); /* */
    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  2, INPUT_2_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 2, INPUT_2_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/

    /*Input Port 3 */
    ssSetInputPortWidth(S,  3, INPUT_3_WIDTH); /* */
    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  3, INPUT_3_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 3, INPUT_3_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/

    /*Input Port 4 */
    ssSetInputPortWidth(S,  4, INPUT_4_WIDTH); /* */
    ssSetInputPortDataType(S, 4, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  4, INPUT_4_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 4, INPUT_4_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 4, 1); /*direct input signal access*/

    /*Input Port 5 */
    ssSetInputPortWidth(S,  5, INPUT_5_WIDTH); /* */
    ssSetInputPortDataType(S, 5, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  5, INPUT_5_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 5, INPUT_5_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 5, 1); /*direct input signal access*/

    /*Input Port 6 */
    ssSetInputPortWidth(S,  6, INPUT_6_WIDTH); /* */
    ssSetInputPortDataType(S, 6, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  6, INPUT_6_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 6, INPUT_6_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 6, 1); /*direct input signal access*/

    /*Input Port 7 */
    ssSetInputPortWidth(S,  7, INPUT_7_WIDTH); /* */
    ssSetInputPortDataType(S, 7, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  7, INPUT_7_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 7, INPUT_7_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 7, 1); /*direct input signal access*/

    /*Input Port 8 */
    ssSetInputPortWidth(S,  8, INPUT_8_WIDTH); /* */
    ssSetInputPortDataType(S, 8, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  8, INPUT_8_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 8, INPUT_8_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 8, 1); /*direct input signal access*/

    /*Input Port 9 */
    ssSetInputPortWidth(S,  9, INPUT_9_WIDTH); /* */
    ssSetInputPortDataType(S, 9, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  9, INPUT_9_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 9, INPUT_9_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 9, 1); /*direct input signal access*/

    /*Input Port 10 */
    ssSetInputPortWidth(S,  10, INPUT_10_WIDTH); /* */
    ssSetInputPortDataType(S, 10, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  10, INPUT_10_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 10, INPUT_10_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 10, 1); /*direct input signal access*/

    /*Input Port 11 */
    ssSetInputPortWidth(S,  11, INPUT_11_WIDTH); /* */
    ssSetInputPortDataType(S, 11, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  11, INPUT_11_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 11, INPUT_11_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 11, 1); /*direct input signal access*/

    /*Input Port 12 */
    ssSetInputPortWidth(S,  12, INPUT_12_WIDTH); /* */
    ssSetInputPortDataType(S, 12, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  12, INPUT_12_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 12, INPUT_12_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 12, 1); /*direct input signal access*/

    /*Input Port 13 */
    ssSetInputPortWidth(S,  13, INPUT_13_WIDTH); /* */
    ssSetInputPortDataType(S, 13, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  13, INPUT_13_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 13, INPUT_13_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 13, 1); /*direct input signal access*/

    /*Input Port 14 */
    ssSetInputPortWidth(S,  14, INPUT_14_WIDTH); /* */
    ssSetInputPortDataType(S, 14, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  14, INPUT_14_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 14, INPUT_14_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 14, 1); /*direct input signal access*/

    /*Input Port 15 */
    ssSetInputPortWidth(S,  15, INPUT_15_WIDTH); /* */
    ssSetInputPortDataType(S, 15, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  15, INPUT_15_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 15, INPUT_15_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 15, 1); /*direct input signal access*/

    /*Input Port 16 */
    ssSetInputPortWidth(S,  16, INPUT_16_WIDTH); /* */
    ssSetInputPortDataType(S, 16, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  16, INPUT_16_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 16, INPUT_16_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 16, 1); /*direct input signal access*/

    /*Input Port 17 */
    ssSetInputPortWidth(S,  17, INPUT_17_WIDTH); /* */
    ssSetInputPortDataType(S, 17, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  17, INPUT_17_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 17, INPUT_17_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 17, 1); /*direct input signal access*/

    /*Input Port 18 */
    ssSetInputPortWidth(S,  18, INPUT_18_WIDTH); /* */
    ssSetInputPortDataType(S, 18, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  18, INPUT_18_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 18, INPUT_18_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 18, 1); /*direct input signal access*/

    /*Input Port 19 */
    ssSetInputPortWidth(S,  19, INPUT_19_WIDTH); /* */
    ssSetInputPortDataType(S, 19, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  19, INPUT_19_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 19, INPUT_19_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 19, 1); /*direct input signal access*/

    /*Input Port 20 */
    ssSetInputPortWidth(S,  20, INPUT_20_WIDTH); /* */
    ssSetInputPortDataType(S, 20, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  20, INPUT_20_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 20, INPUT_20_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 20, 1); /*direct input signal access*/

    /*Input Port 21 */
    ssSetInputPortWidth(S,  21, INPUT_21_WIDTH); /* */
    ssSetInputPortDataType(S, 21, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  21, INPUT_21_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 21, INPUT_21_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 21, 1); /*direct input signal access*/

    /*Input Port 22 */
    ssSetInputPortWidth(S,  22, INPUT_22_WIDTH); /* */
    ssSetInputPortDataType(S, 22, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  22, INPUT_22_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 22, INPUT_22_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 22, 1); /*direct input signal access*/

    /*Input Port 23 */
    ssSetInputPortWidth(S,  23, INPUT_23_WIDTH); /* */
    ssSetInputPortDataType(S, 23, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  23, INPUT_23_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 23, INPUT_23_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 23, 1); /*direct input signal access*/

    /*Input Port 24 */
    ssSetInputPortWidth(S,  24, INPUT_24_WIDTH); /* */
    ssSetInputPortDataType(S, 24, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  24, INPUT_24_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 24, INPUT_24_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 24, 1); /*direct input signal access*/

    /*Input Port 25 */
    ssSetInputPortWidth(S,  25, INPUT_25_WIDTH); /* */
    ssSetInputPortDataType(S, 25, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  25, INPUT_25_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 25, INPUT_25_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 25, 1); /*direct input signal access*/

    /*Input Port 26 */
    ssSetInputPortWidth(S,  26, INPUT_26_WIDTH); /* */
    ssSetInputPortDataType(S, 26, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  26, INPUT_26_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 26, INPUT_26_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 26, 1); /*direct input signal access*/

    /*Input Port 27 */
    ssSetInputPortWidth(S,  27, INPUT_27_WIDTH); /* */
    ssSetInputPortDataType(S, 27, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  27, INPUT_27_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 27, INPUT_27_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 27, 1); /*direct input signal access*/

    /*Input Port 28 */
    ssSetInputPortWidth(S,  28, INPUT_28_WIDTH); /* */
    ssSetInputPortDataType(S, 28, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  28, INPUT_28_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 28, INPUT_28_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 28, 1); /*direct input signal access*/

    /*Input Port 29 */
    ssSetInputPortWidth(S,  29, INPUT_29_WIDTH); /* */
    ssSetInputPortDataType(S, 29, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  29, INPUT_29_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 29, INPUT_29_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 29, 1); /*direct input signal access*/

    /*Input Port 30 */
    ssSetInputPortWidth(S,  30, INPUT_30_WIDTH); /* */
    ssSetInputPortDataType(S, 30, SS_DOUBLE);
    ssSetInputPortComplexSignal(S,  30, INPUT_30_COMPLEX);
    ssSetInputPortDirectFeedThrough(S, 30, INPUT_30_FEEDTHROUGH);
    ssSetInputPortRequiredContiguous(S, 30, 1); /*direct input signal access*/                


    if (!ssSetNumOutputPorts(S, NUM_OUTPUTS)) return;
    /*Output Port 0 */
    ssSetOutputPortWidth(S, 0, OUTPUT_0_WIDTH);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, OUTPUT_0_COMPLEX);
    /*Output Port 1 */
    ssSetOutputPortWidth(S, 1, OUTPUT_1_WIDTH);
    ssSetOutputPortDataType(S, 1, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 1, OUTPUT_1_COMPLEX);
    /*Output Port 2 */
    outputDimsInfo.width = OUTPUT_2_WIDTH;
    ssSetOutputPortDimensionInfo(S, 2, &outputDimsInfo);
    ssSetOutputPortMatrixDimensions( S ,2, OUTPUT_2_WIDTH, OUTPUT_DIMS_2_COL);
    ssSetOutputPortFrameData(S, 2, OUT_2_FRAME_BASED);
    ssSetOutputPortDataType(S, 2, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 2, OUTPUT_2_COMPLEX);
    /*Output Port 3 */
    ssSetOutputPortWidth(S, 3, OUTPUT_1_WIDTH);
    ssSetOutputPortDataType(S, 3, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 3, OUTPUT_1_COMPLEX);
    /*Output Port 4 */
    ssSetOutputPortWidth(S, 4, OUTPUT_1_WIDTH);
    ssSetOutputPortDataType(S, 4, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 4, OUTPUT_1_COMPLEX);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
    ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
                     SS_OPTION_USE_TLC_WITH_ACCELERATOR | 
             SS_OPTION_WORKS_WITH_CODE_REUSE));
}

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct        *S, 
                                         int_T            port,
                                         const DimsInfo_T *dimsInfo)
{
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO)
static void mdlSetOutputPortDimensionInfo(SimStruct        *S, 
                                          int_T            port, 
                                          const DimsInfo_T *dimsInfo)
{
 if (!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif
#define MDL_SET_DEFAULT_PORT_DIMENSION_INFO
static void mdlSetDefaultPortDimensionInfo(SimStruct *S)
{
  DECL_AND_INIT_DIMSINFO(portDimsInfo);
  int_T dims[2] = { INPUT_0_WIDTH, 1 };
  bool  frameIn = ssGetInputPortFrameData(S, 0) == FRAME_YES;

  /* Neither the input nor the output ports have been set */

  portDimsInfo.width   = INPUT_0_WIDTH;
  portDimsInfo.numDims = frameIn ? 2 : 1;
  portDimsInfo.dims    = frameIn ? dims : &portDimsInfo.width;
  if (ssGetInputPortNumDimensions(S, 0) == (-1)) {  
   ssSetInputPortDimensionInfo(S, 0, &portDimsInfo);
  }
  portDimsInfo.width   = OUTPUT_0_WIDTH;
  dims[0]              = OUTPUT_0_WIDTH;
  dims[1]              = 1;
  portDimsInfo.dims    = frameIn ? dims : &portDimsInfo.width;
 if (ssGetOutputPortNumDimensions(S, 0) == (-1)) {  
  ssSetOutputPortDimensionInfo(S, 0, &portDimsInfo);
 }
  return;
}
# define MDL_SET_INPUT_PORT_FRAME_DATA
static void mdlSetInputPortFrameData(SimStruct  *S, 
                                     int_T      port,
                                     Frame_T    frameData)
{
    ssSetInputPortFrameData(S, port, frameData);
}
/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, SAMPLE_TIME_0);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, int port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
  ssSetInputPortDataType( S, 0, SS_DOUBLE);
 ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}
/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const real_T   *OwnshipStateVector  = (const real_T*) ssGetInputPortSignal(S,0);
    const real_T   *IntruderStateVector  = (const real_T*) ssGetInputPortSignal(S,1);
    
    const real_T   *DTHR = (const real_T*) ssGetInputPortSignal(S,2);
    const real_T   *ZTHR = (const real_T*) ssGetInputPortSignal(S,3);
    const real_T   *TTHR = (const real_T*) ssGetInputPortSignal(S,4);
    const real_T   *TCOA = (const real_T*) ssGetInputPortSignal(S,5);
    const real_T   *Look = (const real_T*) ssGetInputPortSignal(S,6);

    const real_T   *prevDTHR = (const real_T*) ssGetInputPortSignal(S,7);
    const real_T   *prevZTHR = (const real_T*) ssGetInputPortSignal(S,8);
    const real_T   *prevTTHR = (const real_T*) ssGetInputPortSignal(S,9);
    const real_T   *prevTCOA = (const real_T*) ssGetInputPortSignal(S,10);
    const real_T   *prevLook = (const real_T*) ssGetInputPortSignal(S,11);

    const real_T   *corrDTHR = (const real_T*) ssGetInputPortSignal(S,12);
    const real_T   *corrZTHR = (const real_T*) ssGetInputPortSignal(S,13);
    const real_T   *corrTTHR = (const real_T*) ssGetInputPortSignal(S,14);
    const real_T   *corrTCOA = (const real_T*) ssGetInputPortSignal(S,15);
    const real_T   *corrLook = (const real_T*) ssGetInputPortSignal(S,16);

    const real_T   *warnDTHR = (const real_T*) ssGetInputPortSignal(S,17);
    const real_T   *warnZTHR = (const real_T*) ssGetInputPortSignal(S,18);
    const real_T   *warnTTHR = (const real_T*) ssGetInputPortSignal(S,19);
    const real_T   *warnTCOA = (const real_T*) ssGetInputPortSignal(S,20);
    const real_T   *warnLook = (const real_T*) ssGetInputPortSignal(S,21);

    const real_T   *TurnRate = (const real_T*) ssGetInputPortSignal(S,22);
    const real_T   *VertRate = (const real_T*) ssGetInputPortSignal(S,23);

    const real_T   *prevEarly = (const real_T*) ssGetInputPortSignal(S,24);
    const real_T   *corrEarly = (const real_T*) ssGetInputPortSignal(S,25);
    const real_T   *warnEarly = (const real_T*) ssGetInputPortSignal(S,26);

    real_T        *StatusFlag  = (real_T *)ssGetOutputPortRealSignal(S,0);
    real_T        *Bands  = (real_T *)ssGetOutputPortRealSignal(S,1);
    real_T        *AlertLvl  = (real_T *)ssGetOutputPortRealSignal(S,2);
    real_T        *recoverRight = (real_T *)ssGetOutputPortRealSignal(S,3);
    real_T        *recoverUp = (real_T *)ssGetOutputPortRealSignal(S,4);

    const real_T    *MinimumAltitude = (const real_T*) ssGetInputPortSignal(S,27);
    const real_T    *RecoveryStabilityTime = (const real_T*) ssGetInputPortSignal(S,28);
    const real_T	*MinimumHorizontalRecovery = (const real_T*) ssGetInputPortSignal(S,29);
    const real_T	*CAFactor = (const real_T*) ssGetInputPortSignal(S,30);

    sfnc_daidalus_Outputs_wrapper(OwnshipStateVector, 
                                  IntruderStateVector, 
                                  DTHR, 
                                  ZTHR, 
                                  TTHR, 
                                  TCOA, 
                                  Look,
                                  prevDTHR, 
                                  prevZTHR, 
                                  prevTTHR, 
                                  prevTCOA, 
                                  prevLook,
                                  prevEarly,
                                  corrDTHR, 
                                  corrZTHR, 
                                  corrTTHR, 
                                  corrTCOA, 
                                  corrLook,
                                  corrEarly,
                                  warnDTHR, 
                                  warnZTHR, 
                                  warnTTHR, 
                                  warnTCOA, 
                                  warnLook,
                                  warnEarly,
                                  TurnRate,
                                  VertRate,
                                  StatusFlag, 
                                  Bands,
                                  AlertLvl,
                                  recoverRight,
                                  recoverUp,
                                  MinimumAltitude,
                                  RecoveryStabilityTime,
                                  MinimumHorizontalRecovery,
                                  CAFactor);

}

/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif



