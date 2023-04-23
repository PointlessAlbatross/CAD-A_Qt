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
    emit signalOperatingSystemParametersToMain (ui->pulseDurationBox->value(), ui->pressureBox->value(),
                                                     ui->radiationFrequencyBox->value(), ui->receivingFrequencyBox->value());
    QWidget::close();
}


void OperatingSystemParameters::on_pushButton_2_clicked()
{
    QWidget::close();
}

void OperatingSystemParameters::slotMainToOperatingSystemParameters(int pulseDuration1, int pressure1, int radiation_freq1, int receiving_freq1)
{
    pulseDuration = pulseDuration1;
    pressure = pressure1;
    receivingFreq = receiving_freq1;
    radiationFreq = radiation_freq1;
    ui->pulseDurationBox->setValue(pulseDuration);
    ui->pressureBox->setValue(pressure);
    ui->radiationFrequencyBox->setValue(radiationFreq);
    ui->receivingFrequencyBox->setValue(receivingFreq);
}

