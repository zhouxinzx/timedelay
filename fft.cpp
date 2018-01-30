//
// File: fft.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//

// Include Files
#include "rt_nonfinite.h"
#include "timedelay.h"
#include "fft.h"
#include "timedelay_emxutil.h"
#include "fft1.h"

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                double varargin_1
//                emxArray_creal_T *y
// Return Type  : void
//
void fft(const double x_data[], const int x_size[1], double varargin_1,
         emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  emxInit_real_T1(&costab, 2);
  emxInit_real_T1(&sintab, 2);
  emxInit_real_T1(&sintabinv, 2);
  if ((x_size[0] == 0) || ((int)varargin_1 == 0)) {
    N2blue = y->size[0];
    y->size[0] = (int)varargin_1;
    emxEnsureCapacity_creal_T(y, N2blue);
    if ((int)varargin_1 > x_size[0]) {
      nRows = y->size[0];
      N2blue = y->size[0];
      y->size[0] = nRows;
      emxEnsureCapacity_creal_T(y, N2blue);
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        y->data[N2blue].re = 0.0;
        y->data[N2blue].im = 0.0;
      }
    }
  } else {
    useRadix2 = (((int)varargin_1 & ((int)varargin_1 - 1)) == 0);
    get_algo_sizes((int)varargin_1, useRadix2, &N2blue, &nRows);
    generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      r2br_r2dit_trig(x_data, x_size, (int)varargin_1, costab, sintab, y);
    } else {
      dobluesteinfft(x_data, x_size, N2blue, (int)varargin_1, costab, sintab,
                     sintabinv, y);
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

//
// File trailer for fft.cpp
//
// [EOF]
//
