#ifndef CARRIER_PARAMETERS_H
#define CARRIER_PARAMETERS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>



class CarrierParameters : public QDialog
{
    Q_OBJECT
    QDoubleSpinBox *HSubBox;
    QDoubleSpinBox *LSubBox;
    QDoubleSpinBox *speedBox;
    QDoubleSpinBox *noiseEngBox;

public:
    explicit CarrierParameters(QWidget *parent = nullptr);
    ~CarrierParameters();

public slots:
    void slot_mainToCarrierParameters(double HSub1, double LSub1, double speed1, double noise1);

signals:
    void signal_carrierParametersToMain(double HSub1, double LSub1, double speed1, double noise1);

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonSave_clicked();

};

#endif // CARRIER_PARAMETERS_H
