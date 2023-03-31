#ifndef CARRIERPARAMETERS_H
#define CARRIERPARAMETERS_H

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

private:
    Ui::CarrierParameters *ui;
};

#endif // CARRIERPARAMETERS_H
