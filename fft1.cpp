//
// File: fft1.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//

// Include Files
#include "rt_nonfinite.h"
#include "timedelay.h"
#include "fft1.h"
#include "timedelay_emxutil.h"
#include "bluesteinSetup.h"

// Function Declarations
static void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y);

// Function Definitions

//
// Arguments    : const emxArray_creal_T *x
//                int n1_unsigned
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                emxArray_creal_T *y
// Return Type  : void
//
static void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int j;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int ihi;
  j = x->size[0];
  if (!(j < n1_unsigned)) {
    j = n1_unsigned;
  }

  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iy);
  if (n1_unsigned > x->size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 1; i < j; i++) {
    y->data[iy] = x->data[ix];
    iDelta = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= n1_unsigned - 2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re = y->data[i + iDelta].re;
      temp_im = y->data[i + iDelta].im;
      y->data[i + iDelta].re = y->data[i].re - temp_re;
      y->data[i + iDelta].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re = twid_re * y->data[i + iDelta].re - twid_im * y->data[i +
          iDelta].im;
        temp_im = twid_re * y->data[i + iDelta].im + twid_im * y->data[i +
          iDelta].re;
        y->data[i + iDelta].re = y->data[i].re - temp_re;
        y->data[i + iDelta].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }
}

//
// Arguments    : const emxArray_creal_T *x
//                int unsigned_nRows
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                emxArray_creal_T *y
// Return Type  : void
//
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y)
{
  int j;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int ihi;
  j = x->size[0];
  if (!(j < unsigned_nRows)) {
    j = unsigned_nRows;
  }

  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 1; i < j; i++) {
    y->data[iy] = x->data[ix];
    iDelta = unsigned_nRows;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= unsigned_nRows - 2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re = y->data[i + iDelta].re;
      temp_im = y->data[i + iDelta].im;
      y->data[i + iDelta].re = y->data[i].re - temp_re;
      y->data[i + iDelta].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re = twid_re * y->data[i + iDelta].re - twid_im * y->data[i +
          iDelta].im;
        temp_im = twid_re * y->data[i + iDelta].im + twid_im * y->data[i +
          iDelta].re;
        y->data[i + iDelta].re = y->data[i].re - temp_re;
        y->data[i + iDelta].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }
}

//
// Arguments    : const emxArray_creal_T *x
//                int N2
//                int n1
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                const emxArray_real_T *sintabinv
//                emxArray_creal_T *y
// Return Type  : void
//
void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
                      emxArray_real_T *costab, const emxArray_real_T *sintab,
                      const emxArray_real_T *sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int minNrowsNx;
  emxArray_creal_T *fv;
  int k;
  int xidx;
  double denom_re;
  double denom_im;
  emxArray_creal_T *r1;
  double wwc_re;
  emxArray_creal_T *b_fv;
  double fv_im;
  double wwc_im;
  double fv_re;
  double b_fv_re;
  double b_fv_im;
  emxInit_creal_T(&wwc, 1);
  b_bluesteinSetup(n1, wwc);
  minNrowsNx = x->size[0];
  if (n1 < minNrowsNx) {
    minNrowsNx = n1;
  }

  emxInit_creal_T(&fv, 1);
  k = fv->size[0];
  fv->size[0] = n1;
  emxEnsureCapacity_creal_T(fv, k);
  if (n1 > x->size[0]) {
    xidx = fv->size[0];
    k = fv->size[0];
    fv->size[0] = xidx;
    emxEnsureCapacity_creal_T(fv, k);
    for (k = 0; k < xidx; k++) {
      fv->data[k].re = 0.0;
      fv->data[k].im = 0.0;
    }
  }

  k = y->size[0];
  y->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(y, k);
  xidx = fv->size[0];
  for (k = 0; k < xidx; k++) {
    y->data[k] = fv->data[k];
  }

  xidx = 0;
  for (k = 0; k + 1 <= minNrowsNx; k++) {
    denom_re = wwc->data[(n1 + k) - 1].re;
    denom_im = wwc->data[(n1 + k) - 1].im;
    wwc_re = x->data[xidx].re;
    fv_im = x->data[xidx].im;
    wwc_im = x->data[xidx].im;
    fv_re = x->data[xidx].re;
    y->data[k].re = denom_re * wwc_re + denom_im * fv_im;
    y->data[k].im = denom_re * wwc_im - denom_im * fv_re;
    xidx++;
  }

  while (minNrowsNx + 1 <= n1) {
    y->data[minNrowsNx].re = 0.0;
    y->data[minNrowsNx].im = 0.0;
    minNrowsNx++;
  }

  emxInit_creal_T(&r1, 1);
  emxInit_creal_T(&b_fv, 1);
  r2br_r2dit_trig_impl(y, N2, costab, sintab, fv);
  b_r2br_r2dit_trig(wwc, N2, costab, sintab, r1);
  k = b_fv->size[0];
  b_fv->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(b_fv, k);
  xidx = fv->size[0];
  for (k = 0; k < xidx; k++) {
    b_fv_re = fv->data[k].re;
    b_fv_im = fv->data[k].im;
    denom_re = r1->data[k].re;
    denom_im = r1->data[k].im;
    b_fv->data[k].re = b_fv_re * denom_re - b_fv_im * denom_im;
    b_fv->data[k].im = b_fv_re * denom_im + b_fv_im * denom_re;
  }

  emxFree_creal_T(&r1);
  c_r2br_r2dit_trig(b_fv, N2, costab, sintabinv, fv);
  xidx = 0;
  k = n1 - 1;
  emxFree_creal_T(&b_fv);
  while (k + 1 <= wwc->size[0]) {
    denom_re = wwc->data[k].re;
    b_fv_re = fv->data[k].re;
    denom_im = wwc->data[k].im;
    b_fv_im = fv->data[k].im;
    wwc_re = wwc->data[k].re;
    fv_im = fv->data[k].im;
    wwc_im = wwc->data[k].im;
    fv_re = fv->data[k].re;
    y->data[xidx].re = denom_re * b_fv_re + denom_im * b_fv_im;
    y->data[xidx].im = wwc_re * fv_im - wwc_im * fv_re;
    denom_re = wwc->data[k].re;
    b_fv_re = fv->data[k].re;
    denom_im = wwc->data[k].im;
    b_fv_im = fv->data[k].im;
    wwc_re = wwc->data[k].re;
    fv_im = fv->data[k].im;
    wwc_im = wwc->data[k].im;
    fv_re = fv->data[k].re;
    y->data[xidx].re = denom_re * b_fv_re + denom_im * b_fv_im;
    y->data[xidx].im = wwc_re * fv_im - wwc_im * fv_re;
    denom_re = y->data[xidx].re;
    denom_im = y->data[xidx].im;
    if (denom_im == 0.0) {
      y->data[xidx].re = denom_re / (double)n1;
      y->data[xidx].im = 0.0;
    } else if (denom_re == 0.0) {
      y->data[xidx].re = 0.0;
      y->data[xidx].im = denom_im / (double)n1;
    } else {
      y->data[xidx].re = denom_re / (double)n1;
      y->data[xidx].im = denom_im / (double)n1;
    }

    xidx++;
    k++;
  }

  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
}

//
// Arguments    : int nRows
//                boolean_T useRadix2
//                emxArray_real_T *costab
//                emxArray_real_T *sintab
//                emxArray_real_T *sintabinv
// Return Type  : void
//
void b_generate_twiddle_tables(int nRows, boolean_T useRadix2, emxArray_real_T
  *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  int nRowsD4;
  int nd2;
  int k;
  int n2;
  emxInit_real_T1(&costab1q, 2);
  e = 6.2831853071795862 / (double)nRows;
  nRowsD4 = nRows / 2 / 2;
  nd2 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = nRowsD4 + 1;
  emxEnsureCapacity_real_T1(costab1q, nd2);
  costab1q->data[0] = 1.0;
  nd2 = nRowsD4 / 2;
  for (k = 1; k <= nd2; k++) {
    costab1q->data[k] = std::cos(e * (double)k);
  }

  for (k = nd2 + 1; k < nRowsD4; k++) {
    costab1q->data[k] = std::sin(e * (double)(nRowsD4 - k));
  }

  costab1q->data[nRowsD4] = 0.0;
  if (!useRadix2) {
    nRowsD4 = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(costab, nd2);
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(sintab, nd2);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    nd2 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(sintabinv, nd2);
    for (k = 1; k <= nRowsD4; k++) {
      sintabinv->data[k] = costab1q->data[nRowsD4 - k];
    }

    for (k = costab1q->size[1]; k <= n2; k++) {
      sintabinv->data[k] = costab1q->data[k - nRowsD4];
    }

    for (k = 1; k <= nRowsD4; k++) {
      costab->data[k] = costab1q->data[k];
      sintab->data[k] = -costab1q->data[nRowsD4 - k];
    }

    for (k = costab1q->size[1]; k <= n2; k++) {
      costab->data[k] = -costab1q->data[n2 - k];
      sintab->data[k] = -costab1q->data[k - nRowsD4];
    }
  } else {
    nRowsD4 = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(costab, nd2);
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(sintab, nd2);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 1; k <= nRowsD4; k++) {
      costab->data[k] = costab1q->data[k];
      sintab->data[k] = costab1q->data[nRowsD4 - k];
    }

    for (k = costab1q->size[1]; k <= n2; k++) {
      costab->data[k] = -costab1q->data[n2 - k];
      sintab->data[k] = costab1q->data[k - nRowsD4];
    }

    nd2 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
    emxEnsureCapacity_real_T1(sintabinv, nd2);
  }

  emxFree_real_T(&costab1q);
}

//
// Arguments    : const emxArray_creal_T *x
//                int n1_unsigned
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                emxArray_creal_T *y
// Return Type  : void
//
void c_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int j;
  int nRowsD2;
  int nRowsD4;
  int iDelta2;
  int iy;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double r;
  double twid_im;
  int ihi;
  j = x->size[0];
  if (!(j < n1_unsigned)) {
    j = n1_unsigned;
  }

  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  iDelta2 = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iDelta2);
  if (n1_unsigned > x->size[0]) {
    iy = y->size[0];
    iDelta2 = y->size[0];
    y->size[0] = iy;
    emxEnsureCapacity_creal_T(y, iDelta2);
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y->data[iDelta2].re = 0.0;
      y->data[iDelta2].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 1; i < j; i++) {
    y->data[iy] = x->data[ix];
    iDelta2 = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta2 >>= 1;
      ju ^= iDelta2;
      tst = ((ju & iDelta2) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= n1_unsigned - 2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iDelta2) {
      temp_re = y->data[i + iy].re;
      temp_im = y->data[i + iy].im;
      y->data[i + iy].re = y->data[i].re - temp_re;
      y->data[i + iy].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      r = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re = r * y->data[i + iy].re - twid_im * y->data[i + iy].im;
        temp_im = r * y->data[i + iy].im + twid_im * y->data[i + iy].re;
        y->data[i + iy].re = y->data[i].re - temp_re;
        y->data[i + iy].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iDelta2;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    ix -= iy;
  }

  if (y->size[0] > 1) {
    r = 1.0 / (double)y->size[0];
    iDelta2 = y->size[0];
    emxEnsureCapacity_creal_T(y, iDelta2);
    iy = y->size[0];
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y->data[iDelta2].re *= r;
      y->data[iDelta2].im *= r;
    }
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                int N2
//                int n1
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                const emxArray_real_T *sintabinv
//                emxArray_creal_T *y
// Return Type  : void
//
void dobluesteinfft(const double x_data[], const int x_size[1], int N2, int n1,
                    const emxArray_real_T *costab, const emxArray_real_T *sintab,
                    const emxArray_real_T *sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int minNrowsNx;
  int k;
  int xidx;
  double re;
  double im;
  emxArray_creal_T *fv;
  emxArray_creal_T *r0;
  emxArray_creal_T *b_fv;
  double fv_re;
  double fv_im;
  double wwc_re;
  double b_fv_im;
  double wwc_im;
  double b_fv_re;
  emxInit_creal_T(&wwc, 1);
  bluesteinSetup(n1, wwc);
  minNrowsNx = x_size[0];
  if (n1 < minNrowsNx) {
    minNrowsNx = n1;
  }

  k = y->size[0];
  y->size[0] = n1;
  emxEnsureCapacity_creal_T(y, k);
  if (n1 > x_size[0]) {
    xidx = y->size[0];
    k = y->size[0];
    y->size[0] = xidx;
    emxEnsureCapacity_creal_T(y, k);
    for (k = 0; k < xidx; k++) {
      y->data[k].re = 0.0;
      y->data[k].im = 0.0;
    }
  }

  xidx = 0;
  for (k = 0; k + 1 <= minNrowsNx; k++) {
    re = wwc->data[(n1 + k) - 1].re;
    im = wwc->data[(n1 + k) - 1].im;
    y->data[k].re = re * x_data[xidx];
    y->data[k].im = im * -x_data[xidx];
    xidx++;
  }

  while (minNrowsNx + 1 <= n1) {
    y->data[minNrowsNx].re = 0.0;
    y->data[minNrowsNx].im = 0.0;
    minNrowsNx++;
  }

  emxInit_creal_T(&fv, 1);
  emxInit_creal_T(&r0, 1);
  emxInit_creal_T(&b_fv, 1);
  r2br_r2dit_trig_impl(y, N2, costab, sintab, fv);
  b_r2br_r2dit_trig(wwc, N2, costab, sintab, r0);
  k = b_fv->size[0];
  b_fv->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(b_fv, k);
  xidx = fv->size[0];
  for (k = 0; k < xidx; k++) {
    fv_re = fv->data[k].re;
    fv_im = fv->data[k].im;
    re = r0->data[k].re;
    im = r0->data[k].im;
    b_fv->data[k].re = fv_re * re - fv_im * im;
    b_fv->data[k].im = fv_re * im + fv_im * re;
  }

  emxFree_creal_T(&r0);
  c_r2br_r2dit_trig(b_fv, N2, costab, sintabinv, fv);
  xidx = 0;
  k = n1 - 1;
  emxFree_creal_T(&b_fv);
  while (k + 1 <= wwc->size[0]) {
    re = wwc->data[k].re;
    fv_re = fv->data[k].re;
    im = wwc->data[k].im;
    fv_im = fv->data[k].im;
    wwc_re = wwc->data[k].re;
    b_fv_im = fv->data[k].im;
    wwc_im = wwc->data[k].im;
    b_fv_re = fv->data[k].re;
    y->data[xidx].re = re * fv_re + im * fv_im;
    y->data[xidx].im = wwc_re * b_fv_im - wwc_im * b_fv_re;
    xidx++;
    k++;
  }

  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
}

//
// Arguments    : int nRows
//                boolean_T useRadix2
//                emxArray_real_T *costab
//                emxArray_real_T *sintab
//                emxArray_real_T *sintabinv
// Return Type  : void
//
void generate_twiddle_tables(int nRows, boolean_T useRadix2, emxArray_real_T
  *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  int nRowsD4;
  int nd2;
  int k;
  int n2;
  emxInit_real_T1(&costab1q, 2);
  e = 6.2831853071795862 / (double)nRows;
  nRowsD4 = nRows / 2 / 2;
  nd2 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = nRowsD4 + 1;
  emxEnsureCapacity_real_T1(costab1q, nd2);
  costab1q->data[0] = 1.0;
  nd2 = nRowsD4 / 2;
  for (k = 1; k <= nd2; k++) {
    costab1q->data[k] = std::cos(e * (double)k);
  }

  for (k = nd2 + 1; k < nRowsD4; k++) {
    costab1q->data[k] = std::sin(e * (double)(nRowsD4 - k));
  }

  costab1q->data[nRowsD4] = 0.0;
  if (!useRadix2) {
    nRowsD4 = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(costab, nd2);
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(sintab, nd2);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    nd2 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(sintabinv, nd2);
    for (k = 1; k <= nRowsD4; k++) {
      sintabinv->data[k] = costab1q->data[nRowsD4 - k];
    }

    for (k = costab1q->size[1]; k <= n2; k++) {
      sintabinv->data[k] = costab1q->data[k - nRowsD4];
    }

    for (k = 1; k <= nRowsD4; k++) {
      costab->data[k] = costab1q->data[k];
      sintab->data[k] = -costab1q->data[nRowsD4 - k];
    }

    for (k = costab1q->size[1]; k <= n2; k++) {
      costab->data[k] = -costab1q->data[n2 - k];
      sintab->data[k] = -costab1q->data[k - nRowsD4];
    }
  } else {
    nRowsD4 = costab1q->size[1] - 1;
    n2 = (costab1q->size[1] - 1) << 1;
    nd2 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(costab, nd2);
    nd2 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = n2 + 1;
    emxEnsureCapacity_real_T1(sintab, nd2);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 1; k <= nRowsD4; k++) {
      costab->data[k] = costab1q->data[k];
      sintab->data[k] = -costab1q->data[nRowsD4 - k];
    }

    for (k = costab1q->size[1]; k <= n2; k++) {
      costab->data[k] = -costab1q->data[n2 - k];
      sintab->data[k] = -costab1q->data[k - nRowsD4];
    }

    nd2 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
    emxEnsureCapacity_real_T1(sintabinv, nd2);
  }

  emxFree_real_T(&costab1q);
}

//
// Arguments    : int n1
//                boolean_T useRadix2
//                int *N2blue
//                int *nRows
// Return Type  : void
//
void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows)
{
  int nn1m1;
  int pmax;
  int pmin;
  boolean_T exitg1;
  int p;
  int pow2p;
  *N2blue = 1;
  if (useRadix2) {
    *nRows = n1;
  } else {
    nn1m1 = (n1 + n1) - 1;
    pmax = 31;
    if (nn1m1 <= 1) {
      pmax = 0;
    } else {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        p = (pmin + pmax) >> 1;
        pow2p = 1 << p;
        if (pow2p == nn1m1) {
          pmax = p;
          exitg1 = true;
        } else if (pow2p > nn1m1) {
          pmax = p;
        } else {
          pmin = p;
        }
      }
    }

    *N2blue = 1 << pmax;
    *nRows = *N2blue;
  }
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                int n1_unsigned
//                const emxArray_real_T *costab
//                const emxArray_real_T *sintab
//                emxArray_creal_T *y
// Return Type  : void
//
void r2br_r2dit_trig(const double x_data[], const int x_size[1], int n1_unsigned,
                     const emxArray_real_T *costab, const emxArray_real_T
                     *sintab, emxArray_creal_T *y)
{
  int j;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int ihi;
  j = x_size[0];
  if (!(j < n1_unsigned)) {
    j = n1_unsigned;
  }

  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iy);
  if (n1_unsigned > x_size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 1; i < j; i++) {
    y->data[iy].re = x_data[ix];
    y->data[iy].im = 0.0;
    iDelta = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy].re = x_data[ix];
  y->data[iy].im = 0.0;
  if (n1_unsigned > 1) {
    for (i = 0; i <= n1_unsigned - 2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re = y->data[i + iDelta].re;
      temp_im = y->data[i + iDelta].im;
      y->data[i + iDelta].re = y->data[i].re - temp_re;
      y->data[i + iDelta].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re = twid_re * y->data[i + iDelta].re - twid_im * y->data[i +
          iDelta].im;
        temp_im = twid_re * y->data[i + iDelta].im + twid_im * y->data[i +
          iDelta].re;
        y->data[i + iDelta].re = y->data[i].re - temp_re;
        y->data[i + iDelta].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }
}

//
// File trailer for fft1.cpp
//
// [EOF]
//
