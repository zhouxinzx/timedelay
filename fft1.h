//
// File: fft1.h
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//
#ifndef FFT1_H
#define FFT1_H

// Include Files
#include <cmath>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "timedelay_types.h"

// Function Declarations
extern void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
extern void b_generate_twiddle_tables(int nRows, boolean_T useRadix2,
  emxArray_real_T *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv);
extern void c_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);
extern void dobluesteinfft(const double x_data[], const int x_size[1], int N2,
  int n1, const emxArray_real_T *costab, const emxArray_real_T *sintab, const
  emxArray_real_T *sintabinv, emxArray_creal_T *y);
extern void generate_twiddle_tables(int nRows, boolean_T useRadix2,
  emxArray_real_T *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv);
extern void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows);
extern void r2br_r2dit_trig(const double x_data[], const int x_size[1], int
  n1_unsigned, const emxArray_real_T *costab, const emxArray_real_T *sintab,
  emxArray_creal_T *y);

#endif

//
// File trailer for fft1.h
//
// [EOF]
//
