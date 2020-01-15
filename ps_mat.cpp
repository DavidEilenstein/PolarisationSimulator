#include "ps_mat.h"

PS_Mat::PS_Mat()
{
    data[0][0] = 1;
    data[0][1] = 0;
    data[1][0] = 0;
    data[1][1] = 1;
}

PS_Mat::PS_Mat(double angle)
{
    angle *= Grad2Rad;
    data[0][0] =  cos(angle);
    data[0][1] = -sin(angle);
    data[1][0] =  sin(angle);
    data[1][1] =  cos(angle);
    //Info();
}

PS_Mat::PS_Mat(complex<double> x11, complex<double> x12, complex<double> x21, complex<double> x22)
{
    data[0][0] = x11;
    data[0][1] = x12;
    data[1][0] = x21;
    data[1][1] = x22;
}

void PS_Mat::Info()
{
    cout << "matrix:" << endl;
    cout << data[0][0] << data[0][1] << endl;
    cout << data[1][0] << data[1][1] << endl;
    cout << endl;
}

PS_Vec PS_Mat::operator*(PS_Vec V)
{
    // R = A(this) * V
    //
    //                      V.x1
    //                      V.x2
    //
    //A.x11     A.x12       R.x1
    //A.x21     A.x22       R.x2

    return PS_Vec(
                x11() * V.x1() + x12() * V.x2(),
                x21() * V.x1() + x22() * V.x2());
}

PS_Mat PS_Mat::operator*(PS_Mat M)
{
    // R = A(this) * B
    //
    //                      B.x11       B.x12
    //                      B.x21       B.x22
    //
    //A.x11     A.x12       R.x11       R.x21
    //A.x21     A.x22       R.x21       R.x22

    return PS_Mat(
                x11() * M.x11() + x12() * M.x21(),      x11() * M.x12() + x12() * M.x22(),
                x21() * M.x11() + x22() * M.x21(),      x21() * M.x12() + x22() * M.x22());
}

