//
// File: ifft.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//

// Include Files
#include "rt_nonfinite.h"
#include "timedelay.h"
#include "ifft.h"
#include "timedelay_emxutil.h"
#include "fft1.h"

// Function Definitions

//
// Arguments    : const emxArray_creal_T *x
//                emxArray_creal_T *y
// Return Type  : void
//
void ifft(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  emxArray_creal_T *b_y;
  emxArray_real_T *costab;
  int N2blue;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T useRadix2;
  int nRows;
  emxInit_creal_T(&b_y, 1);
  if (x->size[0] == 0) {
    N2blue = b_y->size[0];
    b_y->size[0] = 0;
    emxEnsureCapacity_creal_T(b_y, N2blue);
    N2blue = y->size[0];
    y->size[0] = b_y->size[0];
    emxEnsureCapacity_creal_T(y, N2blue);
    nRows = b_y->size[0];
    for (N2blue = 0; N2blue < nRows; N2blue++) {
      y->data[N2blue] = b_y->data[N2blue];
    }
  } else {
    emxInit_real_T1(&costab, 2);
    emxInit_real_T1(&sintab, 2);
    emxInit_real_T1(&sintabinv, 2);
    useRadix2 = ((x->size[0] & (x->size[0] - 1)) == 0);
    get_algo_sizes(x->size[0], useRadix2, &N2blue, &nRows);
    b_generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      c_r2br_r2dit_trig(x, x->size[0], costab, sintab, b_y);
      N2blue = y->size[0];
      y->size[0] = b_y->size[0];
      emxEnsureCapacity_creal_T(y, N2blue);
      nRows = b_y->size[0];
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        y->data[N2blue] = b_y->data[N2blue];
      }
    } else {
      b_dobluesteinfft(x, N2blue, x->size[0], costab, sintab, sintabinv, y);
    }

    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }

  emxFree_creal_T(&b_y);
}

//
// File trailer for ifft.cpp
//
// [EOF]
//
