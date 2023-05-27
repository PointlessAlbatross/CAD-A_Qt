#include "chartsParameters.h"
#include "ui_chartsParameters.h"

ChartsParameters::ChartsParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartsParameters)
{
    ui->setupUi(this);
}

ChartsParameters::~ChartsParameters()
{
    delete ui;
}

void ChartsParameters::slot_mainToChartsParameters(int chartsChannel)
{
    ui->channelBox->setValue(chartsChannel);
}

void ChartsParameters::on_pushButtonSave_clicked()
{
    emit signal_chartsParametersToMain(ui->channelBox->value());
    QWidget::close();
}


void ChartsParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

