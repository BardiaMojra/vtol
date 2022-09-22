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

PmfMessageId dp_a151ee3d_1_recordLog(const RuntimeDerivedValuesBundle *rtdv,
  const int *eqnEnableFlags, const double *state, const int *modeVector, const
  double *input, const double *inputDot, const double *inputDdot, double
  *logVector, double *errorResult, NeuDiagnosticManager *neDiagMgr)
{
  const double *rtdvd = rtdv->mDoubles.mValues;
  const int *rtdvi = rtdv->mInts.mValues;
  int ii[1];
  double xx[29];
  (void) rtdvd;
  (void) rtdvi;
  (void) eqnEnableFlags;
  (void) modeVector;
  (void) input;
  (void) inputDot;
  (void) inputDdot;
  (void) neDiagMgr;
  xx[0] = 57.29577951308232;
  xx[1] = 1.248;
  xx[2] = 2.0;
  xx[3] = 0.1;
  xx[4] = 0.5;
  xx[5] = xx[4] * state[2];
  xx[6] = sin(xx[5]);
  xx[7] = xx[3] * xx[6];
  xx[8] = 0.2 - xx[2] * xx[7] * xx[6];
  xx[9] = state[1] * xx[8] * state[1];
  xx[10] = xx[9] * xx[6];
  xx[11] = cos(xx[5]);
  xx[5] = xx[2] * xx[7] * xx[11];
  xx[7] = xx[5] * state[1] * state[1];
  xx[12] = xx[7] * xx[6];
  xx[13] = xx[1] * (xx[2] * (xx[10] * xx[11] + xx[12] * xx[6]) - xx[7]);
  xx[7] = 5.950114242193449 * xx[13];
  xx[14] = xx[13] - 0.1248 * xx[7];
  xx[13] = xx[1] * (xx[2] * (xx[10] * xx[6] - xx[12] * xx[11]) - xx[9] - xx[3] *
                    state[3] * (state[1] + state[1] + state[3]));
  xx[9] = xx[13] * xx[6];
  xx[10] = xx[14] * xx[6];
  xx[12] = xx[14] + xx[2] * (xx[9] * xx[11] - xx[10] * xx[6]);
  xx[14] = 4.3264e-3;
  xx[15] = xx[3] * state[1] * state[1];
  xx[16] = xx[2] * xx[11] * xx[6];
  xx[17] = xx[1] * xx[16];
  xx[18] = xx[11] * xx[11];
  xx[19] = 1.0;
  xx[20] = xx[2] * xx[18] - xx[19];
  xx[21] = 0.3212673267326732;
  xx[22] = xx[21] * xx[20];
  xx[23] = xx[17] * xx[20] - xx[22] * xx[16];
  xx[24] = xx[1] * xx[20];
  xx[25] = xx[21] * xx[16];
  xx[21] = xx[23] * xx[8] - xx[5] * (xx[24] * xx[20] + xx[25] * xx[16]);
  xx[26] = 0.03212673267326733;
  xx[27] = xx[2] * (xx[18] + xx[6] * xx[6]) - xx[19];
  xx[18] = xx[26] * xx[16] * xx[27];
  xx[19] = xx[21] + xx[18];
  xx[28] = xx[24] * xx[16] - xx[25] * xx[20];
  xx[24] = xx[26] * xx[20] * xx[27];
  xx[25] = xx[5] * xx[18] + xx[24] * xx[8];
  xx[18] = xx[17] * xx[16] + xx[22] * xx[20];
  xx[16] = xx[18] * xx[8] - xx[5] * xx[28];
  xx[17] = xx[16] - xx[24];
  xx[20] = xx[17] + xx[3] * (xx[1] + xx[18]);
  xx[1] = 3.212673267326733e-3 * xx[27] * xx[27] - xx[25] - xx[25] + xx[8] * xx
    [16] - xx[5] * xx[21] + xx[3] * xx[17] + xx[3] * xx[20] + xx[14];
  ii[0] = factorSymmetricPosDef(xx + 1, 1, xx + 16);
  if (ii[0] != 0) {
    return sm_ssci_recordRunTimeError(
      "sm:compiler:messages:simulationErrors:DegenerateMass",
      "'dp/J1' has a degenerate mass distribution on its follower side.",
      neDiagMgr);
  }

  xx[16] = 9.806649999999999;
  xx[17] = xx[4] * state[0];
  xx[4] = sin(xx[17]);
  xx[18] = xx[16] * xx[4];
  xx[21] = xx[2] * xx[18] * cos(xx[17]);
  xx[17] = xx[16] - xx[2] * xx[18] * xx[4];
  xx[4] = (xx[12] * xx[8] - xx[5] * (xx[13] - xx[2] * (xx[10] * xx[11] + xx[9] *
             xx[6])) - xx[14] * xx[7] - xx[15] * xx[19] + xx[3] * (xx[12] - xx
            [15] * xx[28])) / xx[1] + xx[21] * (xx[19] + xx[3] * xx[23]) / xx[1]
    + xx[17] * xx[20] / xx[1];
  xx[1] = xx[17] - xx[3] * xx[4] - xx[4] * xx[8];
  logVector[0] = xx[0] * state[0];
  logVector[1] = xx[0] * state[1];
  logVector[2] = xx[0] * state[2];
  logVector[3] = xx[0] * state[3];
  logVector[4] = - (xx[0] * xx[4]);
  logVector[5] = - (xx[0] * (xx[7] + 7.425742574257425 * (xx[1] - xx[2] * ((xx
    [21] - xx[15] + xx[5] * xx[4]) * xx[6] * xx[11] + xx[1] * xx[6] * xx[6])) -
    0.2574257425742574 * xx[4]));
  errorResult[0] = 0.0;
  return NULL;
}
