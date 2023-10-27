#ifndef ECHOSIGNAL_H
#define ECHOSIGNAL_H

#include <QDialog>

#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class EchoSignal : public QDialog
{
    Q_OBJECT

    int echo_type;

    QDoubleSpinBox *elevationBox;
    QDoubleSpinBox *azimuthBox;
    QDoubleSpinBox *relativeSpedBox;
    QDoubleSpinBox *equivalentRadBox;
    QSpinBox *channelBox;
    QSpinBox *numDotBox;

    QDoubleSpinBox *param1Box;
    QDoubleSpinBox *param2Box;
    QDoubleSpinBox *param3Box;

    QLabel *labelParam_1;
    QLabel *labelParam_2;
    QLabel *labelParam_3;


public:
    explicit EchoSignal(QWidget *parent = nullptr);
    ~EchoSignal();
signals:
    void signal_echoSignalToMain(double param1, double param2, double param3, int channel, int numDot,  int typeEchoSign, bool isCalculate, double elevation, double azimuth, double relative_speed, double R_ekv);
public slots:
    void slot_mainToEchoSignal(double param1, double param2, double param3, int channel, int numDot,  int typeEchoSign,  double elevation, double azimuth, double relative_speed, double R_ekv);

private slots:
    void on_pushButtonCompute_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();

};

#endif // ECHOSIGNAL_H
