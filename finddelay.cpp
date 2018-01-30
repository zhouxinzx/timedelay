//
// File: finddelay.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//

// Include Files
#include "rt_nonfinite.h"
#include "timedelay.h"
#include "finddelay.h"
#include "xcorr.h"
#include "sqrt.h"

// Function Declarations
static double sumsq(const double x_data[], const int x_size[1]);
static void vFindDelay(const double x_data[], const int x_size[1], const double
  y_data[], const int y_size[1], int maxlag, double cxx0, double cyy0, int *d,
  double *max_c);

// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[1]
// Return Type  : double
//
static double sumsq(const double x_data[], const int x_size[1])
{
  double s;
  int k;
  s = 0.0;
  for (k = 0; k + 1 <= x_size[0]; k++) {
    s += x_data[k] * x_data[k];
  }

  return s;
}

//
// Arguments    : const double x_data[]
//                const int x_size[1]
//                const double y_data[]
//                const int y_size[1]
//                int maxlag
//                double cxx0
//                double cyy0
//                int *d
//                double *max_c
// Return Type  : void
//
static void vFindDelay(const double x_data[], const int x_size[1], const double
  y_data[], const int y_size[1], int maxlag, double cxx0, double cyy0, int *d,
  double *max_c)
{
  int y;
  double scale;
  int index_max;
  int index_max_pos;
  int index_max_neg;
  double c_data[5999];
  int c_size[1];
  double max_c_neg;
  int k;
  double max_c_pos;
  double vpos;
  y = maxlag << 1;
  *d = 0;
  *max_c = 0.0;
  scale = cxx0 * cyy0;
  b_sqrt(&scale);
  if ((maxlag == 0) || (scale == 0.0)) {
  } else {
    index_max = -1;
    index_max_pos = 0;
    index_max_neg = 1;
    xcorr(x_data, x_size, y_data, y_size, maxlag, c_data, c_size);
    max_c_neg = std::abs(c_data[maxlag - 1]) / scale;
    for (k = 2; k <= maxlag; k++) {
      max_c_pos = std::abs(c_data[maxlag - k]) / scale;
      if (max_c_pos > max_c_neg) {
        max_c_neg = max_c_pos;
        index_max_neg = k;
      }
    }

    max_c_pos = std::abs(c_data[maxlag]) / scale;
    for (k = maxlag + 2; k <= y + 1; k++) {
      vpos = std::abs(c_data[k - 1]) / scale;
      if (vpos > max_c_pos) {
        max_c_pos = vpos;
        index_max_pos = (k - maxlag) - 1;
      }
    }

    if (max_c_pos > max_c_neg) {
      index_max = maxlag + index_max_pos;
      *max_c = max_c_pos;
    } else if (max_c_pos < max_c_neg) {
      index_max = maxlag - index_max_neg;
      *max_c = max_c_neg;
    } else {
      if (max_c_pos == max_c_neg) {
        *max_c = max_c_pos;
        if (index_max_pos + 1 <= index_max_neg) {
          index_max = maxlag + index_max_pos;
        } else {
          index_max = maxlag - index_max_neg;
        }
      }
    }

    *d = maxlag - index_max;
  }
}

//
// Arguments    : const double x_in_data[]
//                const int x_in_size[2]
//                const double y_in_data[]
//                const int y_in_size[2]
// Return Type  : int
//
int FindDelay(const double x_in_data[], const int x_in_size[2], const double
              y_in_data[], const int y_in_size[2])
{
  int d;
  int x_in[1];
  double cxx0;
  int y_in[1];
  double cyy0;
  int u0;
  int u1;
  double max_c;
  x_in[0] = x_in_size[1];
  cxx0 = sumsq(x_in_data, x_in);
  y_in[0] = y_in_size[1];
  cyy0 = sumsq(y_in_data, y_in);
  x_in[0] = x_in_size[1];
  y_in[0] = y_in_size[1];
  u0 = x_in_size[1];
  u1 = y_in_size[1];
  if (u0 > u1) {
    u1 = u0;
  }

  vFindDelay(x_in_data, x_in, y_in_data, y_in, u1 - 1, cxx0, cyy0, &d, &max_c);
  if (max_c < 1.0E-8) {
    d = 0;
  }

  return d;
}

//
// File trailer for finddelay.cpp
//
// [EOF]
//
