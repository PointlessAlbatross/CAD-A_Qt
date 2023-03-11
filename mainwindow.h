#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <antennaArrayParametersRect.h>
#include <antennaArrayParametersHex.h>
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int overlayType;

    double radCircScr;
    double distHex;

    double sizeX;
    double sizeZ;
    double distX;
    double distZ;

    double radAnt;

    int sizeXPix;
    int sizeZPix;
    int distXPix;
    int distZPix;

    int radCircScrPix;
    int distHexPix;

    int duration;
    int pressure;
    int radiationFreq;
    int receivingFreq;
    double k; // Волновое число

    int num_row;
    QVector<int> Max_elem;

    std::array<QVector<QVector<bool>>, 16> SelectedElem;
    QVector<int> CurrNumElem;
    QVector<QVector<double>> WeightCoef;
    QVector<QVector<std::tuple<int, int, int> > > ButtonPos;


    bool PARAM_WINDOW_FLAG;


private slots:
    void on_action_triggered();
    void on_antenna_array_triggered();
    void on_exit_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_charts_action_triggered();


signals:
    void signalMainToParamRect(double size_x, double size_z,
                double dist_x, double dist_z,
                double rad_ant, int num_row);
    void signalMainToParamHex(double size_x, double dist,
                double rad_ant, int num_row);
    void signalMainToOperatingSystemParameters(int duration, int pressure, int receiving_freq,
                                                    int radiation_freq);
    void signalMainToArrange(double size_x, double size_z, double dist_x, double dist_z,
                double rad_circ_scr, double dist,
                double rad_ant, int num_row, QVector<int> Max_elem, QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef,
                std::array<QVector<QVector<bool>>, 16> Selected_elem,
                                int overlay_type);
    void signalMainToCharts(QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef, QVector<QVector<std::tuple<int, int, int> > > Button_pos,
                               double k,
                               double size_x, double size_z, double dist_x, double dist_z,
                               int size_x_pix, int size_z_pix,
                               double rad_circ_scr, double dist_hex,
                               int rad_circ_scr_pix, int dist_hex_pix,
                               int overlay_type);
public slots:
    void slotParamRectToMain(double size_x, double size_z,
              double dist_x, double dist_z,
              double rad_ant, int num_row,
              QVector<int> Max_elem);
    void slotParamHexToMain(double rad_circ_scr, double dist,
              double rad_ant, int num_row,
              QVector<int> Max_elem);
    void slotOperatingSystemParametersToMain(int duration, int pressure, int receiving_freq,
                                                  int radiation_freq);
    void slotArrangeToMain(QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef, QVector <QVector<std::tuple<int, int, int>>> Button_pos,
                              int size_x_pix, int size_z_pix, int dist_x_pix, int dist_z_pix,
                              int rad_circ_scr_pix, int dist_hex_pix);

};
#endif // MAINWINDOW_H
