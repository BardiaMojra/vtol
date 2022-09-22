/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: dp_capi.c
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

#include <stddef.h>
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "dp_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#ifndef SS_UINT64
#define SS_UINT64                      17
#endif

#ifndef SS_INT64
#define SS_INT64                       18
#endif

#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "dp.h"
#include "dp_capi.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Block output signal information */
static rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, TARGET_STRING("dp/Solver Configuration/RTP_1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 1, 0, TARGET_STRING("dp/Solver Configuration/EVAL_KEY/STATE_1"),
    TARGET_STRING(""), 0, 0, 1, 0, 1 },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

/* Individual block tuning is not valid when inline parameters is *
 * selected. An empty map is produced to provide a consistent     *
 * interface independent  of inlining parameters.                 *
 */
static rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Block states information */
static rtwCAPI_States rtBlockStates[] = {
  /* addrMapIndex, contStateStartIndex, blockPath,
   * stateName, pathAlias, dWorkIndex, dataTypeIndex, dimIndex,
   * fixPtIdx, sTimeIndex, isContinuous, hierInfoIdx, flatElemIdx
   */
  { 2, 0, TARGET_STRING("dp/Solver\nConfiguration/EVAL_KEY/STATE_1"),
    TARGET_STRING("dp.J1.Rz.q"),
    TARGET_STRING("dp/J1"),
    0, 0, 2, 0, 1, 1, -1, 0 },

  { 3, 1, TARGET_STRING("dp/Solver\nConfiguration/EVAL_KEY/STATE_1"),
    TARGET_STRING("dp.J1.Rz.w"),
    TARGET_STRING("dp/J1"),
    0, 0, 2, 0, 1, 1, -1, 0 },

  { 4, 2, TARGET_STRING("dp/Solver\nConfiguration/EVAL_KEY/STATE_1"),
    TARGET_STRING("dp.J2.Rz.q"),
    TARGET_STRING("dp/J2"),
    0, 0, 2, 0, 1, 1, -1, 0 },

  { 5, 3, TARGET_STRING("dp/Solver\nConfiguration/EVAL_KEY/STATE_1"),
    TARGET_STRING("dp.J2.Rz.w"),
    TARGET_STRING("dp/J2"),
    0, 0, 2, 0, 1, 1, -1, 0 },

  {
    0, -1, (NULL), (NULL), (NULL), 0, 0, 0, 0, 0, 0, -1, 0
  }
};

/* Tunable variable parameters */
static rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Initialize Data Address */
static void InitializeDataAddr(void* dataAddr[], DW *rtDW, X *rtX)
{
  dataAddr[0] = (void*) (&rtDW->RTP_1);
  dataAddr[1] = (void*) (&rtDW->STATE_1[0]);
  dataAddr[2] = (void*) (&rtX->dpJ1Rzq[0]);
  dataAddr[3] = (void*) (&rtX->dpJ1Rzq[1]);
  dataAddr[4] = (void*) (&rtX->dpJ1Rzq[2]);
  dataAddr[5] = (void*) (&rtX->dpJ1Rzq[3]);
}

#endif

/* Initialize Data Run-Time Dimension Buffer Address */
#ifndef HOST_CAPI_BUILD

static void InitializeVarDimsAddr(int32_T* vardimsAddr[])
{
  vardimsAddr[0] = (NULL);
}

#endif

#ifndef HOST_CAPI_BUILD

/* Initialize logging function pointers */
static void InitializeLoggingFunctions(RTWLoggingFcnPtr loggingPtrs[])
{
  loggingPtrs[0] = (NULL);
  loggingPtrs[1] = (NULL);
  loggingPtrs[2] = (NULL);
  loggingPtrs[3] = (NULL);
  loggingPtrs[4] = (NULL);
  loggingPtrs[5] = (NULL);
}

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer, enumStorageType */
  { "double", "real_T", 0, 0, sizeof(real_T), (uint8_T)SS_DOUBLE, 0, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 0, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  4,                                   /* 2 */
  1                                    /* 3 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.01, 0.0
};

/* Fixed Point Map */
static rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, (boolean_T)0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    (int8_T)1, (uint8_T)0 },

  { (const void *) &rtcapiStoredFloats[1], (const void *) &rtcapiStoredFloats[1],
    (int8_T)0, (uint8_T)0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { rtBlockSignals, 2,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 0,
    rtModelParameters, 0 },

  { rtBlockStates, 4 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 620876257U,
    3792811495U,
    152514045U,
    2844669954U },
  (NULL), 0,
  (boolean_T)0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  dp_GetCAPIStaticMap(void)
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void dp_InitializeDataMapInfo(RT_MODEL *const rtM, X *rtX)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(rtM->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(rtM->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(rtM->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  InitializeDataAddr(rtM->DataMapInfo.dataAddress, rtM->dwork, (X *)
                     rtM->contStates);
  rtwCAPI_SetDataAddressMap(rtM->DataMapInfo.mmi, rtM->DataMapInfo.dataAddress);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  InitializeVarDimsAddr(rtM->DataMapInfo.vardimsAddress);
  rtwCAPI_SetVarDimsAddressMap(rtM->DataMapInfo.mmi,
    rtM->DataMapInfo.vardimsAddress);

  /* Set Instance specific path */
  rtwCAPI_SetPath(rtM->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetFullPath(rtM->DataMapInfo.mmi, (NULL));

  /* Cache C-API logging function pointers into the Real-Time Model Data structure */
  InitializeLoggingFunctions(rtM->DataMapInfo.loggingPtrs);
  rtwCAPI_SetLoggingPtrs(rtM->DataMapInfo.mmi, rtM->DataMapInfo.loggingPtrs);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(rtM->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(rtM->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(rtM->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C"
{

#endif

  void dp_host_InitializeDataMapInfo(dp_host_DataMapInfo_T *dataMap, const char *
    path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, (NULL));

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, (NULL));

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, (NULL));

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}

#endif
#endif                                 /* HOST_CAPI_BUILD */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
