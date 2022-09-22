/*
 * dp.c
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

#include "dp.h"
#include "rtwtypes.h"
#include <stddef.h>
#include "dp_private.h"
#include <string.h>
#include "rt_nonfinite.h"

/* Block signals (default storage) */
B_dp_T dp_B;

/* Continuous states */
X_dp_T dp_X;

/* Block states (default storage) */
DW_dp_T dp_DW;

/* Real-time model */
static RT_MODEL_dp_T dp_M_;
RT_MODEL_dp_T *const dp_M = &dp_M_;

/* Projection for root system: '<Root>' */
void dp_projection(void)
{
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  real_T time;
  int_T tmp_0;
  boolean_T tmp;

  /* Projection for SimscapeExecutionBlock: '<S14>/STATE_1' */
  simulationData = (NeslSimulationData *)dp_DW.STATE_1_SimData;
  time = dp_M->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 4;
  simulationData->mData->mContStates.mX = &dp_X.dpJ1Rzq[0];
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &dp_DW.STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 0;
  simulationData->mData->mModeVector.mX = &dp_DW.STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(dp_M);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&dp_M->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&dp_M->solverInfo);
  tmp_0 = 0;
  simulationData->mData->mInputValues.mN = 0;
  simulationData->mData->mInputOffsets.mN = 1;
  simulationData->mData->mInputOffsets.mX = &tmp_0;
  diagnosticManager = (NeuDiagnosticManager *)dp_DW.STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_0 = ne_simulator_method((NeslSimulator *)dp_DW.STATE_1_Simulator,
    NESL_SIM_PROJECTION, simulationData, diagnosticManager);
  if (tmp_0 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
    if (tmp) {
      char *msg;
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(dp_M, msg);
    }
  }

  /* End of Projection for SimscapeExecutionBlock: '<S14>/STATE_1' */
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  dp_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  dp_step();
  dp_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  dp_step();
  dp_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  dp_step();
  dp_projection();
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void dp_step(void)
{
  if (rtmIsMajorTimeStep(dp_M)) {
    /* set solver stop time */
    if (!(dp_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&dp_M->solverInfo, ((dp_M->Timing.clockTickH0 + 1) *
        dp_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&dp_M->solverInfo, ((dp_M->Timing.clockTick0 + 1) *
        dp_M->Timing.stepSize0 + dp_M->Timing.clockTickH0 *
        dp_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(dp_M)) {
    dp_M->Timing.t[0] = rtsiGetT(&dp_M->solverInfo);
  }

  {
    NeParameterBundle expl_temp;
    NeslSimulationData *simulationData;
    NeuDiagnosticManager *diag;
    NeuDiagnosticTree *diagnosticTree;
    NeuDiagnosticTree *diagnosticTree_0;
    real_T tmp[4];
    real_T tmp_4[4];
    real_T time;
    real_T time_0;
    real_T time_1;
    real_T time_2;
    real_T time_tmp;
    real_T time_tmp_0;
    real_T *parameterBundle_mRealParameters;
    int32_T tmp_2;
    int_T tmp_5[2];
    int_T tmp_1;
    boolean_T ok;
    boolean_T tmp_0;
    boolean_T tmp_3;
    if (rtmIsMajorTimeStep(dp_M)) {
      /* SimscapeRtp: '<S7>/RTP_1' incorporates:
       *  Constant: '<Root>/Subsystem_around_RTP_00F46B65_PositionTargetValue'
       *  Constant: '<Root>/Subsystem_around_RTP_00F46B65_VelocityTargetValue'
       *  Constant: '<Root>/Subsystem_around_RTP_9CB22C5A_PositionTargetValue'
       *  Constant: '<Root>/Subsystem_around_RTP_9CB22C5A_VelocityTargetValue'
       */
      if (dp_DW.RTP_1_SetParametersNeeded) {
        NeuDiagnosticTree *diagTree;
        tmp[0] = -30.0;
        tmp[1] = 0.0;
        tmp[2] = -30.0;
        tmp[3] = 0.0;
        parameterBundle_mRealParameters = &tmp[0];
        diag = rtw_create_diagnostics();
        diagTree = neu_diagnostic_manager_get_initial_tree(diag);
        expl_temp.mRealParameters.mN = 4;
        expl_temp.mRealParameters.mX = parameterBundle_mRealParameters;
        expl_temp.mLogicalParameters.mN = 0;
        expl_temp.mLogicalParameters.mX = NULL;
        expl_temp.mIntegerParameters.mN = 0;
        expl_temp.mIntegerParameters.mX = NULL;
        expl_temp.mIndexParameters.mN = 0;
        expl_temp.mIndexParameters.mX = NULL;
        ok = nesl_rtp_manager_set_rtps((NeslRtpManager *)dp_DW.RTP_1_RtpManager,
          dp_M->Timing.t[0], expl_temp, diag);
        if (!ok) {
          ok = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
          if (ok) {
            char *msg;
            msg = rtw_diagnostics_msg(diagTree);
            rtmSetErrorStatus(dp_M, msg);
          }
        }
      }

      dp_DW.RTP_1_SetParametersNeeded = false;

      /* End of SimscapeRtp: '<S7>/RTP_1' */
    }

    /* SimscapeExecutionBlock: '<S14>/STATE_1' incorporates:
     *  SimscapeExecutionBlock: '<S14>/OUTPUT_1_0'
     */
    simulationData = (NeslSimulationData *)dp_DW.STATE_1_SimData;
    time_tmp = dp_M->Timing.t[0];
    time = time_tmp;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 4;
    simulationData->mData->mContStates.mX = &dp_X.dpJ1Rzq[0];
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &dp_DW.STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &dp_DW.STATE_1_Modes;
    ok = false;
    simulationData->mData->mFoundZcEvents = ok;
    ok = rtmIsMajorTimeStep(dp_M);
    simulationData->mData->mIsMajorTimeStep = ok;
    tmp_0 = false;
    simulationData->mData->mIsSolverAssertCheck = tmp_0;
    simulationData->mData->mIsSolverCheckingCIC = false;
    tmp_0 = rtsiIsSolverComputingJacobian(&dp_M->solverInfo);
    simulationData->mData->mIsComputingJacobian = tmp_0;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp_0 = rtsiIsModeUpdateTimeStep(&dp_M->solverInfo);
    simulationData->mData->mIsModeUpdateTimeStep = tmp_0;
    tmp_1 = 0;
    simulationData->mData->mInputValues.mN = 0;
    simulationData->mData->mInputOffsets.mN = 1;
    simulationData->mData->mInputOffsets.mX = &tmp_1;
    simulationData->mData->mOutputs.mN = 4;
    simulationData->mData->mOutputs.mX = &dp_B.STATE_1[0];
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    time_tmp_0 = dp_M->Timing.t[0];
    time_0 = time_tmp_0;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_0;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    diag = (NeuDiagnosticManager *)dp_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diag);
    tmp_2 = ne_simulator_method((NeslSimulator *)dp_DW.STATE_1_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diag);
    if (tmp_2 != 0) {
      tmp_3 = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
      if (tmp_3) {
        char *msg_0;
        msg_0 = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(dp_M, msg_0);
      }
    }

    /* End of SimscapeExecutionBlock: '<S14>/STATE_1' */

    /* SimscapeExecutionBlock: '<S14>/OUTPUT_1_0' */
    simulationData = (NeslSimulationData *)dp_DW.OUTPUT_1_0_SimData;
    time_1 = time_tmp;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_1;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &dp_DW.OUTPUT_1_0_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &dp_DW.OUTPUT_1_0_Modes;
    tmp_3 = false;
    simulationData->mData->mFoundZcEvents = tmp_3;
    simulationData->mData->mIsMajorTimeStep = ok;
    ok = false;
    simulationData->mData->mIsSolverAssertCheck = ok;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = tmp_0;
    tmp_5[0] = 0;
    tmp_4[0] = dp_B.STATE_1[0];
    tmp_4[1] = dp_B.STATE_1[1];
    tmp_4[2] = dp_B.STATE_1[2];
    tmp_4[3] = dp_B.STATE_1[3];
    tmp_5[1] = 4;
    simulationData->mData->mInputValues.mN = 4;
    simulationData->mData->mInputValues.mX = &tmp_4[0];
    simulationData->mData->mInputOffsets.mN = 2;
    simulationData->mData->mInputOffsets.mX = &tmp_5[0];
    simulationData->mData->mOutputs.mN = 6;
    simulationData->mData->mOutputs.mX = &dp_B.OUTPUT_1_0[0];
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    time_2 = time_tmp_0;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_2;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    diag = (NeuDiagnosticManager *)dp_DW.OUTPUT_1_0_DiagMgr;
    diagnosticTree_0 = neu_diagnostic_manager_get_initial_tree(diag);
    tmp_2 = ne_simulator_method((NeslSimulator *)dp_DW.OUTPUT_1_0_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diag);
    if (tmp_2 != 0) {
      ok = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
      if (ok) {
        char *msg_1;
        msg_1 = rtw_diagnostics_msg(diagnosticTree_0);
        rtmSetErrorStatus(dp_M, msg_1);
      }
    }

    if (rtmIsMajorTimeStep(dp_M)) {
    }
  }

  if (rtmIsMajorTimeStep(dp_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(dp_M->rtwLogInfo, (dp_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(dp_M)) {
    NeslSimulationData *simulationData;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    real_T time;
    int_T tmp_0;
    boolean_T tmp;

    /* Update for SimscapeExecutionBlock: '<S14>/STATE_1' */
    simulationData = (NeslSimulationData *)dp_DW.STATE_1_SimData;
    time = dp_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 4;
    simulationData->mData->mContStates.mX = &dp_X.dpJ1Rzq[0];
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &dp_DW.STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &dp_DW.STATE_1_Modes;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(dp_M);
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    tmp = rtsiIsSolverComputingJacobian(&dp_M->solverInfo);
    simulationData->mData->mIsComputingJacobian = tmp;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
      (&dp_M->solverInfo);
    tmp_0 = 0;
    simulationData->mData->mInputValues.mN = 0;
    simulationData->mData->mInputOffsets.mN = 1;
    simulationData->mData->mInputOffsets.mX = &tmp_0;
    diagnosticManager = (NeuDiagnosticManager *)dp_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_0 = ne_simulator_method((NeslSimulator *)dp_DW.STATE_1_Simulator,
      NESL_SIM_UPDATE, simulationData, diagnosticManager);
    if (tmp_0 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
      if (tmp) {
        char *msg;
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(dp_M, msg);
      }
    }

    /* End of Update for SimscapeExecutionBlock: '<S14>/STATE_1' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(dp_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(dp_M)!=-1) &&
          !((rtmGetTFinal(dp_M)-(((dp_M->Timing.clockTick1+
               dp_M->Timing.clockTickH1* 4294967296.0)) * 0.01)) >
            (((dp_M->Timing.clockTick1+dp_M->Timing.clockTickH1* 4294967296.0)) *
             0.01) * (DBL_EPSILON))) {
        rtmSetErrorStatus(dp_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&dp_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++dp_M->Timing.clockTick0)) {
      ++dp_M->Timing.clockTickH0;
    }

    dp_M->Timing.t[0] = rtsiGetSolverStopTime(&dp_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      dp_M->Timing.clockTick1++;
      if (!dp_M->Timing.clockTick1) {
        dp_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void dp_derivatives(void)
{
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  XDot_dp_T *_rtXdot;
  real_T time;
  int_T tmp_0;
  boolean_T tmp;
  _rtXdot = ((XDot_dp_T *) dp_M->derivs);

  /* Derivatives for SimscapeExecutionBlock: '<S14>/STATE_1' */
  simulationData = (NeslSimulationData *)dp_DW.STATE_1_SimData;
  time = dp_M->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 4;
  simulationData->mData->mContStates.mX = &dp_X.dpJ1Rzq[0];
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &dp_DW.STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 0;
  simulationData->mData->mModeVector.mX = &dp_DW.STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(dp_M);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&dp_M->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&dp_M->solverInfo);
  tmp_0 = 0;
  simulationData->mData->mInputValues.mN = 0;
  simulationData->mData->mInputOffsets.mN = 1;
  simulationData->mData->mInputOffsets.mX = &tmp_0;
  simulationData->mData->mDx.mN = 4;
  simulationData->mData->mDx.mX = &_rtXdot->dpJ1Rzq[0];
  diagnosticManager = (NeuDiagnosticManager *)dp_DW.STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_0 = ne_simulator_method((NeslSimulator *)dp_DW.STATE_1_Simulator,
    NESL_SIM_DERIVATIVES, simulationData, diagnosticManager);
  if (tmp_0 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
    if (tmp) {
      char *msg;
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(dp_M, msg);
    }
  }

  /* End of Derivatives for SimscapeExecutionBlock: '<S14>/STATE_1' */
}

/* Model initialize function */
void dp_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)dp_M, 0,
                sizeof(RT_MODEL_dp_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&dp_M->solverInfo, &dp_M->Timing.simTimeStep);
    rtsiSetTPtr(&dp_M->solverInfo, &rtmGetTPtr(dp_M));
    rtsiSetStepSizePtr(&dp_M->solverInfo, &dp_M->Timing.stepSize0);
    rtsiSetdXPtr(&dp_M->solverInfo, &dp_M->derivs);
    rtsiSetContStatesPtr(&dp_M->solverInfo, (real_T **) &dp_M->contStates);
    rtsiSetNumContStatesPtr(&dp_M->solverInfo, &dp_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&dp_M->solverInfo,
      &dp_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&dp_M->solverInfo,
      &dp_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&dp_M->solverInfo,
      &dp_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&dp_M->solverInfo, (&rtmGetErrorStatus(dp_M)));
    rtsiSetRTModelPtr(&dp_M->solverInfo, dp_M);
  }

  rtsiSetSimTimeStep(&dp_M->solverInfo, MAJOR_TIME_STEP);
  dp_M->intgData.y = dp_M->odeY;
  dp_M->intgData.f[0] = dp_M->odeF[0];
  dp_M->intgData.f[1] = dp_M->odeF[1];
  dp_M->intgData.f[2] = dp_M->odeF[2];
  dp_M->contStates = ((X_dp_T *) &dp_X);
  rtsiSetSolverData(&dp_M->solverInfo, (void *)&dp_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&dp_M->solverInfo, false);
  rtsiSetSolverName(&dp_M->solverInfo,"ode3");
  rtmSetTPtr(dp_M, &dp_M->Timing.tArray[0]);
  rtmSetTFinal(dp_M, 10.0);
  dp_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    dp_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(dp_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(dp_M->rtwLogInfo, (NULL));
    rtliSetLogT(dp_M->rtwLogInfo, "tout");
    rtliSetLogX(dp_M->rtwLogInfo, "");
    rtliSetLogXFinal(dp_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(dp_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(dp_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(dp_M->rtwLogInfo, 10000);
    rtliSetLogDecimation(dp_M->rtwLogInfo, 1);
    rtliSetLogY(dp_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(dp_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(dp_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &dp_B), 0,
                sizeof(B_dp_T));

  /* states (continuous) */
  {
    (void) memset((void *)&dp_X, 0,
                  sizeof(X_dp_T));
  }

  /* states (dwork) */
  (void) memset((void *)&dp_DW, 0,
                sizeof(DW_dp_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(dp_M->rtwLogInfo, 0.0, rtmGetTFinal(dp_M),
    dp_M->Timing.stepSize0, (&rtmGetErrorStatus(dp_M)));

  {
    NeModelParameters modelParameters;
    NeModelParameters modelParameters_0;
    NeslRtpManager *manager;
    NeslRtpManager *manager_0;
    NeslSimulationData *tmp_1;
    NeslSimulator *tmp_0;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    NeuDiagnosticTree *diagnosticTree_0;
    real_T tmp_2;
    int32_T tmp_3;
    boolean_T tmp;

    /* Start for SimscapeRtp: '<S7>/RTP_1' */
    manager_0 = nesl_lease_rtp_manager("dp/Solver Configuration_1", 0);
    manager = manager_0;
    tmp = pointer_is_null(manager_0);
    if (tmp) {
      dp_a151ee3d_1_gateway();
      manager = nesl_lease_rtp_manager("dp/Solver Configuration_1", 0);
    }

    dp_DW.RTP_1_RtpManager = (void *)manager;
    dp_DW.RTP_1_SetParametersNeeded = true;

    /* End of Start for SimscapeRtp: '<S7>/RTP_1' */

    /* Start for SimscapeExecutionBlock: '<S14>/STATE_1' */
    tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 0, 0);
    dp_DW.STATE_1_Simulator = (void *)tmp_0;
    tmp = pointer_is_null(dp_DW.STATE_1_Simulator);
    if (tmp) {
      dp_a151ee3d_1_gateway();
      tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 0, 0);
      dp_DW.STATE_1_Simulator = (void *)tmp_0;
    }

    tmp_1 = nesl_create_simulation_data();
    dp_DW.STATE_1_SimData = (void *)tmp_1;
    diagnosticManager = rtw_create_diagnostics();
    dp_DW.STATE_1_DiagMgr = (void *)diagnosticManager;
    modelParameters.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters.mSolverAbsTol = 0.001;
    modelParameters.mSolverRelTol = 0.001;
    modelParameters.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters.mStartTime = 0.0;
    modelParameters.mLoadInitialState = true;
    modelParameters.mUseSimState = false;
    modelParameters.mLinTrimCompile = false;
    modelParameters.mLoggingMode = SSC_LOGGING_ALL;
    modelParameters.mRTWModifiedTimeStamp = 5.8576198E+8;
    tmp_2 = 0.001;
    modelParameters.mSolverTolerance = tmp_2;
    tmp_2 = 0.01;
    modelParameters.mFixedStepSize = tmp_2;
    tmp = false;
    modelParameters.mVariableStepSolver = tmp;
    tmp = false;
    modelParameters.mIsUsingODEN = tmp;
    modelParameters.mZcDisabled = true;
    diagnosticManager = (NeuDiagnosticManager *)dp_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_3 = nesl_initialize_simulator((NeslSimulator *)dp_DW.STATE_1_Simulator,
      &modelParameters, diagnosticManager);
    if (tmp_3 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
      if (tmp) {
        char *msg;
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(dp_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S14>/STATE_1' */

    /* Start for SimscapeExecutionBlock: '<S14>/OUTPUT_1_0' */
    tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 1, 0);
    dp_DW.OUTPUT_1_0_Simulator = (void *)tmp_0;
    tmp = pointer_is_null(dp_DW.OUTPUT_1_0_Simulator);
    if (tmp) {
      dp_a151ee3d_1_gateway();
      tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 1, 0);
      dp_DW.OUTPUT_1_0_Simulator = (void *)tmp_0;
    }

    tmp_1 = nesl_create_simulation_data();
    dp_DW.OUTPUT_1_0_SimData = (void *)tmp_1;
    diagnosticManager = rtw_create_diagnostics();
    dp_DW.OUTPUT_1_0_DiagMgr = (void *)diagnosticManager;
    modelParameters_0.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters_0.mSolverAbsTol = 0.001;
    modelParameters_0.mSolverRelTol = 0.001;
    modelParameters_0.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters_0.mStartTime = 0.0;
    modelParameters_0.mLoadInitialState = true;
    modelParameters_0.mUseSimState = false;
    modelParameters_0.mLinTrimCompile = false;
    modelParameters_0.mLoggingMode = SSC_LOGGING_ALL;
    modelParameters_0.mRTWModifiedTimeStamp = 5.8576198E+8;
    tmp_2 = 0.001;
    modelParameters_0.mSolverTolerance = tmp_2;
    tmp_2 = 0.01;
    modelParameters_0.mFixedStepSize = tmp_2;
    tmp = false;
    modelParameters_0.mVariableStepSolver = tmp;
    tmp = false;
    modelParameters_0.mIsUsingODEN = tmp;
    modelParameters_0.mZcDisabled = true;
    diagnosticManager = (NeuDiagnosticManager *)dp_DW.OUTPUT_1_0_DiagMgr;
    diagnosticTree_0 = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_3 = nesl_initialize_simulator((NeslSimulator *)
      dp_DW.OUTPUT_1_0_Simulator, &modelParameters_0, diagnosticManager);
    if (tmp_3 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(dp_M));
      if (tmp) {
        char *msg_0;
        msg_0 = rtw_diagnostics_msg(diagnosticTree_0);
        rtmSetErrorStatus(dp_M, msg_0);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S14>/OUTPUT_1_0' */
  }

  /* initial state override */
  {
    static const real_T rtcs0_dpJ1Rzq[4] = {
      0.1
      , 0.1
      , 0.1
      , 0.1
    };

    (void) memcpy(dp_X.dpJ1Rzq, rtcs0_dpJ1Rzq,
                  4*sizeof(real_T));
  }
}

/* Model terminate function */
void dp_terminate(void)
{
  /* Terminate for SimscapeExecutionBlock: '<S14>/STATE_1' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)dp_DW.STATE_1_DiagMgr);
  nesl_destroy_simulation_data((NeslSimulationData *)dp_DW.STATE_1_SimData);
  nesl_erase_simulator("dp/Solver Configuration_1");
  nesl_destroy_registry();

  /* Terminate for SimscapeExecutionBlock: '<S14>/OUTPUT_1_0' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    dp_DW.OUTPUT_1_0_DiagMgr);
  nesl_destroy_simulation_data((NeslSimulationData *)dp_DW.OUTPUT_1_0_SimData);
  nesl_erase_simulator("dp/Solver Configuration_1");
  nesl_destroy_registry();
}
