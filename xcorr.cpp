//
// File: xcorr.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//

// Include Files
#include "rt_nonfinite.h"
#include "timedelay.h"
#include "xcorr.h"
#include "timedelay_emxutil.h"
#include "ifft.h"
#include "fft.h"
#include "mpower.h"
#include "nextpow2.h"

// Function Declarations
static double OpCountForXcorrTD(double maxlag, double m1, double n1);
static void crosscorr(const double x_data[], const int x_size[1], const double
                      y_data[], const int y_size[1], double maxlag, double
                      c_data[], int c_size[1]);
static void crosscorrTD(const double x_data[], const int x_size[1], const double
  y_data[], const int y_size[1], double maxlag, double c_data[], int c_size[1]);
static void padOutput(const double c1_data[], const int c1_size[1], double
                      maxlag, double defaultMaxlag, double c_data[], int c_size
                      [1]);

// Function Definitions

//
// Arguments    : double maxlag
//                double m1
//                double n1
// Return Type  : double
//
static double OpCountForXcorrTD(double maxlag, double m1, double n1)
{
  double c;
  double m;
  double n;
  double c0;
  double Sn;
  if ((m1 > n1) || rtIsNaN(n1)) {
    m = m1;
  } else {
    m = n1;
  }

  if ((m1 < n1) || rtIsNaN(n1)) {
    n = m1;
  } else {
    n = n1;
  }

  c0 = 2.0 * n - 1.0;
  if (maxlag <= n - 1.0) {
    Sn = maxlag * ((c0 - maxlag) - 1.0);
    if (maxlag <= m - n) {
      c = (c0 + maxlag * c0) + Sn;
    } else {
      c = ((c0 + (m - n) * c0) + (maxlag - (m - n)) * (((m - maxlag) + n) - 2.0))
        + Sn;
    }
  } else if (maxlag <= m - 1.0) {
    Sn = (n - 1.0) * (n - 1.0);
    if (maxlag <= m - n) {
      c = (c0 + maxlag * c0) + Sn;
    } else {
      c = ((c0 + (m - n) * c0) + (maxlag - (m - n)) * (((m - maxlag) + n) - 2.0))
        + Sn;
    }
  } else {
    c = 2.0 * m * n - ((m + n) - 1.0);
  }

  return c;
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                const double y_data[]
//                const int y_size[1]
//                double maxlag
//                double c_data[]
//                int c_size[1]
// Return Type  : void
//
static void crosscorr(const double x_data[], const int x_size[1], const double
                      y_data[], const int y_size[1], double maxlag, double
                      c_data[], int c_size[1])
{
  int u0;
  int m;
  double mxl;
  double ceilLog2;
  double m2;
  emxArray_creal_T *X;
  emxArray_creal_T *Y;
  emxArray_creal_T *b_X;
  emxArray_real_T *c1;
  double Y_im;
  double X_re;
  double X_im;
  int tmp_size_idx_1;
  int tmp_data[2999];
  u0 = x_size[0];
  m = y_size[0];
  if (u0 > m) {
    m = u0;
  }

  mxl = (double)m - 1.0;
  if (maxlag < mxl) {
    mxl = maxlag;
  }

  ceilLog2 = nextpow2(2.0 * (double)m - 1.0);
  m2 = mpower(ceilLog2);
  if (OpCountForXcorrTD(mxl, (double)x_size[0], (double)y_size[0]) < m2 * (15.0 *
       ceilLog2 + 6.0)) {
    crosscorrTD(x_data, x_size, y_data, y_size, mxl, c_data, c_size);
  } else {
    emxInit_creal_T(&X, 1);
    emxInit_creal_T(&Y, 1);
    emxInit_creal_T(&b_X, 1);
    fft(x_data, x_size, m2, X);
    fft(y_data, y_size, m2, Y);
    u0 = b_X->size[0];
    b_X->size[0] = X->size[0];
    emxEnsureCapacity_creal_T(b_X, u0);
    m = X->size[0];
    for (u0 = 0; u0 < m; u0++) {
      ceilLog2 = Y->data[u0].re;
      Y_im = -Y->data[u0].im;
      X_re = X->data[u0].re;
      X_im = X->data[u0].im;
      b_X->data[u0].re = X_re * ceilLog2 - X_im * Y_im;
      b_X->data[u0].im = X_re * Y_im + X_im * ceilLog2;
    }

    emxFree_creal_T(&Y);
    emxInit_real_T(&c1, 1);
    ifft(b_X, X);
    u0 = c1->size[0];
    c1->size[0] = X->size[0];
    emxEnsureCapacity_real_T(c1, u0);
    m = X->size[0];
    emxFree_creal_T(&b_X);
    for (u0 = 0; u0 < m; u0++) {
      c1->data[u0] = X->data[u0].re;
    }

    emxFree_creal_T(&X);
    if (mxl < 1.0) {
      tmp_size_idx_1 = 0;
    } else {
      tmp_size_idx_1 = (int)std::floor(mxl - 1.0) + 1;
      m = (int)std::floor(mxl - 1.0);
      for (u0 = 0; u0 <= m; u0++) {
        tmp_data[u0] = 1 + u0;
      }
    }

    if (1.0 > mxl + 1.0) {
      m = 0;
    } else {
      m = (int)(mxl + 1.0);
    }

    m2 -= mxl;
    c_size[0] = tmp_size_idx_1 + m;
    for (u0 = 0; u0 < tmp_size_idx_1; u0++) {
      c_data[u0] = c1->data[(int)(m2 + (double)tmp_data[u0]) - 1];
    }

    for (u0 = 0; u0 < m; u0++) {
      c_data[u0 + tmp_size_idx_1] = c1->data[u0];
    }

    emxFree_real_T(&c1);
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                const double y_data[]
//                const int y_size[1]
//                double maxlag
//                double c_data[]
//                int c_size[1]
// Return Type  : void
//
static void crosscorrTD(const double x_data[], const int x_size[1], const double
  y_data[], const int y_size[1], double maxlag, double c_data[], int c_size[1])
{
  int m;
  int n;
  int u0;
  int maxmn;
  double mxl;
  double nc;
  double ihi;
  m = x_size[0];
  n = y_size[0];
  u0 = x_size[0];
  maxmn = y_size[0];
  if (u0 > maxmn) {
    maxmn = u0;
  }

  mxl = (double)maxmn - 1.0;
  if (maxlag < mxl) {
    mxl = maxlag;
  }

  nc = 2.0 * mxl + 1.0;
  c_size[0] = (int)nc;
  maxmn = (int)nc;
  if (0 <= maxmn - 1) {
    memset(&c_data[0], 0, (unsigned int)(maxmn * (int)sizeof(double)));
  }

  for (maxmn = 0; maxmn < (int)(mxl + 1.0); maxmn++) {
    nc = (double)m - (double)maxmn;
    ihi = n;
    if (nc < ihi) {
      ihi = nc;
    }

    nc = 0.0;
    for (u0 = 0; u0 < (int)ihi; u0++) {
      nc += y_data[u0] * x_data[(int)((double)maxmn + (1.0 + (double)u0)) - 1];
    }

    c_data[(int)((mxl + (double)maxmn) + 1.0) - 1] = nc;
  }

  for (maxmn = 0; maxmn < (int)mxl; maxmn++) {
    ihi = (double)n - (1.0 + (double)maxmn);
    nc = m;
    if (nc < ihi) {
      ihi = nc;
    }

    nc = 0.0;
    for (u0 = 0; u0 < (int)ihi; u0++) {
      nc += y_data[(int)((1.0 + (double)maxmn) + (1.0 + (double)u0)) - 1] *
        x_data[u0];
    }

    c_data[(int)((mxl - (1.0 + (double)maxmn)) + 1.0) - 1] = nc;
  }
}

//
// Arguments    : const double c1_data[]
//                const int c1_size[1]
//                double maxlag
//                double defaultMaxlag
//                double c_data[]
//                int c_size[1]
// Return Type  : void
//
static void padOutput(const double c1_data[], const int c1_size[1], double
                      maxlag, double defaultMaxlag, double c_data[], int c_size
                      [1])
{
  int loop_ub;
  double offset;
  c_size[0] = (int)(2.0 * maxlag + 1.0);
  loop_ub = (int)(2.0 * maxlag + 1.0);
  if (0 <= loop_ub - 1) {
    memset(&c_data[0], 0, (unsigned int)(loop_ub * (int)sizeof(double)));
  }

  if (maxlag > defaultMaxlag) {
    offset = maxlag - defaultMaxlag;
    for (loop_ub = 0; loop_ub < c1_size[0]; loop_ub++) {
      c_data[(int)(offset + (1.0 + (double)loop_ub)) - 1] = c1_data[loop_ub];
    }
  } else {
    loop_ub = c1_size[0] - 1;
    if (0 <= loop_ub) {
      memcpy(&c_data[0], &c1_data[0], (unsigned int)((loop_ub + 1) * (int)sizeof
              (double)));
    }
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                const double varargin_1_data[]
//                const int varargin_1_size[1]
//                int varargin_2
//                double c_data[]
//                int c_size[1]
// Return Type  : void
//
void xcorr(const double x_data[], const int x_size[1], const double
           varargin_1_data[], const int varargin_1_size[1], int varargin_2,
           double c_data[], int c_size[1])
{
  unsigned int maxlag;
  int varargin_1[1];
  double c1_data[5999];
  int c1_size[1];
  int u0;
  int u1;
  maxlag = (unsigned int)std::abs((double)varargin_2);
  varargin_1[0] = varargin_1_size[0];
  crosscorr(x_data, x_size, varargin_1_data, varargin_1, (double)maxlag, c1_data,
            c1_size);
  u0 = x_size[0];
  u1 = varargin_1_size[0];
  if (u0 > u1) {
    u1 = u0;
  }

  padOutput(c1_data, c1_size, (double)maxlag, (double)u1 - 1.0, c_data, c_size);
}

//
// File trailer for xcorr.cpp
//
// [EOF]
//
