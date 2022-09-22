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
#include "dp_a151ee3d_1_geometries.h"

PmfMessageId dp_a151ee3d_1_compOutputs(const RuntimeDerivedValuesBundle *rtdv,
  const double *state, const int *modeVector, const double *input, const double *
  inputDot, const double *inputDdot, const double *discreteState, double *output,
  NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[15];
  (void) rtdvd;
  (void) rtdvi;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
  xx[0] = 0.1;
  xx[1] = 2.0;
  xx[2] = 0.5;
  xx[3] = xx[2] * state[0];
  xx[4] = sin(xx[3]);
  xx[5] = xx[0] * xx[4];
  xx[6] = xx[1] * xx[5] * xx[4];
  xx[7] = xx[6] - xx[0];
  xx[8] = cos(xx[3]);
  xx[3] = xx[1] * xx[5] * xx[8];
  xx[5] = xx[2] * state[2];
  xx[2] = sin(xx[5]);
  xx[9] = xx[0] * xx[2];
  xx[10] = 0.2 - xx[1] * xx[9] * xx[2];
  xx[11] = cos(xx[5]);
  xx[5] = xx[1] * xx[9] * xx[11];
  xx[9] = xx[5] * xx[4];
  xx[12] = xx[10] * xx[4];
  xx[13] = xx[8] * xx[2] + xx[11] * xx[4];
  xx[14] = xx[0] * xx[13];
  output[0] = state[0];
  output[1] = state[2];
  output[2] = xx[0] - xx[6] - xx[7];
  output[3] = xx[3] + xx[3];
  output[4] = xx[10] - xx[1] * (xx[9] * xx[8] + xx[12] * xx[4]) - (xx[1] * xx[14]
    * xx[13] + xx[7]) + xx[0];
  output[5] = xx[1] * xx[14] * (xx[8] * xx[11] - xx[4] * xx[2]) + xx[1] * (xx[12]
    * xx[8] - xx[9] * xx[4]) + xx[5] + xx[3];
  return NULL;
}
