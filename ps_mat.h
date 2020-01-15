#ifndef PS_MAT_H
#define PS_MAT_H

#include <math.h>
#include <complex>
#include <vector>
#include <ps_vec.h>
#include <ps_enum.h>
#include <iostream>

using namespace std;

class PS_Mat
{
public:
    PS_Mat();
    PS_Mat(double angle);
    PS_Mat(complex<double> x11, complex<double> x12, complex<double> x21, complex<double> x22);

    void Info();

    PS_Vec operator* (PS_Vec V);
    PS_Mat operator* (PS_Mat M);

    complex<double> x11()  {return data[0][0];}
    complex<double> x12()  {return data[0][1];}
    complex<double> x21()  {return data[1][0];}
    complex<double> x22()  {return data[1][1];}

private:
    complex<double> data[2][2];
};

#endif // PS_MAT_H
