#ifndef OPERATING_SYSTEM_PARAMETERS_H
#define OPERATING_SYSTEM_PARAMETERS_H

#include <QDialog>

namespace Ui {
class OperatingSystemParameters;
}

class OperatingSystemParameters : public QDialog
{
    Q_OBJECT

public:
    explicit OperatingSystemParameters(QWidget *parent = nullptr);
    ~OperatingSystemParameters();

    int duration;
    int pressure;
    int radiationFreq;
    int receivingFreq;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


signals:
    void signalOperatingSystemParametersToMain (int duration, int pressure,
        int radiation_freq,int receiving_freq);

public slots:
   void slotMainToOperatingSystemParameters (int duration, int pressure,
                                                  int radiation_freq,int receiving_freq);

private:
    Ui::OperatingSystemParameters *ui;
};

#endif // OPERATING_SYSTEM_PARAMETERS_H
