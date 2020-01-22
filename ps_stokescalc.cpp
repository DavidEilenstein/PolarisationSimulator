#include "ps_stokescalc.h"
#include <math.h>
#include "ui_ps_stokescalc.h"

PS_StokesCalc::PS_StokesCalc(QDir *pDIR, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PS_StokesCalc)
{
    ui->setupUi(this);

    pDIR_Operation = pDIR;

    setWindowTitle("Stokes Parameter Calculator");
}

PS_StokesCalc::~PS_StokesCalc()
{
    delete ui;
}

void PS_StokesCalc::CalcAll()
{
    ui->groupBox_Stokes->setEnabled(true);
    ui->groupBox_Poincare->setEnabled(true);
    ui->groupBox_Ellipse->setEnabled(true);

    Stks_0      = P_0_0 + P_p90_0;
    Stks_1      = P_0_0 - P_p90_0;
    Stks_2      = P_p45_0 - P_m45_0;
    Stks_3      = P_p45_m90 - P_m45_m90;;
    Stks_I      = Stks_0;
    Stks_p      = sqrt(Stks_1 + Stks_2 + Stks_3) / Stks_0;
    Stks_Psi    = atan2(Stks_2, Stks_1) / 2.0;
    Stks_Chi    = atan2(Stks_3, sqrt(Stks_1 * Stks_1 + Stks_2 * Stks_2)) / 2.0;

    ui->doubleSpinBox_S0->setValue(Stks_0);
    ui->doubleSpinBox_S1->setValue(Stks_1);
    ui->doubleSpinBox_S2->setValue(Stks_2);
    ui->doubleSpinBox_S3->setValue(Stks_3);

    ui->doubleSpinBox_I->setValue(Stks_I);
    ui->doubleSpinBox_p->setValue(Stks_p);
    ui->doubleSpinBox_Psi->setValue(Stks_Psi);
    ui->doubleSpinBox_Chi->setValue(Stks_Chi);

    //ellipse parameters
    double angle = Stks_Psi * Rad2Grad;
    double Rre = 1.0;
    double Rim = tan(Stks_Chi);

    //clear old content
    ui->label_Ellipse->clear();

    //target pixmap
    PX_Ellipse = QPixmap(ui->label_Ellipse->width(), ui->label_Ellipse->height());
    PX_Ellipse.fill(Qt::white);

    //scale
    double min = ui->label_Ellipse->width();
    if(min > ui->label_Ellipse->height())
        min = ui->label_Ellipse->height();
    double R_max = (min-3)/2.0;

    //draw
    QPainter painter(&PX_Ellipse);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.translate(PX_Ellipse.rect().center().x(), PX_Ellipse.rect().center().y());
    painter.rotate(angle);
    painter.translate(-PX_Ellipse.rect().center().x(), -PX_Ellipse.rect().center().y());
    painter.drawEllipse(
                PX_Ellipse.rect().center(),
                static_cast<int>(Rre * R_max),
                static_cast<int>(Rim * R_max));
    ui->label_Ellipse->setPixmap(PX_Ellipse);
}

void PS_StokesCalc::on_doubleSpinBox_P_0_0_valueChanged(double arg1)
{
    P_0_0 = arg1;
    CalcAll();
}

void PS_StokesCalc::on_doubleSpinBox_P_p90_0_valueChanged(double arg1)
{
    P_p90_0 = arg1;
    CalcAll();
}

void PS_StokesCalc::on_doubleSpinBox_P_p45_0_valueChanged(double arg1)
{
    P_p45_0 = arg1;
    CalcAll();
}

void PS_StokesCalc::on_doubleSpinBox_m45_0_valueChanged(double arg1)
{
    P_m45_0 = arg1;
    CalcAll();
}

void PS_StokesCalc::on_doubleSpinBox_45_m90_valueChanged(double arg1)
{
    P_p45_m90 = arg1;
    CalcAll();
}

void PS_StokesCalc::on_doubleSpinBox_m45_m90_valueChanged(double arg1)
{
    P_m45_m90 = arg1;
    CalcAll();
}

void PS_StokesCalc::on_pushButton_Save_clicked()
{
    QString name_save = QFileDialog::getSaveFileName(
                this,
                "Save Stokes Calculation",
                pDIR_Operation->path() + "/Stokes_Calculation.jpg",
                tr("Image Files (*.png *.jpg *.bmp)"));
    if(name_save.isEmpty())
        return;

    this->grab().save(name_save);
    pDIR_Operation->setPath(name_save);
}
