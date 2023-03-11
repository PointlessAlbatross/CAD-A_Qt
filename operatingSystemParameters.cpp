#include "operatingSystemParameters.h"
#include "ui_operatingSystemParameters.h"

Operating_system_parameters::Operating_system_parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Operating_system_parameters)
{
    ui->setupUi(this);
    ui->radiationFrequencyBox->setFocus();
    ui->radiationFrequencyBox->selectAll();
}

Operating_system_parameters::~Operating_system_parameters()
{
    delete ui;
}

void Operating_system_parameters::on_pushButton_clicked()
{
    emit signalOperatingSystemParametersToMain (ui->durationBox->value(), ui->pressureBox->value(),
                                                     ui->radiationFrequencyBox->value(), ui->receivingFrequencyBox->value());
    QWidget::close();
}


void Operating_system_parameters::on_pushButton_2_clicked()
{
    QWidget::close();
}

void Operating_system_parameters::slotMainToOperatingSystemParameters(int duration1, int pressure1, int radiation_freq1, int receiving_freq1)
{
    duration = duration1;
    pressure = pressure1;
    receivingFreq = receiving_freq1;
    radiationFreq = radiation_freq1;
    ui->durationBox->setValue(duration);
    ui->pressureBox->setValue(pressure);
    ui->radiationFrequencyBox->setValue(radiationFreq);
    ui->receivingFrequencyBox->setValue(receivingFreq);
}

