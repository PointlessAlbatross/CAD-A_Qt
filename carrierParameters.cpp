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

void CarrierParameters::slot_mainToCarrierParameters(double HSub1, double LSub1, double speed1, double noise1)
{
    ui->HSubBox->setValue(HSub1);
    ui->LSubBox->setValue(LSub1);
    ui->speedBox->setValue(speed1);
    ui->noiseEngBox->setValue(noise1);
}


void CarrierParameters::on_pushButtonSave_clicked()
{
    emit signal_carrierParametersToMain (ui->HSubBox->value(),
                                         ui->LSubBox->value(),
                                         ui->speedBox->value(),
                                         ui->noiseEngBox->value());
    QWidget::close();
}

void CarrierParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}
