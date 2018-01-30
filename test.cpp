#include<iostream>
#include"timedelay.h"
using namespace std;


 int main()
 {
         double a[3]={1.1,2.1,3.1};
         double b[5]={0,0,1,2,3};
         int a_size[2]={1,3};
         int b_size[2]={1,5};
         double c=timedelay(b,b_size,a,a_size);
         cout<<c<<endl;
         return 0;
 }
