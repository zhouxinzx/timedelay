//
// File: timedelay.cpp
//
// MATLAB Coder version            : 3.4
// C/C++ source code generated on  : 27-Jan-2018 19:57:38
//

// Include Files
#include "rt_nonfinite.h"
#include "timedelay.h"
#include "finddelay.h"
#include<iostream>
using namespace std;
// Function Definitions

//
// Arguments    : const double x_data[]
//                const int x_size[2]
//                const double y_data[]
//                const int y_size[2]
// Return Type  : double
//
double timedelay(const double x_data[], const int x_size[2], const double
                 y_data[], const int y_size[2])
{
  int di;
  di = FindDelay(x_data, x_size, y_data, y_size);
  return di;
}
/*
int main()
{
		double a[3]={1.1,2.1,3.1};
		double b[5]={0,0,1,2,3};
		int a_size[2]={1,3};
		int b_size[2]={1,5};
		double c=timedelay(b,b_size,a,a_size);
		cout<<c<<endl;
		return 0;
}*/


//
// File trailer for timedelay.cpp
//
// [EOF]
//
