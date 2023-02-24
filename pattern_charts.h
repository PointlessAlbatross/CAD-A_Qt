#ifndef PATTERN_CHARTS_H
#define PATTERN_CHARTS_H

#include <QDialog>
#include <cmath>
#include <ccomplex>
#include <QPainter>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPolarChart>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

namespace Ui {
class Pattern_charts;
}

class Pattern_charts : public QDialog
{
    Q_OBJECT

public:
    explicit Pattern_charts(QWidget *parent = nullptr);
    ~Pattern_charts();

private:

    QVector<int> Curr_num_elem;
    QVector<QVector<double> > Weight_coef;
    QVector<QVector<QPair<double,double>>> Center_pos;

    double k;
    double size_x;
    double size_z;
    double dist_x;
    double dist_z;


    double theta;
    double theta_t;
    double phi;
    double phi_t;

    int reg_chart;

    double D(double theta, double phi);
    std::complex<double> Dt(double theta, double phi);
    void drow_chart();
    void drow_polar_chart();

public slots:
    void slot_main_to_charts(QVector<int> Curr_num_elem, QVector<QVector<double> > Weight_coef,
                             QVector<QVector<std::tuple<int, int, int> > > Button_pos,
                             double k,
                             double size_x, double size_z, double dist_x, double dist_z,
                             int size_x_pix, int size_z_pix);
private:
    Ui::Pattern_charts *ui;
};

#endif // PATTERN_CHARTS_H
