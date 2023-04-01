#ifndef CARRIER_PARAMETERS_H
#define CARRIER_PARAMETERS_H

#include <QDialog>

namespace Ui {
class CarrierParameters;
}

class CarrierParameters : public QDialog
{
    Q_OBJECT

public:
    explicit CarrierParameters(QWidget *parent = nullptr);
    ~CarrierParameters();

public slots:
    void slot_mainToCarrierParameters(double HSub1, double LSub1, double speed1);

signals:
    void signal_carrierParametersToMain(double HSub1, double LSub1, double speed1);

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonSave_clicked();

private:
    Ui::CarrierParameters *ui;
};

#endif // CARRIER_PARAMETERS_H
