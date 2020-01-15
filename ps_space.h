#ifndef PS_SPACE_H
#define PS_SPACE_H

#include <QObject>
#include <complex>
#include <vector>
#include <math.h>
#include <algorithm>
#include <ps_vec.h>
#include <ps_mat.h>
#include <ps_element.h>
#include <QDoubleSpinBox>
#include <QProgressBar>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QLabel>
#include <QPixmap>

using namespace std;
QT_CHARTS_USE_NAMESPACE

class PS_Space : public QObject
{
    Q_OBJECT
public:
    PS_Space();
    PS_Space(const PS_Space& S);

    void Set_Ui             (QLabel *pPolState, QProgressBar *pIntensity, QDoubleSpinBox *pX1R, QDoubleSpinBox *pX1I, QDoubleSpinBox *pX2R, QDoubleSpinBox *pX2I, QDoubleSpinBox *pS0, QDoubleSpinBox *pS1, QDoubleSpinBox *pS2, QDoubleSpinBox *pS3);
    void Set_SpaceInput     (PS_Space *S);
    void Set_ElementInput   (PS_Element *E);

    void    Set             (PS_Vec V);
    void    Calc            (PS_Element *E, PS_Space *S);
    PS_Vec  Get             ();
    void    Get_Rotation    (QSplineSeries *Lines[], QScatterSeries *Dot);

signals:
    void Updated();
    void Updated(double intensity);
public slots:
    void Update();
    void Update_PolStateDraw();

private:
    PS_Vec         V_PolState;
    double         Stks_0   = 1.0;
    double         Stks_1   = 1.0;
    double         Stks_2   = 0.0;
    double         Stks_3   = 0.0;
    double         Stks_I   = 1.0;
    double         Stks_p   = 1.0;
    double         Stks_Psi = 0.0;
    double         Stks_Chi = 0.0;

    QProgressBar   *pPB_Intensity;
    QLabel         *pL_PolState;
    QDoubleSpinBox *pDSB_X1R;
    QDoubleSpinBox *pDSB_X1I;
    QDoubleSpinBox *pDSB_X2R;
    QDoubleSpinBox *pDSB_X2I;
    QDoubleSpinBox *pDSB_S0;
    QDoubleSpinBox *pDSB_S1;
    QDoubleSpinBox *pDSB_S2;
    QDoubleSpinBox *pDSB_S3;

    PS_Space *InputSpace;
    PS_Element *InputElement;

    QPixmap PX_PolState;

};

#endif // PS_SPACE_H
