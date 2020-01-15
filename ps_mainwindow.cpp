#include "ps_mainwindow.h"
#include "ui_ps_mainwindow.h"

PS_MainWindow::PS_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PS_MainWindow)
{
    ui->setupUi(this);

    //spaces
    vSpaces.resize(5, PS_Space());
    vSpaces[0].Set_Ui(
                ui->label_Pol_S0,
                ui->progressBar_S0,
                ui->doubleSpinBox_X1_R_S0,
                ui->doubleSpinBox_X1_I_S0,
                ui->doubleSpinBox_X2_R_S0,
                ui->doubleSpinBox_X2_I_S0,
                ui->doubleSpinBox_Stokes0_S0,
                ui->doubleSpinBox_Stokes1_S0,
                ui->doubleSpinBox_Stokes2_S0,
                ui->doubleSpinBox_Stokes3_S0);
    vSpaces[1].Set_Ui(
                ui->label_Pol_S1,
                ui->progressBar_S1,
                ui->doubleSpinBox_X1_R_S1,
                ui->doubleSpinBox_X1_I_S1,
                ui->doubleSpinBox_X2_R_S1,
                ui->doubleSpinBox_X2_I_S1,
                ui->doubleSpinBox_Stokes0_S1,
                ui->doubleSpinBox_Stokes1_S1,
                ui->doubleSpinBox_Stokes2_S1,
                ui->doubleSpinBox_Stokes3_S1);
    vSpaces[2].Set_Ui(
                ui->label_Pol_S2,
                ui->progressBar_S2,
                ui->doubleSpinBox_X1_R_S2,
                ui->doubleSpinBox_X1_I_S2,
                ui->doubleSpinBox_X2_R_S2,
                ui->doubleSpinBox_X2_I_S2,
                ui->doubleSpinBox_Stokes0_S2,
                ui->doubleSpinBox_Stokes1_S2,
                ui->doubleSpinBox_Stokes2_S2,
                ui->doubleSpinBox_Stokes3_S2);
    vSpaces[3].Set_Ui(
                ui->label_Pol_S3,
                ui->progressBar_S3,
                ui->doubleSpinBox_X1_R_S3,
                ui->doubleSpinBox_X1_I_S3,
                ui->doubleSpinBox_X2_R_S3,
                ui->doubleSpinBox_X2_I_S3,
                ui->doubleSpinBox_Stokes0_S3,
                ui->doubleSpinBox_Stokes1_S3,
                ui->doubleSpinBox_Stokes2_S3,
                ui->doubleSpinBox_Stokes3_S3);
    vSpaces[4].Set_Ui(
                ui->label_Pol_S4,
                ui->progressBar_S4,
                ui->doubleSpinBox_X1_R_S4,
                ui->doubleSpinBox_X1_I_S4,
                ui->doubleSpinBox_X2_R_S4,
                ui->doubleSpinBox_X2_I_S4,
                ui->doubleSpinBox_Stokes0_S4,
                ui->doubleSpinBox_Stokes1_S4,
                ui->doubleSpinBox_Stokes2_S4,
                ui->doubleSpinBox_Stokes3_S4);


    //Elements
    vElements.resize(4, PS_Element());
    vElements[0].Set_Ui(
                ui->comboBox_Type_E1,
                ui->dial_Angle_E1,
                ui->doubleSpinBox_Angle_E1,
                ui->action_Rotate_Element_1,
                ui->doubleSpinBox_M11_R_E1,
                ui->doubleSpinBox_M11_I_E1,
                ui->doubleSpinBox_M12_R_E1,
                ui->doubleSpinBox_M12_I_E1,
                ui->doubleSpinBox_M21_R_E1,
                ui->doubleSpinBox_M21_I_E1,
                ui->doubleSpinBox_M22_R_E1,
                ui->doubleSpinBox_M22_I_E1);
    vElements[1].Set_Ui(
                ui->comboBox_Type_E2,
                ui->dial_Angle_E2,
                ui->doubleSpinBox_Angle_E2,
                ui->action_Rotate_Element_2,
                ui->doubleSpinBox_M11_R_E2,
                ui->doubleSpinBox_M11_I_E2,
                ui->doubleSpinBox_M12_R_E2,
                ui->doubleSpinBox_M12_I_E2,
                ui->doubleSpinBox_M21_R_E2,
                ui->doubleSpinBox_M21_I_E2,
                ui->doubleSpinBox_M22_R_E2,
                ui->doubleSpinBox_M22_I_E2);
    vElements[2].Set_Ui(
                ui->comboBox_Type_E3,
                ui->dial_Angle_E3,
                ui->doubleSpinBox_Angle_E3,
                ui->action_Rotate_Element_3,
                ui->doubleSpinBox_M11_R_E3,
                ui->doubleSpinBox_M11_I_E3,
                ui->doubleSpinBox_M12_R_E3,
                ui->doubleSpinBox_M12_I_E3,
                ui->doubleSpinBox_M21_R_E3,
                ui->doubleSpinBox_M21_I_E3,
                ui->doubleSpinBox_M22_R_E3,
                ui->doubleSpinBox_M22_I_E3);
    vElements[3].Set_Ui(
                ui->comboBox_Type_E4,
                ui->dial_Angle_E4,
                ui->doubleSpinBox_Angle_E4,
                ui->action_Rotate_Element_4,
                ui->doubleSpinBox_M11_R_E4,
                ui->doubleSpinBox_M11_I_E4,
                ui->doubleSpinBox_M12_R_E4,
                ui->doubleSpinBox_M12_I_E4,
                ui->doubleSpinBox_M21_R_E4,
                ui->doubleSpinBox_M21_I_E4,
                ui->doubleSpinBox_M22_R_E4,
                ui->doubleSpinBox_M22_I_E4);

    //connect stuff
    vSpaces[1].Set_SpaceInput(&(vSpaces[0]));
    vSpaces[2].Set_SpaceInput(&(vSpaces[1]));
    vSpaces[3].Set_SpaceInput(&(vSpaces[2]));
    vSpaces[4].Set_SpaceInput(&(vSpaces[3]));
    vSpaces[1].Set_ElementInput(&(vElements[0]));
    vSpaces[2].Set_ElementInput(&(vElements[1]));
    vSpaces[3].Set_ElementInput(&(vElements[2]));
    vSpaces[4].Set_ElementInput(&(vElements[3]));

    Plot_Init();

    //connect Autoupdate of plot
    connect(&(vSpaces[4]), SIGNAL(Updated()), this, SLOT(Update_Plot()));

    this->showMaximized();
    this->setWindowTitle("Polarisation Simulator");
    pLabelStatusbar = new QLabel(this);
    pLabelStatusbar->setText("by David Eilenstein (h_da)");
    ui->statusBar->addPermanentWidget(pLabelStatusbar);

    //initial shows
    for(size_t s = 0; s < vSpaces.size(); s++)
        vSpaces[s].Update_PolStateDraw();
    Update_Plot();
}

PS_MainWindow::~PS_MainWindow()
{
    delete ui;
}

void PS_MainWindow::Update_Plot()
{
    for(size_t s = 0; s < PLOT_SERIES_COUNT; s++)
            vSpaces[s+1].Get_Rotation(pSeriesLine[s], pSeriesDot[s]);
}

void PS_MainWindow::Plot_Init()
{
    //Chart & Chartview
    pChartView = new QChartView(this);
    pChart = new QChart();
    pChartView->setChart(pChart);
    ui->gridLayout_Plot->addWidget(pChartView);
    pChartView->setInteractive(true);
    //pChartView->setRenderHint(QPainter::Antialiasing);

    //axis
    pAxisX = new QValueAxis();
    pAxisX->setTitleText("Rotation of Element before Space");
    pAxisX->setMin(PLOT_MIN_X);
    pAxisX->setMax(PLOT_MAX_X);
    pChart->setAxisX(pAxisX);
    pAxisY = new QValueAxis();
    pAxisY->setTitleText("Amplitude(thin) and Intensity(thick)");
    pAxisY->setMin(PLOT_MIN_Y);
    pAxisY->setMax(PLOT_MAX_Y);
    pChart->setAxisY(pAxisY);

    //hello wrorls

    //Series
    for(size_t s = 0; s < PLOT_SERIES_COUNT; s++)
    {
        //Selected Angles
        pSeriesDot[s] = new QScatterSeries();
        pChart->addSeries(pSeriesDot[s]);
        pSeriesDot[s]->attachAxis(pAxisX);
        pSeriesDot[s]->attachAxis(pAxisY);

        //Lines
        for(size_t p = 0; p < PLOT_NUMBER_OF; p++)
        {
            pSeriesLine[s][p] = new QSplineSeries();
            pChart->addSeries(pSeriesLine[s][p]);
            pSeriesLine[s][p]->attachAxis(pAxisX);
            pSeriesLine[s][p]->attachAxis(pAxisY);
        }

        //Style
        //Dot
        pSeriesDot[s]->setColor(PLOT_SERIES_COLORS[s]);
        pSeriesDot[s]->setMarkerSize(16);
        pSeriesDot[s]->setName("angle" + QString::number(s+1));
        //Line
        QPen pen = pSeriesLine[s][0]->pen();
        pen.setColor(PLOT_SERIES_COLORS[s]);
        pen.setWidth(1);
        pen.setStyle((Qt::DotLine));
        pSeriesLine[s][PLOT_IMAG]->setPen(pen);
        pSeriesLine[s][PLOT_IMAG]->setName("im" + QString::number(s+1));
        pen.setStyle(Qt::SolidLine);
        pSeriesLine[s][PLOT_REAL]->setPen(pen);
        pSeriesLine[s][PLOT_REAL]->setName("re" + QString::number(s+1));
        pen.setWidth(3);
        pSeriesLine[s][PLOT_SQUARE]->setPen(pen);
        pSeriesLine[s][PLOT_SQUARE]->setName("intensity" + QString::number(s+1));
    }

    //Legend

}

void PS_MainWindow::on_action_Calc_Stokes_triggered()
{
    PS_StokesCalc stokes_window(&DIR_Operation);
    stokes_window.exec();
}

void PS_MainWindow::on_action_All_triggered()
{
    QString name_save = QFileDialog::getSaveFileName(
                this,
                "Save Stokes Calculation",
                DIR_Operation.path() + "/Setup.jpg",
                tr("Image Files (*.png *.jpg *.bmp)"));
    if(name_save.isEmpty())
        return;

    this->grab().save(name_save);
    DIR_Operation.setPath(name_save);
}

void PS_MainWindow::on_action_Plot_triggered()
{
    QString name_save = QFileDialog::getSaveFileName(
                this,
                "Save Stokes Calculation",
                DIR_Operation.path() + "/Plot.jpg",
                tr("Image Files (*.png *.jpg *.bmp)"));
    if(name_save.isEmpty())
        return;

    pChartView->grab().save(name_save);
    DIR_Operation.setPath(name_save);
}

void PS_MainWindow::on_action_Normal_triggered()
{
    this->showNormal();
}

void PS_MainWindow::on_action_Minimum_triggered()
{
    this->showMinimized();
}

void PS_MainWindow::on_action_Maximum_triggered()
{
    this->showMaximized();
}

void PS_MainWindow::on_action_Fullscreen_triggered()
{
    this->showFullScreen();
}
