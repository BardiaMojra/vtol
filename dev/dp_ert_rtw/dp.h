/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: dp.h
 *
 * Code generated for Simulink model 'dp'.
 *
 * Model version                  : 2.1
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Wed Sep 21 21:26:42 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_dp_h_
#define RTW_HEADER_dp_h_
#ifndef dp_COMMON_INCLUDES_
#define dp_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "nesl_rtw_rtp.h"
#include "dp_a151ee3d_1_gateway.h"
#include "nesl_rtw.h"
#endif                                 /* dp_COMMON_INCLUDES_ */

#include "rtw_modelmap.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm)         ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val)    ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef SS_UINT64
#define SS_UINT64                      17
#endif

#ifndef SS_INT64
#define SS_INT64                       18
#endif

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T STATE_1[4];                   /* '<S14>/STATE_1' */
  real_T RTP_1;                        /* '<S7>/RTP_1' */
  real_T STATE_1_Discrete;             /* '<S14>/STATE_1' */
  real_T OUTPUT_1_0_Discrete;          /* '<S14>/OUTPUT_1_0' */
  void* RTP_1_RtpManager;              /* '<S7>/RTP_1' */
  void* STATE_1_Simulator;             /* '<S14>/STATE_1' */
  void* STATE_1_SimData;               /* '<S14>/STATE_1' */
  void* STATE_1_DiagMgr;               /* '<S14>/STATE_1' */
  void* STATE_1_ZcLogger;              /* '<S14>/STATE_1' */
  void* STATE_1_TsInfo;                /* '<S14>/STATE_1' */
  void* OUTPUT_1_0_Simulator;          /* '<S14>/OUTPUT_1_0' */
  void* OUTPUT_1_0_SimData;            /* '<S14>/OUTPUT_1_0' */
  void* OUTPUT_1_0_DiagMgr;            /* '<S14>/OUTPUT_1_0' */
  void* OUTPUT_1_0_ZcLogger;           /* '<S14>/OUTPUT_1_0' */
  void* OUTPUT_1_0_TsInfo;             /* '<S14>/OUTPUT_1_0' */
  void* SINK_1_RtwLogger;              /* '<S14>/SINK_1' */
  void* SINK_1_RtwLogBuffer;           /* '<S14>/SINK_1' */
  void* SINK_1_RtwLogFcnManager;       /* '<S14>/SINK_1' */
  int_T STATE_1_Modes;                 /* '<S14>/STATE_1' */
  int_T OUTPUT_1_0_Modes;              /* '<S14>/OUTPUT_1_0' */
  boolean_T RTP_1_SetParametersNeeded; /* '<S7>/RTP_1' */
  boolean_T STATE_1_FirstOutput;       /* '<S14>/STATE_1' */
  boolean_T OUTPUT_1_0_FirstOutput;    /* '<S14>/OUTPUT_1_0' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T dpJ1Rzq[4];                   /* '<S14>/STATE_1' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T dpJ1Rzq[4];                   /* '<S14>/STATE_1' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T dpJ1Rzq[4];                /* '<S14>/STATE_1' */
} XDis;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[4];
  real_T odeF[3][4];
  ODE3_IntgData intgData;
  DW *dwork;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
    void* dataAddress[6];
    int32_T* vardimsAddress[6];
    RTWLoggingFcnPtr loggingPtrs[6];
  } DataMapInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Model entry point functions */
extern void dp_initialize(RT_MODEL *const rtM);
extern void dp_step(RT_MODEL *const rtM);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  dp_GetCAPIStaticMap(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S8>/RESHAPE' : Unused code path elimination
 * Block '<S9>/RESHAPE' : Unused code path elimination
 * Block '<S10>/RESHAPE' : Unused code path elimination
 * Block '<S11>/RESHAPE' : Unused code path elimination
 * Block '<Root>/L1_x' : Unused code path elimination
 * Block '<Root>/L1_y' : Unused code path elimination
 * Block '<S12>/RESHAPE' : Unused code path elimination
 * Block '<S13>/RESHAPE' : Unused code path elimination
 * Block '<Root>/L2_x' : Unused code path elimination
 * Block '<Root>/L2_y' : Unused code path elimination
 * Block '<Root>/th1' : Unused code path elimination
 * Block '<Root>/th2' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'dp'
 * '<S1>'   : 'dp/J1-th1'
 * '<S2>'   : 'dp/J2-th2'
 * '<S3>'   : 'dp/L1-x'
 * '<S4>'   : 'dp/L1-y'
 * '<S5>'   : 'dp/L2-x'
 * '<S6>'   : 'dp/L2-y'
 * '<S7>'   : 'dp/Solver Configuration'
 * '<S8>'   : 'dp/J1-th1/EVAL_KEY'
 * '<S9>'   : 'dp/J2-th2/EVAL_KEY'
 * '<S10>'  : 'dp/L1-x/EVAL_KEY'
 * '<S11>'  : 'dp/L1-y/EVAL_KEY'
 * '<S12>'  : 'dp/L2-x/EVAL_KEY'
 * '<S13>'  : 'dp/L2-y/EVAL_KEY'
 * '<S14>'  : 'dp/Solver Configuration/EVAL_KEY'
 */
#endif                                 /* RTW_HEADER_dp_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
