#ifndef ECHOSIGNAL_H
#define ECHOSIGNAL_H

#include <QDialog>

namespace Ui {
class EchoSignal;
}

class EchoSignal : public QDialog
{
    Q_OBJECT

    bool ECHO_TYPE;

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

private:
    Ui::EchoSignal *ui;
};

#endif // ECHOSIGNAL_H
