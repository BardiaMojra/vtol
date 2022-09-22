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

void dp_a151ee3d_1_validateRuntimeParameters(const double *rtp, int32_T
  *satFlags)
{
  boolean_T bb[8];
  double xx[1];
  xx[0] = rtp[0];
  bb[0] = sm_core_math_anyIsInf(1, xx + 0);
  bb[1] = sm_core_math_anyIsNaN(1, xx + 0);
  xx[0] = rtp[1];
  bb[2] = sm_core_math_anyIsInf(1, xx + 0);
  bb[3] = sm_core_math_anyIsNaN(1, xx + 0);
  xx[0] = rtp[2];
  bb[4] = sm_core_math_anyIsInf(1, xx + 0);
  bb[5] = sm_core_math_anyIsNaN(1, xx + 0);
  xx[0] = rtp[3];
  bb[6] = sm_core_math_anyIsInf(1, xx + 0);
  bb[7] = sm_core_math_anyIsNaN(1, xx + 0);
  satFlags[0] = !bb[0] ? 1 : 0;
  satFlags[1] = !bb[1] ? 1 : 0;
  satFlags[2] = !bb[2] ? 1 : 0;
  satFlags[3] = !bb[3] ? 1 : 0;
  satFlags[4] = !bb[4] ? 1 : 0;
  satFlags[5] = !bb[5] ? 1 : 0;
  satFlags[6] = !bb[6] ? 1 : 0;
  satFlags[7] = !bb[7] ? 1 : 0;
}

const NeAssertData dp_a151ee3d_1_assertData[8] = {
  { "dp/J1", 0, 0, "J1", "", false,
    "The parameter Rz/Position contains an Inf value, which is not allowed.",
    "sm:model:evaluate:InvalidValueInf" },

  { "dp/J1", 0, 0, "J1", "", false,
    "The parameter Rz/Position contains a NaN value, which is not allowed.",
    "sm:model:evaluate:InvalidValueNaN" },

  { "dp/J1", 0, 0, "J1", "", false,
    "The parameter Rz/Velocity contains an Inf value, which is not allowed.",
    "sm:model:evaluate:InvalidValueInf" },

  { "dp/J1", 0, 0, "J1", "", false,
    "The parameter Rz/Velocity contains a NaN value, which is not allowed.",
    "sm:model:evaluate:InvalidValueNaN" },

  { "dp/J2", 0, 0, "J2", "", false,
    "The parameter Rz/Position contains an Inf value, which is not allowed.",
    "sm:model:evaluate:InvalidValueInf" },

  { "dp/J2", 0, 0, "J2", "", false,
    "The parameter Rz/Position contains a NaN value, which is not allowed.",
    "sm:model:evaluate:InvalidValueNaN" },

  { "dp/J2", 0, 0, "J2", "", false,
    "The parameter Rz/Velocity contains an Inf value, which is not allowed.",
    "sm:model:evaluate:InvalidValueInf" },

  { "dp/J2", 0, 0, "J2", "", false,
    "The parameter Rz/Velocity contains a NaN value, which is not allowed.",
    "sm:model:evaluate:InvalidValueNaN" }
};
