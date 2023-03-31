#include "carrierParameters.h"
#include "ui_carrierParameters.h"

CarrierParameters::CarrierParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarrierParameters)
{
    ui->setupUi(this);
}

CarrierParameters::~CarrierParameters()
{
    delete ui;
}
