#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <antennaArrayParametersRect.h>
#include <antennaArrayParametersHex.h>
#include "operatingSystemParameters.h"
#include "arrangementOfElements.h"
#include "antennaArrayParametersRect.h"
#include "antennaArrayParametersHex.h"
#include "selectionOfCorrectiveElements.h"
#include "patternCharts.h"
#include "workingEnvironmentSettings.h"
#include "carrierParameters.h"
#include "channelParameters.h"
#include "reverberationParameters.h"

#include <array>
#include <ccomplex>
#include <functional>
#include "cadAMath.h"
#include <QMessageBox>
#include <QDebug>
#include <QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    CadAMath m_cadAMath;

private:
    Ui::MainWindow *ui;

    int antennaType;
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

    int impulseType;
    int pulseDuration;
    int riseTime;
    int pressure;
    int radiationFreq;
    int receivingFreq;
    double k; // Волновое число

    int num_row;
    QVector<int> Max_elem;

    std::array<QVector<QVector<bool>>, 16> SelectedElem;
    QVector<int> CurrNumElem;
    std::array<QVector<QVector<double>>, 17> WeightCoef;
    //QVector<QVector<std::tuple<int, int, int> > > ButtonPos;
    QVector<QVector<QPair<double,double>>> CenterPos;
    std::array<QPair<double, double>, 16> Centroids;
    std::array<QPair<double, double>, 30> SubarrayCenter;

    QVector<double> ElemetTurbPower;


    bool PARAM_WINDOW_FLAG;

    double q;
    double q1;
    double freq;       // f
    double deltaFreq;  // delta_f
    double capacity_0; // C0
    double capacity;   // C
    double resistance; // R
    double inductance; // L

    QVector<double> abs_K;
    QVector<double> abs_K0;

    double HSub;
    double LSub;
    double speed;
    double noiseEng;

    double depthSea;
    double windSpeed;
    double salinity;
    double tempWater;
    double volumeDisp;
    double surfReflCoef;
    double botReflCoef;

    std::array<std::array<bool, 16>, 30> TableChannel;

    std::array<double,16> Arr_sensitivityGroup;

    std::complex<double> DLt(double theta, double phi, int chn); //диаграмма направленности канала
    std::complex<double> DUt(double theta, double phi, int grp); //диаграмма направленности группы
    std::complex<double> Dt(double theta, double phi, int grp); //диаграмма направленности
    double D(double theta, double phi);

    double reverbDist1;
    double reverbDist2;
    double reverbDist3;
    double reverbFreq1;
    double reverbFreq2;
    double reverbFreq3;
    int reverbChannel1;
    int reverbChannel2;
    std::array<bool, 4> ReverbChecks;
    int numDot;

    double g(double f);

private slots:
    void on_action_triggered();
    void on_antenna_array_triggered();
    void on_exit_action_triggered();
    void on_action_2_triggered();
    void on_overlayAction_triggered();
    void on_charts_action_triggered();


    void on_corrective_action_triggered();

    void on_antennaTypeAction_triggered();

    void on_elemTurbulentInterf_triggered();

    void on_powerDiffuseInterf_triggered();

    void on_workingEnvironmentSettingsAction_triggered();


    void on_carrierParametersAction_triggered();

    void on_paramChanelAction_triggered();

    void on_actionRevervPowFreq_triggered();

    void on_actionRevervPowTime_triggered();

signals:
    void signalMainToParamRect(double size_x, double size_z,
                double dist_x, double dist_z,
                double rad_ant, int num_row);
    void signalMainToParamHex(double size_x, double dist,
                double rad_ant, int num_row);
    void signalMainToOperatingSystemParameters(int pulseDuration, int riseTime, int pressure, int receiving_freq,
                                                    int radiation_freq, int impulseType);
    void signalMainToArrange(double size_x, double size_z, double dist_x, double dist_z,
                double rad_circ_scr, double dist,
                double rad_ant, int num_row, QVector<int> Max_elem, QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17> Weight_coef,
                std::array<QVector<QVector<bool>>, 16> Selected_elem,
                                 int antenna_type, int overlay_type);
    void signalMainToCharts(QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17> Weight_coef, QVector<QVector<QPair<double,double>>> Center_pos,
                               double k,
                               double size_x, double size_z, double dist_x, double dist_z,
                               double rad_circ_scr, double dist_hex,
                               int overlay_type);
    void signal_mainToSelectionOfCorrectiveElements(double qSignal, double q1Signal, double f, double delta_f,
                                                    double C0, double C, double R, double L);

    void signal_mainToWorkingEnvironmentSettings(double depthSea1, double windSpeed1,
                                                 double salinity1, double tempWater1,
                                                 double volumeDisp1,
                                                 double surfReflCoef1, double botReflCoef1
                                                 );

    void signal_mainToCarrierParameters(double HSub, double LSub, double speed, double noiseEng);
    void signal_mainToChannelParameters(std::array<std::array<bool, 16>, 30> Table);
    void signal_mainToReverberationParameters1(double param1, double param2, double param3, int channel1, int numDot, std::array<bool, 4> ReverbChecks, int typeReverb);
    void signal_mainToReverberationParameters2(double param1, double param2, double param3, int channel1, int channel2, int numDot, std::array<bool, 4> ReverbChecks, int typeReverb);

public slots:
    void slotParamRectToMain(double size_x, double size_z,
              double dist_x, double dist_z,
              double rad_ant, int num_row,
              QVector<int> Max_elem);
    void slotParamHexToMain(double rad_circ_scr, double dist,
              double rad_ant, int num_row,
              QVector<int> Max_elem);
    void slotOperatingSystemParametersToMain(int duration, int riseTime, int pressure, int receiving_freq,
                                                  int radiation_freq, int impulseType);
    void slotArrangeToMain(QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17>  Weight_coef, QVector<QVector<QPair<double,double>>> Center_pos,
                           std::array<QPair<double, double>, 16> Centroids, std::array<double,16> Arr_Denum, std::array<QVector<QVector<bool>>, 16> SelectedElem);
    void slot_selectionOfCorrectiveElementsToMain_save(double qSlot, double q1Slot, double f, double delta_f,
                                                        double C0, double C, double R, double L);
    void slot_selectionOfCorrectiveElementsToMain_calculate(double qSlot, double q1Slot, double f, double delta_f,
                                                            double C0, double C, double R, double L);

    void slot_workingEnvironmentSettingsToMain(double depthSea1, double windSpeed1,
                                               double salinity1, double tempWater1,
                                               double volumeDisp1,
                                               double surfReflCoef1, double botReflCoef1
                                               );

    void slot_carrierParametersToMain(double HSub1, double LSub1, double speed1, double noiseEng1);
    void slot_channelParametersToMain(std::array<std::array<bool, 16>, 30> Table);
    void slot_reverberationParametersToMain1(double param1, double param2, double param3, int channel1, int numDot,
                                             std::array<bool, 4> ReverbChecks, int typeReverb, bool isCalculate);
    void slot_reverberationParametersToMain2(double param1, double param2, double param3, int channel1, int channel2, int numDot,
                                             std::array<bool, 4> ReverbChecks, int typeReverb, bool isCalculate);

};
#endif // MAINWINDOW_H
