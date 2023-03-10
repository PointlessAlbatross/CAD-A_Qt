#ifndef OPERATING_SYSTEM_PARAMETERS_H
#define OPERATING_SYSTEM_PARAMETERS_H

#include <QDialog>

namespace Ui {
class Operating_system_parameters;
}

class Operating_system_parameters : public QDialog
{
    Q_OBJECT

public:
    explicit Operating_system_parameters(QWidget *parent = nullptr);
    ~Operating_system_parameters();

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
    Ui::Operating_system_parameters *ui;
};

#endif // OPERATING_SYSTEM_PARAMETERS_H
