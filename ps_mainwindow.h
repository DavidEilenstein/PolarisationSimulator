#ifndef PS_MAINWINDOW_H
#define PS_MAINWINDOW_H

#include <ps_enum.h>
#include <ps_space.h>
#include <ps_element.h>
#include <ps_stokescalc.h>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QLabel>

using namespace std;
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class PS_MainWindow;
}

class PS_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PS_MainWindow(QWidget *parent = nullptr);
    ~PS_MainWindow();

public slots:
    void Update_Plot();

private slots:

    void on_action_Calc_Stokes_triggered();

    void on_action_All_triggered();

    void on_action_Plot_triggered();

    void on_action_Normal_triggered();

    void on_action_Minimum_triggered();

    void on_action_Maximum_triggered();

    void on_action_Fullscreen_triggered();

private:
    Ui::PS_MainWindow *ui;

    //optical axis:
    vector<PS_Space>    vSpaces;    //  0       1       2       3       4       5
    vector<PS_Element>  vElements;  //      1       2       3       4       5

    //Charts
    void            Plot_Init();
    QChartView      *pChartView;
    QChart          *pChart;
    QValueAxis      *pAxisX;
    QValueAxis      *pAxisY;
    QSplineSeries   *pSeriesLine[4][3];
    QScatterSeries  *pSeriesDot[4];

    QDir            DIR_Operation;
    QLabel          *pLabelStatusbar;
};

#endif // PS_MAINWINDOW_H
