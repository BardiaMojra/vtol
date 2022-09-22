/*
 * dp.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "dp".
 *
 * Model version              : 2.2
 * Simulink Coder version : 9.8 (R2022b) 13-May-2022
 * C source code generated on : Thu Sep 22 10:40:08 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_dp_h_
#define RTW_HEADER_dp_h_
#ifndef dp_COMMON_INCLUDES_
#define dp_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "nesl_rtw_rtp.h"
#include "dp_a151ee3d_1_gateway.h"
#include "nesl_rtw.h"
#endif                                 /* dp_COMMON_INCLUDES_ */

#include "dp_types.h"
#include <float.h>
#include <string.h>
#include <stddef.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
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

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T RTP_1;                        /* '<S7>/RTP_1' */
  real_T STATE_1[4];                   /* '<S14>/STATE_1' */
  real_T OUTPUT_1_0[6];                /* '<S14>/OUTPUT_1_0' */
} B_dp_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
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
} DW_dp_T;

/* Continuous states (default storage) */
typedef struct {
  real_T dpJ1Rzq[4];                   /* '<S14>/STATE_1' */
} X_dp_T;

/* State derivatives (default storage) */
typedef struct {
  real_T dpJ1Rzq[4];                   /* '<S14>/STATE_1' */
} XDot_dp_T;

/* State disabled  */
typedef struct {
  boolean_T dpJ1Rzq[4];                /* '<S14>/STATE_1' */
} XDis_dp_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_dp_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_dp_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_dp_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[4];
  real_T odeF[3][4];
  ODE3_IntgData intgData;

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
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_dp_T dp_B;

/* Continuous states (default storage) */
extern X_dp_T dp_X;

/* Block states (default storage) */
extern DW_dp_T dp_DW;

/* Model entry point functions */
extern void dp_initialize(void);
extern void dp_step(void);
extern void dp_terminate(void);

/* Real-time Model object */
extern RT_MODEL_dp_T *const dp_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Constant' : Unused code path elimination
 * Block '<S8>/RESHAPE' : Reshape block reduction
 * Block '<S9>/RESHAPE' : Reshape block reduction
 * Block '<S10>/RESHAPE' : Reshape block reduction
 * Block '<S11>/RESHAPE' : Reshape block reduction
 * Block '<S12>/RESHAPE' : Reshape block reduction
 * Block '<S13>/RESHAPE' : Reshape block reduction
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
