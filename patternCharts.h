#ifndef PATTERN_CHARTS_H
#define PATTERN_CHARTS_H

#include <QDialog>
#include <cmath>
#include <ccomplex>
#include <QPainter>
#include <QFormLayout>


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
#include <QtCharts/QLegend>
#include <QtCharts/QLogValueAxis>

#include "cadAMath.h"


class PatternCharts : public QDialog
{
    Q_OBJECT

public:
    explicit PatternCharts(QWidget *parent = nullptr);
    ~PatternCharts();

    CadAMath m_cadAMath;

    QTabWidget *tabWidget;

    QFormLayout *formLayout1;
    QFormLayout *formLayout2;

private:

    int antennaType;
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

    std::array<std::array<bool, 16>, 30> TableChannel;
    std::array<double,16> Arr_sensitivityGroup;
    std::array<QPair<double, double>, 30> SubarrayCenter;
    std::array<QVector<QVector<bool>>, 16> SelectedElem;
    std::array<QPair<double, double>, 16> Centroids;


    double D(double theta, double phi);
    std::complex<double> Dt(double theta, double phi);
    std::complex<double> DLt(double theta, double phi, int chn); //диаграмма направленности канала
    std::complex<double> DUt(double theta, double phi, int grp); //диаграмма направленности группы
    void drawChart();
    void drawPhaseChart();
    void drawPolarChart();
    void drawReverb(QVector<double> VecSurfFreq, QVector<double> VecSurfDist, QVector<double> VecBotFreq,
                    QVector<double> VecBotDist, QVector<double> VecSurrFreq, QVector<double> VecSurrDist,
                    QVector<double> VecSumFreq, QVector<double> VecSumDist, std::array<bool, 4> ReverbChecks,
                    std::array<bool, 2> ReverbCalc, QVector<double> VecFreq,
                    QVector<double> VecDist);

    void drawEcho(QVector<double> VecFreqE,
                  QVector<double> VecEchoFreq,
                  QVector<double> VecDistE,
                  QVector<double> VecEchoDist,
                  std::array<bool, 2> EchoCalc);

    int chartsChannel;

public slots:
    void slotMainToCharts(QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17>  Weight_coef,
                             QVector<QVector<QPair<double,double>>> Center_pos,
                             double k,
                             double size_x, double size_z, double dist_x, double dist_z,
                             double rad_circ_scr, double dist_hex,
                             int overlay_type,
                             QVector<double> VecSurfFreq,
                             QVector<double> VecSurfDist,
                             QVector<double> VecBotFreq,
                             QVector<double> VecBotDist,
                             QVector<double> VecSurrFreq,
                             QVector<double> VecSurrDist,
                             QVector<double> VecSumFreq,
                             QVector<double> VecSumDist,
                             std::array<bool, 4> ReverbChecks,
                             std::array<bool, 2> ReverbCalc,
                             QVector<double> VecFreq,
                             QVector<double> VecDist,
                             QVector<double> VecFreqE,
                             QVector<double> VecEchoFreq,
                             QVector<double> VecDistE,
                             QVector<double> VecEchoDist,
                             std::array<bool, 2> EchoCalc,
                             std::array<std::array<bool, 16>, 30> TableChannel,
                             std::array<double,16> Arr_sensitivityGroup,
                             std::array<QPair<double, double>, 30> SubarrayCenter,
                             std::array<QVector<QVector<bool>>, 16> SelectedElem,
                             std::array<QPair<double, double>, 16> Centroids,
                             int antennaType, int chartsChannel);

};

#endif // PATTERN_CHARTS_H
