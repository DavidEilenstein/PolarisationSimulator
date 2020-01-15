#ifndef PS_ENUM_H
#define PS_ENUM_H

#include <QStringList>
#include <vector>
#include <QColor>

using namespace std;

enum Prototypes {
    ELEMENT_NOTHING,
    ELEMENT_LINEAR,
    ELEMENT_LAMBDA4,
    ELEMENT_LAMBDA2,
    ELEMENT_CIRC_LEFT,
    ELEMENT_CIRC_RIGHT,
    ElEMENT_CUSTOM,
    ELEMENT_NUMER_OF
};
const QStringList QSL_Prototypes = {
    "-",
    "Linear Filter",
    "Quaterwaveplate",
    "Halfwaveplate",
    "Circular Filter Left",
    "Circular Filter Right"
};


enum PlotIndex
{
    PLOT_REAL,
    PLOT_IMAG,
    PLOT_SQUARE,
    PLOT_NUMBER_OF
};
const int PLOT_MIN_X = 0;
const int PLOT_MAX_X = 360;
const int PLOT_MIN_Y = 0;
const int PLOT_MAX_Y = 1;
const int PLOT_STEP  = 10;
const int PLOT_SERIES_COUNT = 4;
const vector<QColor> PLOT_SERIES_COLORS = {
    QColor(000, 255, 000),
    QColor(255, 255, 000),
    QColor(255, 000, 000),
    QColor(000, 000, 255)
};

//Angles
const double
PI                      = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
const double
PI_4_0                  = 4.0 * PI,
PI_2_0                  = 2.0 * PI,
PI_0_5                  = PI / 2.0,
PI_0_25                 = PI / 4.0;
const double
Rad2Grad                = 180.0 / PI,
Grad2Rad                = PI / 180.0;
const double EULER      = 2.71828182846;

#endif // PS_ENUM_H
