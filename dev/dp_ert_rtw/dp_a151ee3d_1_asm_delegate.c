/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'dp/Solver Configuration'.
 */

#include <math.h>
#include <string.h>
#include "pm_std.h"
#include "sm_std.h"
#include "ne_std.h"
#include "ne_dae.h"
#include "sm_ssci_run_time_errors.h"
#include "sm_RuntimeDerivedValuesBundle.h"
#include "sm_CTarget.h"

static void setTargets_0(const RuntimeDerivedValuesBundle *rtdv, double *values,
  double *auxData)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  (void) auxData;
  values[0] = rtdvd[0];
}

static void setTargets_1(const RuntimeDerivedValuesBundle *rtdv, double *values,
  double *auxData)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  (void) auxData;
  values[0] = rtdvd[1];
}

static void setTargets_2(const RuntimeDerivedValuesBundle *rtdv, double *values,
  double *auxData)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  (void) auxData;
  values[0] = rtdvd[2];
}

static void setTargets_3(const RuntimeDerivedValuesBundle *rtdv, double *values,
  double *auxData)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) rtdvi;
  (void) auxData;
  values[0] = rtdvd[3];
}

void dp_a151ee3d_1_setTargets(const RuntimeDerivedValuesBundle *rtdv, CTarget
  *targets)
{
  setTargets_0(rtdv, targets[0].mValue, targets[0].mAuxiliaryTargetData);
  setTargets_1(rtdv, targets[1].mValue, targets[1].mAuxiliaryTargetData);
  setTargets_2(rtdv, targets[2].mValue, targets[2].mAuxiliaryTargetData);
  setTargets_3(rtdv, targets[3].mValue, targets[3].mAuxiliaryTargetData);
}

void dp_a151ee3d_1_resetAsmStateVector(const void *mech, double *state)
{
  double xx[1];
  (void) mech;
  xx[0] = 0.0;
  state[0] = xx[0];
  state[1] = xx[0];
  state[2] = xx[0];
  state[3] = xx[0];
}

void dp_a151ee3d_1_initializeTrackedAngleState(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, const int *modeVector, const double
  *motionData, double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  (void) state;
  (void) modeVector;
  (void) motionData;
}

void dp_a151ee3d_1_computeDiscreteState(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, double *state)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  (void) state;
}

void dp_a151ee3d_1_adjustPosition(const void *mech, const double *dofDeltas,
  double *state)
{
  (void) mech;
  state[0] = state[0] + dofDeltas[0];
  state[2] = state[2] + dofDeltas[1];
}

static void perturbAsmJointPrimitiveState_0_0(double mag, double *state)
{
  state[0] = state[0] + mag;
}

static void perturbAsmJointPrimitiveState_0_0v(double mag, double *state)
{
  state[0] = state[0] + mag;
  state[1] = state[1] - 0.875 * mag;
}

static void perturbAsmJointPrimitiveState_1_0(double mag, double *state)
{
  state[2] = state[2] + mag;
}

static void perturbAsmJointPrimitiveState_1_0v(double mag, double *state)
{
  state[2] = state[2] + mag;
  state[3] = state[3] - 0.875 * mag;
}

void dp_a151ee3d_1_perturbAsmJointPrimitiveState(const void *mech, size_t
  stageIdx, size_t primIdx, double mag, boolean_T doPerturbVelocity, double
  *state)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) mag;
  (void) doPerturbVelocity;
  (void) state;
  switch ((stageIdx * 6 + primIdx) * 2 + (doPerturbVelocity ? 1 : 0))
  {
   case 0:
    perturbAsmJointPrimitiveState_0_0(mag, state);
    break;

   case 1:
    perturbAsmJointPrimitiveState_0_0v(mag, state);
    break;

   case 12:
    perturbAsmJointPrimitiveState_1_0(mag, state);
    break;

   case 13:
    perturbAsmJointPrimitiveState_1_0v(mag, state);
    break;
  }
}

void dp_a151ee3d_1_computePosDofBlendMatrix(const void *mech, size_t stageIdx,
  size_t primIdx, const double *state, int partialType, double *matrix)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) state;
  (void) partialType;
  (void) matrix;
  switch ((stageIdx * 6 + primIdx))
  {
  }
}

void dp_a151ee3d_1_computeVelDofBlendMatrix(const void *mech, size_t stageIdx,
  size_t primIdx, const double *state, int partialType, double *matrix)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) state;
  (void) partialType;
  (void) matrix;
  switch ((stageIdx * 6 + primIdx))
  {
  }
}

void dp_a151ee3d_1_projectPartiallyTargetedPos(const void *mech, size_t stageIdx,
  size_t primIdx, const double *origState, int partialType, double *state)
{
  (void) mech;
  (void) stageIdx;
  (void) primIdx;
  (void) origState;
  (void) partialType;
  (void) state;
  switch ((stageIdx * 6 + primIdx))
  {
  }
}

void dp_a151ee3d_1_propagateMotion(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, const double *state, double *motionData)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[18];
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  xx[0] = 0.5;
  xx[1] = xx[0] * state[0];
  xx[2] = cos(xx[1]);
  xx[3] = 0.0;
  xx[4] = sin(xx[1]);
  xx[1] = 2.0;
  xx[5] = 0.1;
  xx[6] = xx[5] * xx[4];
  xx[7] = xx[1] * xx[6] * xx[4] - xx[5];
  xx[8] = xx[1] * xx[6] * xx[2];
  xx[6] = xx[0] * state[2];
  xx[0] = cos(xx[6]);
  xx[9] = sin(xx[6]);
  xx[6] = xx[5] * xx[9];
  xx[10] = xx[5] - (xx[1] * xx[6] * xx[9] - xx[5]);
  xx[11] = xx[1] * xx[6] * xx[0];
  xx[6] = xx[11] * xx[4];
  xx[12] = xx[10] * xx[4];
  xx[13] = xx[5] * state[1];
  xx[14] = xx[10] * state[1] + xx[13];
  xx[15] = xx[14] * xx[9];
  xx[16] = xx[11] * state[1];
  xx[17] = xx[16] * xx[9];
  motionData[0] = - xx[2];
  motionData[1] = xx[3];
  motionData[2] = xx[3];
  motionData[3] = - xx[4];
  motionData[4] = - xx[7];
  motionData[5] = xx[8];
  motionData[6] = xx[3];
  motionData[7] = - xx[0];
  motionData[8] = xx[3];
  motionData[9] = xx[3];
  motionData[10] = - xx[9];
  motionData[11] = xx[10];
  motionData[12] = xx[11];
  motionData[13] = xx[3];
  motionData[14] = xx[2] * xx[0] - xx[4] * xx[9];
  motionData[15] = xx[3];
  motionData[16] = xx[3];
  motionData[17] = xx[2] * xx[9] + xx[0] * xx[4];
  motionData[18] = xx[10] - xx[1] * (xx[6] * xx[2] + xx[12] * xx[4]) - xx[7];
  motionData[19] = xx[1] * (xx[12] * xx[2] - xx[6] * xx[4]) + xx[11] + xx[8];
  motionData[20] = xx[3];
  motionData[21] = xx[3];
  motionData[22] = xx[3];
  motionData[23] = state[1];
  motionData[24] = xx[3];
  motionData[25] = xx[13];
  motionData[26] = xx[3];
  motionData[27] = xx[3];
  motionData[28] = xx[3];
  motionData[29] = state[1] + state[3];
  motionData[30] = xx[1] * (xx[15] * xx[0] + xx[17] * xx[9]) - xx[16];
  motionData[31] = xx[14] - xx[1] * (xx[15] * xx[9] - xx[17] * xx[0]) + xx[5] *
    state[3];
  motionData[32] = xx[3];
}

size_t dp_a151ee3d_1_computeAssemblyError(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, size_t constraintIdx, const int *modeVector,
  const double *motionData, double *error)
{
  (void) mech;
  (void)rtdv;
  (void) modeVector;
  (void) motionData;
  (void) error;
  switch (constraintIdx)
  {
  }

  return 0;
}

size_t dp_a151ee3d_1_computeAssemblyJacobian(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, size_t constraintIdx, boolean_T
  forVelocitySatisfaction, const double *state, const int *modeVector, const
  double *motionData, double *J)
{
  (void) mech;
  (void) rtdv;
  (void) state;
  (void) modeVector;
  (void) forVelocitySatisfaction;
  (void) motionData;
  (void) J;
  switch (constraintIdx)
  {
  }

  return 0;
}

size_t dp_a151ee3d_1_computeFullAssemblyJacobian(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, const double *state, const int *modeVector,
  const double *motionData, double *J)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) mech;
  (void) rtdvd;
  (void) rtdvi;
  (void) state;
  (void) modeVector;
  (void) motionData;
  (void) J;
  return 0;
}

boolean_T dp_a151ee3d_1_isInKinematicSingularity(const void *mech, const
  RuntimeDerivedValuesBundle *rtdv, size_t constraintIdx, const int *modeVector,
  const double *motionData)
{
  (void) mech;
  (void) rtdv;
  (void) modeVector;
  (void) motionData;
  switch (constraintIdx)
  {
  }

  return 0;
}

void dp_a151ee3d_1_convertStateVector(const void *asmMech, const
  RuntimeDerivedValuesBundle *rtdv, const void *simMech, const double *asmState,
  const int *asmModeVector, const int *simModeVector, double *simState)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  (void) asmMech;
  (void) rtdvd;
  (void) rtdvi;
  (void) simMech;
  (void) asmModeVector;
  (void) simModeVector;
  simState[0] = asmState[0];
  simState[1] = asmState[1];
  simState[2] = asmState[2];
  simState[3] = asmState[3];
}
