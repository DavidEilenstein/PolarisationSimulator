#ifndef PS_ELEMENT_H
#define PS_ELEMENT_H

#include <ps_enum.h>
#include <QObject>
#include <complex>
#include <vector>
#include <math.h>
#include <ps_mat.h>
#include <QDoubleSpinBox>
#include <QDial>
#include <QComboBox>
#include <iostream>
#include <QPainter>
#include <QAction>
#include <QTimer>
#include <QInputDialog>
#include <QDebug>

using namespace std;

class PS_Element : public QWidget
{
    Q_OBJECT
public:
    PS_Element();
    PS_Element(const PS_Element& E);

    void Set_Ui             (QComboBox *pType, QDial *pAngle, QDoubleSpinBox *pAngleNum, QAction *rot, QDoubleSpinBox *pX11R, QDoubleSpinBox *pX11I, QDoubleSpinBox *pX12R, QDoubleSpinBox *pX12I, QDoubleSpinBox *pX21R, QDoubleSpinBox *pX21I, QDoubleSpinBox *pX22R, QDoubleSpinBox *pX22I);

    void    Set             (PS_Mat M);
    PS_Mat  Get             ();
    PS_Mat  Get             (double angle);
    double  Angle           ()                  {return pD_Angle->value() / 4.0;}//Dial values from 0-1440
    int     Prototype       ()                  {return PrototypeIndex;}

signals:
    void Updated();
public slots:
    void Update_Prototype(int prototype);
    void Update_Angle(int angle);
    void Update_Angle(double angle);
    void Update_Rot(bool rot);
    void Rotate();

private:
    QComboBox      *pCB_Type;
    QDial          *pD_Angle;
    QDoubleSpinBox *pDSB_Angle;
    QAction        *pA_Rotate;
    QDoubleSpinBox *pDSB_X11R;
    QDoubleSpinBox *pDSB_X11I;
    QDoubleSpinBox *pDSB_X12R;
    QDoubleSpinBox *pDSB_X12I;
    QDoubleSpinBox *pDSB_X21R;
    QDoubleSpinBox *pDSB_X21I;
    QDoubleSpinBox *pDSB_X22R;
    QDoubleSpinBox *pDSB_X22I;

    int PrototypeIndex = ELEMENT_NOTHING;
    PS_Mat M_Prototype;
    PS_Mat M_Element;

    int     tick_ms = 20;
    double  step_deg = 45;
    QTimer  timer;
};

#endif // PS_ELEMENT_H
