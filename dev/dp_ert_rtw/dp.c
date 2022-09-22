/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: dp.c
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

#include "dp.h"
#include "rtwtypes.h"
#include <stddef.h>
#include "dp_capi.h"
#include <string.h>

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* private model entry point functions */
extern void dp_derivatives(RT_MODEL *const rtM);

/* Projection for root system: '<Root>' */
void dp_projection(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  X *rtX = rtM->contStates;
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  real_T time;
  int_T tmp_0;
  boolean_T tmp;

  /* Projection for SimscapeExecutionBlock: '<S14>/STATE_1' */
  simulationData = (NeslSimulationData *)rtDW->STATE_1_SimData;
  time = rtM->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 4;
  simulationData->mData->mContStates.mX = &rtX->dpJ1Rzq[0];
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &rtDW->STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 0;
  simulationData->mData->mModeVector.mX = &rtDW->STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(rtM);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&rtM->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&rtM->solverInfo);
  tmp_0 = 0;
  simulationData->mData->mInputValues.mN = 0;
  simulationData->mData->mInputOffsets.mN = 1;
  simulationData->mData->mInputOffsets.mX = &tmp_0;
  diagnosticManager = (NeuDiagnosticManager *)rtDW->STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_0 = ne_simulator_method((NeslSimulator *)rtDW->STATE_1_Simulator,
    NESL_SIM_PROJECTION, simulationData, diagnosticManager);
  if (tmp_0 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(rtM));
    if (tmp) {
      char *msg;
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(rtM, msg);
    }
  }

  /* End of Projection for SimscapeExecutionBlock: '<S14>/STATE_1' */
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si , RT_MODEL *const
  rtM)
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
  dp_derivatives(rtM);

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  dp_step(rtM);
  dp_derivatives(rtM);

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  dp_step(rtM);
  dp_derivatives(rtM);

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  dp_step(rtM);
  dp_projection(rtM);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void dp_step(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  X *rtX = rtM->contStates;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  {
    NeParameterBundle expl_temp;
    NeslSimulationData *simulationData;
    NeuDiagnosticManager *diag;
    NeuDiagnosticTree *diagnosticTree;
    NeuDiagnosticTree *diagnosticTree_0;
    real_T rtb_OUTPUT_1_0[6];
    real_T tmp[4];
    real_T tmp_3[4];
    real_T time;
    real_T time_0;
    real_T time_1;
    real_T time_2;
    real_T time_tmp;
    real_T time_tmp_0;
    real_T *parameterBundle_mRealParameters;
    int_T tmp_4[2];
    int_T j;
    int_T tmp_1;
    boolean_T ok;
    boolean_T tmp_0;
    boolean_T tmp_2;
    if (rtmIsMajorTimeStep(rtM)) {
      /* SimscapeRtp: '<S7>/RTP_1' incorporates:
       *  Constant: '<Root>/Subsystem_around_RTP_00F46B65_PositionTargetValue'
       *  Constant: '<Root>/Subsystem_around_RTP_00F46B65_VelocityTargetValue'
       *  Constant: '<Root>/Subsystem_around_RTP_9CB22C5A_PositionTargetValue'
       *  Constant: '<Root>/Subsystem_around_RTP_9CB22C5A_VelocityTargetValue'
       */
      if (rtDW->RTP_1_SetParametersNeeded) {
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
        ok = nesl_rtp_manager_set_rtps((NeslRtpManager *)rtDW->RTP_1_RtpManager,
          rtM->Timing.t[0], expl_temp, diag);
        if (!ok) {
          ok = error_buffer_is_empty(rtmGetErrorStatus(rtM));
          if (ok) {
            char *msg;
            msg = rtw_diagnostics_msg(diagTree);
            rtmSetErrorStatus(rtM, msg);
          }
        }
      }

      rtDW->RTP_1_SetParametersNeeded = false;

      /* End of SimscapeRtp: '<S7>/RTP_1' */
    }

    /* SimscapeExecutionBlock: '<S14>/STATE_1' incorporates:
     *  SimscapeExecutionBlock: '<S14>/OUTPUT_1_0'
     */
    simulationData = (NeslSimulationData *)rtDW->STATE_1_SimData;
    time_tmp = rtM->Timing.t[0];
    time = time_tmp;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 4;
    simulationData->mData->mContStates.mX = &rtX->dpJ1Rzq[0];
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &rtDW->STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &rtDW->STATE_1_Modes;
    ok = false;
    simulationData->mData->mFoundZcEvents = ok;
    ok = rtmIsMajorTimeStep(rtM);
    simulationData->mData->mIsMajorTimeStep = ok;
    tmp_0 = false;
    simulationData->mData->mIsSolverAssertCheck = tmp_0;
    simulationData->mData->mIsSolverCheckingCIC = false;
    tmp_0 = rtsiIsSolverComputingJacobian(&rtM->solverInfo);
    simulationData->mData->mIsComputingJacobian = tmp_0;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp_0 = rtsiIsModeUpdateTimeStep(&rtM->solverInfo);
    simulationData->mData->mIsModeUpdateTimeStep = tmp_0;
    tmp_1 = 0;
    simulationData->mData->mInputValues.mN = 0;
    simulationData->mData->mInputOffsets.mN = 1;
    simulationData->mData->mInputOffsets.mX = &tmp_1;
    simulationData->mData->mOutputs.mN = 4;
    simulationData->mData->mOutputs.mX = &rtDW->STATE_1[0];
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    time_tmp_0 = rtM->Timing.t[0];
    time_0 = time_tmp_0;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_0;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    diag = (NeuDiagnosticManager *)rtDW->STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diag);
    j = ne_simulator_method((NeslSimulator *)rtDW->STATE_1_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diag);
    if (j != 0) {
      tmp_2 = error_buffer_is_empty(rtmGetErrorStatus(rtM));
      if (tmp_2) {
        char *msg_0;
        msg_0 = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(rtM, msg_0);
      }
    }

    /* End of SimscapeExecutionBlock: '<S14>/STATE_1' */

    /* SimscapeExecutionBlock: '<S14>/OUTPUT_1_0' */
    simulationData = (NeslSimulationData *)rtDW->OUTPUT_1_0_SimData;
    time_1 = time_tmp;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_1;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &rtDW->OUTPUT_1_0_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &rtDW->OUTPUT_1_0_Modes;
    tmp_2 = false;
    simulationData->mData->mFoundZcEvents = tmp_2;
    simulationData->mData->mIsMajorTimeStep = ok;
    ok = false;
    simulationData->mData->mIsSolverAssertCheck = ok;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = tmp_0;
    tmp_4[0] = 0;
    tmp_3[0] = rtDW->STATE_1[0];
    tmp_3[1] = rtDW->STATE_1[1];
    tmp_3[2] = rtDW->STATE_1[2];
    tmp_3[3] = rtDW->STATE_1[3];
    tmp_4[1] = 4;
    simulationData->mData->mInputValues.mN = 4;
    simulationData->mData->mInputValues.mX = &tmp_3[0];
    simulationData->mData->mInputOffsets.mN = 2;
    simulationData->mData->mInputOffsets.mX = &tmp_4[0];
    simulationData->mData->mOutputs.mN = 6;
    simulationData->mData->mOutputs.mX = &rtb_OUTPUT_1_0[0];
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    time_2 = time_tmp_0;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_2;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    diag = (NeuDiagnosticManager *)rtDW->OUTPUT_1_0_DiagMgr;
    diagnosticTree_0 = neu_diagnostic_manager_get_initial_tree(diag);
    j = ne_simulator_method((NeslSimulator *)rtDW->OUTPUT_1_0_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diag);
    if (j != 0) {
      ok = error_buffer_is_empty(rtmGetErrorStatus(rtM));
      if (ok) {
        char *msg_1;
        msg_1 = rtw_diagnostics_msg(diagnosticTree_0);
        rtmSetErrorStatus(rtM, msg_1);
      }
    }
  }

  if (rtmIsMajorTimeStep(rtM)) {
    NeslSimulationData *simulationData;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    real_T time;
    int_T tmp_0;
    boolean_T tmp;

    /* Update for SimscapeExecutionBlock: '<S14>/STATE_1' */
    simulationData = (NeslSimulationData *)rtDW->STATE_1_SimData;
    time = rtM->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 4;
    simulationData->mData->mContStates.mX = &rtX->dpJ1Rzq[0];
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &rtDW->STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &rtDW->STATE_1_Modes;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(rtM);
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    tmp = rtsiIsSolverComputingJacobian(&rtM->solverInfo);
    simulationData->mData->mIsComputingJacobian = tmp;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
      (&rtM->solverInfo);
    tmp_0 = 0;
    simulationData->mData->mInputValues.mN = 0;
    simulationData->mData->mInputOffsets.mN = 1;
    simulationData->mData->mInputOffsets.mX = &tmp_0;
    diagnosticManager = (NeuDiagnosticManager *)rtDW->STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_0 = ne_simulator_method((NeslSimulator *)rtDW->STATE_1_Simulator,
      NESL_SIM_UPDATE, simulationData, diagnosticManager);
    if (tmp_0 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(rtM));
      if (tmp) {
        char *msg;
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(rtM, msg);
      }
    }

    /* End of Update for SimscapeExecutionBlock: '<S14>/STATE_1' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo, rtM);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void dp_derivatives(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  X *rtX = rtM->contStates;
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  XDot *_rtXdot;
  real_T time;
  int_T tmp_0;
  boolean_T tmp;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for SimscapeExecutionBlock: '<S14>/STATE_1' */
  simulationData = (NeslSimulationData *)rtDW->STATE_1_SimData;
  time = rtM->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 4;
  simulationData->mData->mContStates.mX = &rtX->dpJ1Rzq[0];
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &rtDW->STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 0;
  simulationData->mData->mModeVector.mX = &rtDW->STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(rtM);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&rtM->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&rtM->solverInfo);
  tmp_0 = 0;
  simulationData->mData->mInputValues.mN = 0;
  simulationData->mData->mInputOffsets.mN = 1;
  simulationData->mData->mInputOffsets.mX = &tmp_0;
  simulationData->mData->mDx.mN = 4;
  simulationData->mData->mDx.mX = &_rtXdot->dpJ1Rzq[0];
  diagnosticManager = (NeuDiagnosticManager *)rtDW->STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_0 = ne_simulator_method((NeslSimulator *)rtDW->STATE_1_Simulator,
    NESL_SIM_DERIVATIVES, simulationData, diagnosticManager);
  if (tmp_0 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(rtM));
    if (tmp) {
      char *msg;
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(rtM, msg);
    }
  }

  /* End of Derivatives for SimscapeExecutionBlock: '<S14>/STATE_1' */
}

/* Model initialize function */
void dp_initialize(RT_MODEL *const rtM)
{
  DW *rtDW = rtM->dwork;
  X *rtX = rtM->contStates;

  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->contStates = ((X *) rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&rtM->solverInfo, false);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.01;

  /* states (continuous) */
  {
    (void) memset((void *)rtX, 0,
                  sizeof(X));
  }

  /* states (dwork) */
  (void) memset((void *)rtDW, 0,
                sizeof(DW));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  dp_InitializeDataMapInfo(rtM, (X *)rtM->contStates);

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

    rtDW->RTP_1_RtpManager = (void *)manager;
    rtDW->RTP_1_SetParametersNeeded = true;

    /* End of Start for SimscapeRtp: '<S7>/RTP_1' */

    /* Start for SimscapeExecutionBlock: '<S14>/STATE_1' */
    tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 0, 0);
    rtDW->STATE_1_Simulator = (void *)tmp_0;
    tmp = pointer_is_null(rtDW->STATE_1_Simulator);
    if (tmp) {
      dp_a151ee3d_1_gateway();
      tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 0, 0);
      rtDW->STATE_1_Simulator = (void *)tmp_0;
    }

    tmp_1 = nesl_create_simulation_data();
    rtDW->STATE_1_SimData = (void *)tmp_1;
    diagnosticManager = rtw_create_diagnostics();
    rtDW->STATE_1_DiagMgr = (void *)diagnosticManager;
    modelParameters.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters.mSolverAbsTol = 0.001;
    modelParameters.mSolverRelTol = 0.001;
    modelParameters.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters.mStartTime = 0.0;
    modelParameters.mLoadInitialState = true;
    modelParameters.mUseSimState = false;
    modelParameters.mLinTrimCompile = false;
    modelParameters.mLoggingMode = SSC_LOGGING_ALL;
    modelParameters.mRTWModifiedTimeStamp = 5.85714389E+8;
    tmp_2 = 0.001;
    modelParameters.mSolverTolerance = tmp_2;
    tmp_2 = 0.01;
    modelParameters.mFixedStepSize = tmp_2;
    tmp = false;
    modelParameters.mVariableStepSolver = tmp;
    tmp = false;
    modelParameters.mIsUsingODEN = tmp;
    modelParameters.mZcDisabled = true;
    diagnosticManager = (NeuDiagnosticManager *)rtDW->STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_3 = nesl_initialize_simulator((NeslSimulator *)rtDW->STATE_1_Simulator,
      &modelParameters, diagnosticManager);
    if (tmp_3 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(rtM));
      if (tmp) {
        char *msg;
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(rtM, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S14>/STATE_1' */

    /* Start for SimscapeExecutionBlock: '<S14>/OUTPUT_1_0' */
    tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 1, 0);
    rtDW->OUTPUT_1_0_Simulator = (void *)tmp_0;
    tmp = pointer_is_null(rtDW->OUTPUT_1_0_Simulator);
    if (tmp) {
      dp_a151ee3d_1_gateway();
      tmp_0 = nesl_lease_simulator("dp/Solver Configuration_1", 1, 0);
      rtDW->OUTPUT_1_0_Simulator = (void *)tmp_0;
    }

    tmp_1 = nesl_create_simulation_data();
    rtDW->OUTPUT_1_0_SimData = (void *)tmp_1;
    diagnosticManager = rtw_create_diagnostics();
    rtDW->OUTPUT_1_0_DiagMgr = (void *)diagnosticManager;
    modelParameters_0.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters_0.mSolverAbsTol = 0.001;
    modelParameters_0.mSolverRelTol = 0.001;
    modelParameters_0.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters_0.mStartTime = 0.0;
    modelParameters_0.mLoadInitialState = true;
    modelParameters_0.mUseSimState = false;
    modelParameters_0.mLinTrimCompile = false;
    modelParameters_0.mLoggingMode = SSC_LOGGING_ALL;
    modelParameters_0.mRTWModifiedTimeStamp = 5.85714389E+8;
    tmp_2 = 0.001;
    modelParameters_0.mSolverTolerance = tmp_2;
    tmp_2 = 0.01;
    modelParameters_0.mFixedStepSize = tmp_2;
    tmp = false;
    modelParameters_0.mVariableStepSolver = tmp;
    tmp = false;
    modelParameters_0.mIsUsingODEN = tmp;
    modelParameters_0.mZcDisabled = true;
    diagnosticManager = (NeuDiagnosticManager *)rtDW->OUTPUT_1_0_DiagMgr;
    diagnosticTree_0 = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_3 = nesl_initialize_simulator((NeslSimulator *)
      rtDW->OUTPUT_1_0_Simulator, &modelParameters_0, diagnosticManager);
    if (tmp_3 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(rtM));
      if (tmp) {
        char *msg_0;
        msg_0 = rtw_diagnostics_msg(diagnosticTree_0);
        rtmSetErrorStatus(rtM, msg_0);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S14>/OUTPUT_1_0' */
  }

  /* initial state override */
  {
    static const real_T rtcs0_dpJ1Rzq[4] = {
      0.0
      , 0.0
      , 0.0
      , 0.0
    };

    (void) memcpy(rtX->dpJ1Rzq, rtcs0_dpJ1Rzq,
                  4*sizeof(real_T));
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
