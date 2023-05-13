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
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>

#include "cadAMath.h"


namespace Ui {
class PatternCharts;
}

class PatternCharts : public QDialog
{
    Q_OBJECT

public:
    explicit PatternCharts(QWidget *parent = nullptr);
    ~PatternCharts();

    CadAMath m_cadAMath;

private:

    QVector<int> CurrNumElem;
    std::array<QVector<QVector<double>>, 17>  WeightCoef;
    QVector<QVector<QPair<double,double>>> CenterPos;
    int overlayType;

    double k;
    double sizeX;
    double sizeZ;
    double distX;
    double distZ;

    double radCircScr;
    double distHex;

    double theta;
    double theta_t;
    double phi;
    double phi_t;

    int regChart;

    double D(double theta, double phi);
    std::complex<double> Dt(double theta, double phi);
    void drawChart();
    void drawPhaseChart();
    void drawPolarChart();

public slots:
    void slotMainToCharts(QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17>  Weight_coef,
                             QVector<QVector<QPair<double,double>>> Center_pos,
                             double k,
                             double size_x, double size_z, double dist_x, double dist_z,
                             double rad_circ_scr, double dist_hex,
                             int overlay_type);
private:
    Ui::PatternCharts *ui;
};

#endif // PATTERN_CHARTS_H
