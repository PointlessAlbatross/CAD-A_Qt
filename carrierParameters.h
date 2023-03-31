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

private:
    Ui::CarrierParameters *ui;
};

#endif // CARRIER_PARAMETERS_H
