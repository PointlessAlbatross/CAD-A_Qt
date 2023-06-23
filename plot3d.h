#ifndef PLOT3D_H
#define PLOT3D_H

#include <QDialog>
#include <cmath>
#include <ccomplex>
#include <QPainter>

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

#include <QDialog>

namespace Ui {
class Plot3D;
}

class Plot3D : public QDialog
{
    Q_OBJECT

    double D(double theta, double phi);
    std::complex<double> Dt(double theta, double phi);


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

    int chartsChannel;

    int regChart;

    std::array<std::array<bool, 16>, 30> TableChannel;
    std::array<double,16> Arr_sensitivityGroup;
    std::array<QPair<double, double>, 30> SubarrayCenter;
    std::array<QVector<QVector<bool>>, 16> SelectedElem;
    std::array<QPair<double, double>, 16> Centroids;

    void plot3D();

public:
    explicit Plot3D(QWidget *parent = nullptr);
    ~Plot3D();

private:
    Ui::Plot3D *ui;

public slots:
    void slot_MainToPlot3D(QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17> Weight_coef, QVector<QVector<QPair<double,double>>> Center_pos,
                           double k,
                           double size_x, double size_z, double dist_x, double dist_z,
                           double rad_circ_scr, double dist_hex,
                           int overlay_type,
                           std::array<std::array<bool, 16>, 30> TableChannel,
                           std::array<double,16> Arr_sensitivityGroup,
                           std::array<QPair<double, double>, 30> SubarrayCenter,
                           std::array<QVector<QVector<bool>>, 16> SelectedElem,
                           std::array<QPair<double, double>, 16> Centroids,
                           int antennaType, int chartsChannel);

};

#endif // PLOT3D_H
