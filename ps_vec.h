#ifndef PS_VEC_H
#define PS_VEC_H

#include <math.h>
#include <complex>
#include <vector>

using namespace std;

class PS_Vec
{
public:
    PS_Vec();
    PS_Vec(complex<double> x1, complex<double> x2);

    complex<double> x1()                {return data[0];}
    complex<double> x2()                {return data[1];}
    double          x1_re()             {return x1().real();}
    double          x2_re()             {return x2().real();}
    double          x1_im()             {return x1().imag();}
    double          x2_im()             {return x2().imag();}
    double          x1_re_square()      {return x1_re() * x1_re();}
    double          x2_re_square()      {return x2_re() * x2_re();}
    double          x1_im_square()      {return x1_im() * x1_im();}
    double          x2_im_square()      {return x2_im() * x2_im();}
    double          x1_abs_square()     {return x1_re_square() + x1_im_square();}
    double          x2_abs_square()     {return x2_re_square() + x2_im_square();}
    double          x1_abs()            {return sqrt(x1_abs_square());}
    double          x2_abs()            {return sqrt(x2_abs_square());}
    complex<double> x1_conjugated()     {return complex<double>(x1_re(), -x1_im());}
    complex<double> x2_conjugated()     {return complex<double>(x2_re(), -x2_im());}
    double          scalar_product_re() {return x1_re_square() + x2_re_square();}
    double          scalar_product_im() {return x1_im_square() + x2_im_square();}
    double          scalar_product()    {return (x1() * x1_conjugated() + x2() * x1_conjugated()).real();}
    double          length_re()         {return sqrt(scalar_product_re());}
    double          length_im()         {return sqrt(scalar_product_im());}
    double          length()            {return sqrt(scalar_product());}

private:
    complex<double> data[2];
};

#endif // PS_VEC_H
