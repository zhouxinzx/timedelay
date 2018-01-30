/*
 * File: _coder_timedelay_api.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 27-Jan-2018 19:57:38
 */

#ifndef _CODER_TIMEDELAY_API_H
#define _CODER_TIMEDELAY_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_timedelay_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T timedelay(real_T x_data[], int32_T x_size[2], real_T y_data[],
  int32_T y_size[2]);
extern void timedelay_api(const mxArray * const prhs[2], const mxArray *plhs[1]);
extern void timedelay_atexit(void);
extern void timedelay_initialize(void);
extern void timedelay_terminate(void);
extern void timedelay_xil_terminate(void);

#endif

/*
 * File trailer for _coder_timedelay_api.h
 *
 * [EOF]
 */
