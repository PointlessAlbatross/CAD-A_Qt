#include "operatingSystemParameters.h"
#include "ui_operatingSystemParameters.h"

OperatingSystemParameters::OperatingSystemParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperatingSystemParameters)
{
    ui->setupUi(this);
    ui->radiationFrequencyBox->setFocus();
    ui->radiationFrequencyBox->selectAll();
}

OperatingSystemParameters::~OperatingSystemParameters()
{
    delete ui;
}

void OperatingSystemParameters::on_pushButton_clicked()
{
    emit signalOperatingSystemParametersToMain (ui->durationBox->value(), ui->pressureBox->value(),
                                                     ui->radiationFrequencyBox->value(), ui->receivingFrequencyBox->value());
    QWidget::close();
}


void OperatingSystemParameters::on_pushButton_2_clicked()
{
    QWidget::close();
}

void OperatingSystemParameters::slotMainToOperatingSystemParameters(int duration1, int pressure1, int radiation_freq1, int receiving_freq1)
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

