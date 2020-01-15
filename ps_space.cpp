#include "ps_space.h"

PS_Space::PS_Space()
{
    V_PolState = PS_Vec(1, 0);
}

PS_Space::PS_Space(const PS_Space &S)
{
    pDSB_X1R = S.pDSB_X1R;
    pDSB_X1I = S.pDSB_X1I;
    pDSB_X2R = S.pDSB_X2R;
    pDSB_X2I = S.pDSB_X2I;
    pDSB_S0  = S.pDSB_S0;
    pDSB_S1  = S.pDSB_S1;
    pDSB_S2  = S.pDSB_S2;
    pDSB_S3  = S.pDSB_S3;
    V_PolState = S.V_PolState;
    InputSpace = S.InputSpace;
    InputElement = S.InputElement;
}

void PS_Space::Set_Ui(QLabel *pPolState, QProgressBar *pIntensity, QDoubleSpinBox *pX1R, QDoubleSpinBox *pX1I, QDoubleSpinBox *pX2R, QDoubleSpinBox *pX2I, QDoubleSpinBox *pS0, QDoubleSpinBox *pS1, QDoubleSpinBox *pS2, QDoubleSpinBox *pS3)
{
    pL_PolState = pPolState;
    pPB_Intensity = pIntensity;
    pDSB_X1R = pX1R;
    pDSB_X1I = pX1I;
    pDSB_X2R = pX2R;
    pDSB_X2I = pX2I;
    pDSB_S0  = pS0;
    pDSB_S1  = pS1;
    pDSB_S2  = pS2;
    pDSB_S3  = pS3;
}

void PS_Space::Set_SpaceInput(PS_Space *S)
{
    InputSpace = S;
    connect(S, SIGNAL(Updated()), this, SLOT(Update()));
}

void PS_Space::Set_ElementInput(PS_Element *E)
{
    InputElement = E;
    connect(E, SIGNAL(Updated()), this, SLOT(Update()));
}

void PS_Space::Set(PS_Vec V)
{
    //save exact values
    V_PolState = V;

    //Calc Stokes Param
    Stks_0      = V_PolState.x1_abs_square() + V_PolState.x2_abs_square();
    Stks_1      = V_PolState.x1_abs_square() - V_PolState.x2_abs_square();
    Stks_2      = 2 * (V_PolState.x1() * V_PolState.x2_conjugated()).real();
    Stks_3      =-2 * (V_PolState.x1() * V_PolState.x2_conjugated()).imag();
    Stks_I      = Stks_0;
    Stks_p      = sqrt(Stks_1 + Stks_2 + Stks_3) / Stks_0;
    Stks_Psi    = atan2(Stks_2, Stks_1) / 2.0;
    Stks_Chi    = atan2(Stks_3, sqrt(Stks_1 * Stks_1 + Stks_2 * Stks_2)) / 2.0;

    //show rounded values
    pDSB_X1R->setValue(V_PolState.x1().real());
    pDSB_X1I->setValue(V_PolState.x1().imag());
    pDSB_X2R->setValue(V_PolState.x2().real());
    pDSB_X2I->setValue(V_PolState.x2().imag());
    pDSB_S0->setValue(Stks_0);
    pDSB_S1->setValue(Stks_1);
    pDSB_S2->setValue(Stks_2);
    pDSB_S3->setValue(Stks_3);
    pPB_Intensity->setValue(static_cast<int>(10000.0 * Stks_I));

    emit Updated();
    emit Updated(Stks_I);

    //draw ellipse
    Update_PolStateDraw();
}

void PS_Space::Calc(PS_Element *E, PS_Space *S)
{
    Set(E->Get() * S->Get());
}

PS_Vec PS_Space::Get()
{
    return PS_Vec(V_PolState);
}

void PS_Space::Get_Rotation(QSplineSeries *Lines[], QScatterSeries *Dot)
{
    //cout << "clear old content" << endl;
    //clear old stuff
    for(int p = 0; p < PLOT_NUMBER_OF; p++)
        Lines[p]->clear();
    Dot->clear();

    //anything changes?
    if(InputElement->Prototype() == ELEMENT_NOTHING)
        return;

    //input
    //cout << "get input" << endl;
    PS_Vec space_in_at0 = InputSpace->Get();

    //selected angle
    double angle = InputElement->Angle();
    Dot->append(angle, Stks_0);

    //rotate
    for(int a = 0; a <= PLOT_MAX_X; a+=PLOT_STEP)
    {
        //cout << "Rotation step: " << a << endl;
        //rotation
        PS_Vec space_out_rot = InputElement->Get(a) * space_in_at0;

        //lengths
        Lines[PLOT_REAL]  ->append(a, space_out_rot.length_re());
        Lines[PLOT_IMAG]  ->append(a, space_out_rot.length_im());
        Lines[PLOT_SQUARE]->append(a, space_out_rot.x1_abs_square() + space_out_rot.x2_abs_square());
    }
}

void PS_Space::Update()
{
    Calc(InputElement, InputSpace);
}

void PS_Space::Update_PolStateDraw()
{
    //ellipse parameters
    double angle = Stks_Psi * Rad2Grad;
    double Rre = Stks_0;
    double Rim = tan(Stks_Chi);

    //clear old content
    pL_PolState->clear();

    //target pixmap
    PX_PolState = QPixmap(pL_PolState->width(), pL_PolState->height());
    PX_PolState.fill(Qt::white);

    //scale
    double min = pL_PolState->width();
    if(min > pL_PolState->height())
        min = pL_PolState->height();
    double R_max = (min-3)/2.0;

    //draw
    QPainter painter(&PX_PolState);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.translate(PX_PolState.rect().center().x(), PX_PolState.rect().center().y());
    painter.rotate(angle);
    painter.translate(-PX_PolState.rect().center().x(), -PX_PolState.rect().center().y());
    painter.drawEllipse(
                PX_PolState.rect().center(),
                static_cast<int>(Rre * R_max),
                static_cast<int>(Rim * R_max));

    //text
    painter.translate(PX_PolState.rect().center().x(), PX_PolState.rect().center().y());
    painter.rotate(-angle);
    painter.translate(-PX_PolState.rect().center().x(), -PX_PolState.rect().center().y());
    painter.setFont(QFont("Arial"));
    if(Stks_3 < 0)
        painter.drawText(QPoint(2, 12), "L");
    else if(Stks_3 > 0)
        painter.drawText(QPoint(2, 12), "R");

    //show
    pL_PolState->setPixmap(PX_PolState);
}
