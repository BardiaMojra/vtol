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

PmfMessageId dp_a151ee3d_1_compDerivs(const RuntimeDerivedValuesBundle *rtdv,
  const int *eqnEnableFlags, const double *state, const int *modeVector, const
  double *input, const double *inputDot, const double *inputDdot, const double
  *discreteState, double *deriv, double *errorResult, NeuDiagnosticManager
  *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  int ii[1];
  double xx[28];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
  xx[0] = 1.248;
  xx[1] = 2.0;
  xx[2] = 0.1;
  xx[3] = 0.5;
  xx[4] = xx[3] * state[2];
  xx[5] = sin(xx[4]);
  xx[6] = xx[2] * xx[5];
  xx[7] = 0.2 - xx[1] * xx[6] * xx[5];
  xx[8] = state[1] * xx[7] * state[1];
  xx[9] = xx[8] * xx[5];
  xx[10] = cos(xx[4]);
  xx[4] = xx[1] * xx[6] * xx[10];
  xx[6] = xx[4] * state[1] * state[1];
  xx[11] = xx[6] * xx[5];
  xx[12] = xx[0] * (xx[1] * (xx[9] * xx[10] + xx[11] * xx[5]) - xx[6]);
  xx[6] = 5.950114242193449 * xx[12];
  xx[13] = xx[12] - 0.1248 * xx[6];
  xx[12] = xx[0] * (xx[1] * (xx[9] * xx[5] - xx[11] * xx[10]) - xx[8] - xx[2] *
                    state[3] * (state[1] + state[1] + state[3]));
  xx[8] = xx[12] * xx[5];
  xx[9] = xx[13] * xx[5];
  xx[11] = xx[13] + xx[1] * (xx[8] * xx[10] - xx[9] * xx[5]);
  xx[13] = 4.3264e-3;
  xx[14] = xx[2] * state[1] * state[1];
  xx[15] = xx[1] * xx[10] * xx[5];
  xx[16] = xx[0] * xx[15];
  xx[17] = xx[10] * xx[10];
  xx[18] = 1.0;
  xx[19] = xx[1] * xx[17] - xx[18];
  xx[20] = 0.3212673267326732;
  xx[21] = xx[20] * xx[19];
  xx[22] = xx[16] * xx[19] - xx[21] * xx[15];
  xx[23] = xx[0] * xx[19];
  xx[24] = xx[20] * xx[15];
  xx[20] = xx[22] * xx[7] - xx[4] * (xx[23] * xx[19] + xx[24] * xx[15]);
  xx[25] = 0.03212673267326733;
  xx[26] = xx[1] * (xx[17] + xx[5] * xx[5]) - xx[18];
  xx[17] = xx[25] * xx[15] * xx[26];
  xx[18] = xx[20] + xx[17];
  xx[27] = xx[23] * xx[15] - xx[24] * xx[19];
  xx[23] = xx[25] * xx[19] * xx[26];
  xx[24] = xx[4] * xx[17] + xx[23] * xx[7];
  xx[17] = xx[16] * xx[15] + xx[21] * xx[19];
  xx[15] = xx[17] * xx[7] - xx[4] * xx[27];
  xx[16] = xx[15] - xx[23];
  xx[19] = xx[16] + xx[2] * (xx[0] + xx[17]);
  xx[0] = 3.212673267326733e-3 * xx[26] * xx[26] - xx[24] - xx[24] + xx[7] * xx
    [15] - xx[4] * xx[20] + xx[2] * xx[16] + xx[2] * xx[19] + xx[13];
  ii[0] = factorSymmetricPosDef(xx + 0, 1, xx + 15);
  if (ii[0] != 0) {
    return sm_ssci_recordRunTimeError(
      "sm:compiler:messages:simulationErrors:DegenerateMass",
      "'dp/J1' has a degenerate mass distribution on its follower side.",
      neDiagMgr);
  }

  xx[15] = 9.806649999999999;
  xx[16] = xx[3] * state[0];
  xx[3] = sin(xx[16]);
  xx[17] = xx[15] * xx[3];
  xx[20] = xx[1] * xx[17] * cos(xx[16]);
  xx[16] = xx[15] - xx[1] * xx[17] * xx[3];
  xx[3] = (xx[11] * xx[7] - xx[4] * (xx[12] - xx[1] * (xx[9] * xx[10] + xx[8] *
             xx[5])) - xx[13] * xx[6] - xx[14] * xx[18] + xx[2] * (xx[11] - xx
            [14] * xx[27])) / xx[0] + xx[20] * (xx[18] + xx[2] * xx[22]) / xx[0]
    + xx[16] * xx[19] / xx[0];
  xx[0] = xx[16] - xx[2] * xx[3] - xx[3] * xx[7];
  deriv[0] = state[1];
  deriv[1] = - xx[3];
  deriv[2] = state[3];
  deriv[3] = - (xx[6] + 7.425742574257425 * (xx[0] - xx[1] * ((xx[20] - xx[14] +
    xx[4] * xx[3]) * xx[5] * xx[10] + xx[0] * xx[5] * xx[5])) -
                0.2574257425742574 * xx[3]);
  errorResult[0] = 0.0;
  return NULL;
}

PmfMessageId dp_a151ee3d_1_numJacPerturbLoBounds(const
  RuntimeDerivedValuesBundle *rtdv, const int *eqnEnableFlags, const double
  *state, const int *modeVector, const double *input, const double *inputDot,
  const double *inputDdot, const double *discreteState, double *bounds, double
  *errorResult, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[1];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) state;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
  xx[0] = 1.0e-8;
  bounds[0] = xx[0];
  bounds[1] = xx[0];
  bounds[2] = xx[0];
  bounds[3] = xx[0];
  errorResult[0] = 0.0;
  return NULL;
}

PmfMessageId dp_a151ee3d_1_numJacPerturbHiBounds(const
  RuntimeDerivedValuesBundle *rtdv, const int *eqnEnableFlags, const double
  *state, const int *modeVector, const double *input, const double *inputDot,
  const double *inputDdot, const double *discreteState, double *bounds, double
  *errorResult, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  double xx[2];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) state;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) discreteState;
  (void) neDiagMgr;
  xx[0] = 1.0;
  xx[1] = +pmf_get_inf();
  bounds[0] = xx[0];
  bounds[1] = xx[1];
  bounds[2] = xx[0];
  bounds[3] = xx[1];
  errorResult[0] = 0.0;
  return NULL;
}
