#ifndef OPERATING_SYSTEM_PARAMETERS_H
#define OPERATING_SYSTEM_PARAMETERS_H

#include <QDialog>

#include <QSpinBox>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>

#include <QHBoxLayout>
#include <QVBoxLayout>


class OperatingSystemParameters : public QDialog
{
    Q_OBJECT

    QSpinBox *radiationFrequencyBox;
    QSpinBox *receivingFrequencyBox;
    QSpinBox *pulseDurationBox;
    QSpinBox *riseTimeBox;
    QSpinBox *pressureBox;

    QRadioButton *rectRadioButton;
    QRadioButton *trapezRadioButton;
    QRadioButton *unitRadioButton;

    QLabel *label4;


public:
    explicit OperatingSystemParameters(QWidget *parent = nullptr);
    ~OperatingSystemParameters();

    int pulseDuration;
    int riseTime;
    int pressure;
    int radiationFreq;
    int receivingFreq;
    int impulseType;

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();


    void on_rectRadioButton_clicked(bool checked);

    void on_trapezRadioButton_clicked(bool checked);

    void on_unitRadioButton_clicked(bool checked);



signals:
    void signalOperatingSystemParametersToMain (int pulseDuration, int riseTime,  int pressure,
        int radiation_freq,int receiving_freq, int impulseType);

public slots:
   void slotMainToOperatingSystemParameters (int pulseDuration, int riseTime, int pressure,
                                                  int radiation_freq,int receiving_freq, int impulseType);

};

#endif // OPERATING_SYSTEM_PARAMETERS_H
