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
class PatternCharts;
}

class PatternCharts : public QDialog
{
    Q_OBJECT

public:
    explicit PatternCharts(QWidget *parent = nullptr);
    ~PatternCharts();

private:

    QVector<int> CurrNumElem;
    std::array<QVector<QVector<double>>, 17>  WeightCoef;
    QVector<QVector<QPair<double,double>>> CenterPos;
    QVector<QVector<std::tuple<int, int, int> > > ButtonPos;
    int overlayType;

    double k;
    double sizeX;
    double sizeZ;
    double distX;
    double distZ;

    double radCircScr;
    double distHex;
    int radCircScrPix;
    int distHexPix;

    double theta;
    double theta_t;
    double phi;
    double phi_t;

    int regChart;

    double D(double theta, double phi);
    std::complex<double> Dt(double theta, double phi);
    void drawChart();
    void drawPolarChart();

public slots:
    void slotMainToCharts(QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17>  Weight_coef,
                             QVector<QVector<std::tuple<int, int, int> > > Button_pos,
                             double k,
                             double size_x, double size_z, double dist_x, double dist_z,
                             int size_x_pix, int size_z_pix,
                             double rad_circ_scr, double dist_hex,
                             int rad_circ_scr_pix, int dist_hex_pix,
                             int overlay_type);
private:
    Ui::PatternCharts *ui;
};

#endif // PATTERN_CHARTS_H
