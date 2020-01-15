#include "ps_vec.h"

PS_Vec::PS_Vec()
{
    data[0] = 1;
    data[1] = 0;
}

PS_Vec::PS_Vec(complex<double> x1, complex<double> x2)
{
    data[0] = x1;
    data[1] = x2;
}
