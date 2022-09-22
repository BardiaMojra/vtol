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

void dp_a151ee3d_1_computeRuntimeParameters(const real_T t0[], real_T out[])
{
  real_T t5[1];
  real_T t6[1];
  real_T t7[1];
  real_T t8[1];
  real_T t9[1];
  real_T t16;
  real_T t17;
  real_T t18;
  real_T t19;
  t7[0UL] = t0[0UL];
  t8[0UL] = t0[1UL];
  t9[0UL] = t0[2UL];
  t5[0UL] = t0[3UL];
  memcpy(&t6[0], &t7[0], 8U);
  memcpy(&t7[0], &t8[0], 8U);
  memcpy(&t8[0], &t9[0], 8U);
  memcpy(&t9[0], &t5[0], 8U);
  t16 = t6[0UL];
  t17 = t7[0UL];
  t18 = t8[0UL];
  t19 = t9[0UL];
  out[0] = t16;
  out[1] = t17;
  out[2] = t18;
  out[3] = t19;
}

void dp_a151ee3d_1_computeAsmRuntimeDerivedValuesDoubles(const double *rtp,
  double *rtdvd)
{
  boolean_T bb[2];
  double xx[6];
  xx[0] = rtp[0];
  bb[0] = sm_core_math_anyIsInf(1, xx + 0);
  bb[1] = sm_core_math_anyIsNaN(1, xx + 0);
  xx[0] = 0.0174532925199433;
  xx[1] = 0.0;
  xx[2] = !bb[0] && !bb[1] ? xx[0] * rtp[0] : xx[1];
  xx[3] = rtp[1];
  bb[0] = sm_core_math_anyIsInf(1, xx + 3);
  bb[1] = sm_core_math_anyIsNaN(1, xx + 3);
  xx[3] = !bb[0] && !bb[1] ? xx[0] * rtp[1] : xx[1];
  xx[4] = rtp[2];
  bb[0] = sm_core_math_anyIsInf(1, xx + 4);
  bb[1] = sm_core_math_anyIsNaN(1, xx + 4);
  xx[4] = !bb[0] && !bb[1] ? xx[0] * rtp[2] : xx[1];
  xx[5] = rtp[3];
  bb[0] = sm_core_math_anyIsInf(1, xx + 5);
  bb[1] = sm_core_math_anyIsNaN(1, xx + 5);
  xx[5] = !bb[0] && !bb[1] ? xx[0] * rtp[3] : xx[1];
  xx[0] = 57.29577951308232;
  rtdvd[0] = xx[2];
  rtdvd[1] = xx[3];
  rtdvd[2] = xx[4];
  rtdvd[3] = xx[5];
  rtdvd[4] = xx[0] * xx[2];
  rtdvd[5] = xx[0] * xx[3];
  rtdvd[6] = xx[0] * xx[4];
  rtdvd[7] = xx[0] * xx[5];
}

void dp_a151ee3d_1_computeAsmRuntimeDerivedValuesInts(const double *rtp, int
  *rtdvi)
{
  (void) rtp;
  (void) rtdvi;
}

void dp_a151ee3d_1_computeAsmRuntimeDerivedValues(const double *rtp,
  RuntimeDerivedValuesBundle *rtdv)
{
  dp_a151ee3d_1_computeAsmRuntimeDerivedValuesDoubles(rtp,
    rtdv->mDoubles.mValues);
  dp_a151ee3d_1_computeAsmRuntimeDerivedValuesInts(rtp, rtdv->mInts.mValues);
}

void dp_a151ee3d_1_computeSimRuntimeDerivedValuesDoubles(const double *rtp,
  double *rtdvd)
{
  (void) rtp;
  (void) rtdvd;
}

void dp_a151ee3d_1_computeSimRuntimeDerivedValuesInts(const double *rtp, int
  *rtdvi)
{
  (void) rtp;
  (void) rtdvi;
}

void dp_a151ee3d_1_computeSimRuntimeDerivedValues(const double *rtp,
  RuntimeDerivedValuesBundle *rtdv)
{
  dp_a151ee3d_1_computeSimRuntimeDerivedValuesDoubles(rtp,
    rtdv->mDoubles.mValues);
  dp_a151ee3d_1_computeSimRuntimeDerivedValuesInts(rtp, rtdv->mInts.mValues);
}
