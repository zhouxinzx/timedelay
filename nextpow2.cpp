//
// File: nextpow2.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//

// Include Files
#include "rt_nonfinite.h"
#include "timedelay.h"
#include "nextpow2.h"

// Function Definitions

//
// Arguments    : double n
// Return Type  : double
//
double nextpow2(double n)
{
  double p;
  double f;
  int eint;
  f = frexp(std::abs(n), &eint);
  p = eint;
  if (f == 0.5) {
    p = (double)eint - 1.0;
  }

  return p;
}

//
// File trailer for nextpow2.cpp
//
// [EOF]
//
