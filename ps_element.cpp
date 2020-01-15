#include "ps_element.h"

PS_Element::PS_Element()
{
    //do nothing by default
    M_Prototype = PS_Mat(1, 0, 0, 1);
    M_Element   = PS_Mat(1, 0, 0, 1);

    connect(&timer, SIGNAL(timeout()), this, SLOT(Rotate()));
}

PS_Element::PS_Element(const PS_Element &E)
{
    pCB_Type    = E.pCB_Type;
    pD_Angle    = E.pD_Angle;
    pDSB_X11R   = E.pDSB_X11R;
    pDSB_X11I   = E.pDSB_X11I;
    pDSB_X12R   = E.pDSB_X12R;
    pDSB_X12I   = E.pDSB_X12I;
    pDSB_X21R   = E.pDSB_X21R;
    pDSB_X21I   = E.pDSB_X21I;
    pDSB_X22R   = E.pDSB_X22R;
    pDSB_X22I   = E.pDSB_X22I;
    M_Prototype = E.M_Prototype;
    M_Element   = E.M_Element;
}

void PS_Element::Set_Ui(QComboBox *pType, QDial *pAngle, QDoubleSpinBox *pAngleNum, QAction *rot, QDoubleSpinBox *pX11R, QDoubleSpinBox *pX11I, QDoubleSpinBox *pX12R, QDoubleSpinBox *pX12I, QDoubleSpinBox *pX21R, QDoubleSpinBox *pX21I, QDoubleSpinBox *pX22R, QDoubleSpinBox *pX22I)
{
    pCB_Type    = pType;
    pD_Angle    = pAngle;
    pDSB_Angle  = pAngleNum;
    pA_Rotate   = rot;
    pDSB_X11R   = pX11R;
    pDSB_X11I   = pX11I;
    pDSB_X12R   = pX12R;
    pDSB_X12I   = pX12I;
    pDSB_X21R   = pX21R;
    pDSB_X21I   = pX21I;
    pDSB_X22R   = pX22R;
    pDSB_X22I   = pX22I;

    pCB_Type->blockSignals(true);
    pCB_Type->addItems(QSL_Prototypes);
    pCB_Type->blockSignals(false);

    //connect
    connect(pCB_Type,   SIGNAL(currentIndexChanged(int)), this, SLOT(Update_Prototype(int)));
    connect(pD_Angle,   SIGNAL(valueChanged(int)),        this, SLOT(Update_Angle(int)));
    connect(pDSB_Angle, SIGNAL(valueChanged(double)),     this, SLOT(Update_Angle(double)));
    connect(pA_Rotate,  SIGNAL(triggered(bool)),          this, SLOT(Update_Rot(bool)));
}

void PS_Element::Set(PS_Mat M)
{
    M_Element = M;
    pDSB_X11R->setValue(M_Element.x11().real());
    pDSB_X11I->setValue(M_Element.x11().imag());
    pDSB_X12R->setValue(M_Element.x12().real());
    pDSB_X12I->setValue(M_Element.x12().imag());
    pDSB_X21R->setValue(M_Element.x21().real());
    pDSB_X21I->setValue(M_Element.x21().imag());
    pDSB_X22R->setValue(M_Element.x22().real());
    pDSB_X22I->setValue(M_Element.x22().imag());
    Updated();
}

PS_Mat PS_Element::Get()
{
    return PS_Mat(M_Element);
}

PS_Mat PS_Element::Get(double angle)
{
    return PS_Mat(angle) * M_Prototype * PS_Mat(-angle);
}

void PS_Element::Update_Prototype(int prototype)
{
    PrototypeIndex = prototype;

    switch (prototype) {

    case ELEMENT_NOTHING:
    {
        complex<double> x11(1, 0);
        complex<double> x12(0, 0);
        complex<double> x21(0, 0);
        complex<double> x22(1, 0);
        M_Prototype = PS_Mat(x11, x12, x21, x22);
    }
        break;

    case ELEMENT_LINEAR:
    {
        complex<double> x11(1, 0);
        complex<double> x12(0, 0);
        complex<double> x21(0, 0);
        complex<double> x22(0, 0);
        M_Prototype = PS_Mat(x11, x12, x21, x22);
    }
        break;

    case ELEMENT_CIRC_LEFT:
    {
        double v = 0.5;
        complex<double> x11(v, 0);
        complex<double> x12(0,-v);
        complex<double> x21(0, v);
        complex<double> x22(v, 0);
        M_Prototype = PS_Mat(x11, x12, x21, x22);
    }
        break;

    case ELEMENT_CIRC_RIGHT:
    {
        double v = 0.5;
        complex<double> x11(v, 0);
        complex<double> x12(0, v);
        complex<double> x21(0,-v);
        complex<double> x22(v, 0);
        M_Prototype = PS_Mat(x11, x12, x21, x22);
    }
        break;

    case ELEMENT_LAMBDA4:
    {
        double v = 1.0 / sqrt(2);
        complex<double> x11(v,-v);
        complex<double> x12(0, 0);
        complex<double> x21(0, 0);
        complex<double> x22(v, v);
        M_Prototype = PS_Mat(x11, x12, x21, x22);
    }
        break;

    case ELEMENT_LAMBDA2:
    {
        complex<double> x11(0,-1);
        complex<double> x12(0, 0);
        complex<double> x21(0, 0);
        complex<double> x22(0, 1);
        M_Prototype = PS_Mat(x11, x12, x21, x22);
    }
        break;

    default:
        break;
    }

    Update_Angle(pD_Angle->value());
}

void PS_Element::Update_Angle(int angle)
{
    double angle_d = angle / 4.0; //Dial values: 0-1440
    Set(PS_Mat(angle_d) * M_Prototype * PS_Mat(-angle_d));
    pDSB_Angle->setValue(angle_d);
}

void PS_Element::Update_Angle(double angle)
{
    int angle_i = static_cast<int>(angle * 4.0); //Dial values: 0-1440
    Set(PS_Mat(angle) * M_Prototype * PS_Mat(-angle));
    pD_Angle->setValue(angle_i);
}

void PS_Element::Update_Rot(bool rot)
{
    if(rot)
    {
        bool ok;
        step_deg = QInputDialog::getDouble(
                    this,
                    "Rotation Parameters",
                    "Select Degrees/Sec:",
                    step_deg,
                    -180,
                    180,
                    2,
                    &ok,
                    Qt::WindowFlags(),
                    5);
        if(!ok)
            return;
        timer.start(tick_ms);
        connect(&timer, SIGNAL(timeout()), this, SLOT(Rotate()));
        qDebug() << "Timer started:" << tick_ms;
    }
    else
    {
        timer.stop();
        qDebug() << "Timer stopped";
    }
}

void PS_Element::Rotate()
{
    double angle = Angle() + (step_deg / (1000.0 / tick_ms));
    if(angle < 0)   angle += 360.0;
    if(angle > 360) angle -= 360.0;
    //qDebug() << "Rotate to Angle:" << angle;
    pDSB_Angle->setValue(angle);
}
