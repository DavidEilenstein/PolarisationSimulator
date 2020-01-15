#ifndef PS_STOKESCALC_H
#define PS_STOKESCALC_H

#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QDir>
#include <QFileDialog>
#include <ps_enum.h>

namespace Ui {
class PS_StokesCalc;
}

class PS_StokesCalc : public QDialog
{
    Q_OBJECT

public:
    explicit PS_StokesCalc(QDir *pDIR, QWidget *parent = nullptr);
    ~PS_StokesCalc();

private slots:
    void on_doubleSpinBox_P_0_0_valueChanged(double arg1);

    void on_doubleSpinBox_P_p90_0_valueChanged(double arg1);

    void on_doubleSpinBox_P_p45_0_valueChanged(double arg1);

    void on_doubleSpinBox_m45_0_valueChanged(double arg1);

    void on_doubleSpinBox_45_m90_valueChanged(double arg1);

    void on_doubleSpinBox_m45_m90_valueChanged(double arg1);

    void on_pushButton_Save_clicked();

private:
    Ui::PS_StokesCalc *ui;

    void CalcAll();

    double         P_0_0    = 0.0;
    double         P_p90_0  = 0.0;
    double         P_p45_0  = 0.0;
    double         P_m45_0  = 0.0;
    double         P_p45_m90= 0.0;
    double         P_m45_m90= 0.0;
    double         Stks_0   = 0.0;
    double         Stks_1   = 0.0;
    double         Stks_2   = 0.0;
    double         Stks_3   = 0.0;
    double         Stks_I   = 0.0;
    double         Stks_p   = 0.0;
    double         Stks_Psi = 0.0;
    double         Stks_Chi = 0.0;

    QPixmap        PX_Ellipse;

    QDir           *pDIR_Operation;
};

#endif // PS_STOKESCALC_H
