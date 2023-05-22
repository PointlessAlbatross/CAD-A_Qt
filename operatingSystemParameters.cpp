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
    emit signalOperatingSystemParametersToMain (ui->pulseDurationBox->value(), riseTime, ui->pressureBox->value(),
                                                     ui->radiationFrequencyBox->value(), ui->receivingFrequencyBox->value(), impulseType);
    QWidget::close();
}


void OperatingSystemParameters::on_pushButton_2_clicked()
{
    QWidget::close();
}

void OperatingSystemParameters::slotMainToOperatingSystemParameters(int pulseDuration1, int riseTime1, int pressure1, int radiation_freq1, int receiving_freq1, int impulseType1)
{
    impulseType = impulseType1;
    switch (impulseType1) {
    case 1:
        ui->rectRadioButton->setChecked(true);
        ui->riseTimeBox->hide();
        break;
    case 2:
        ui->trapezRadioButton->setChecked(true);
        break;
    case 3:
        ui->unitRadioButton->setChecked(true);
        ui->riseTimeBox->hide();
        break;
    default:
        break;
    }
    pulseDuration = pulseDuration1;
    riseTime = riseTime1;
    pressure = pressure1;
    receivingFreq = receiving_freq1;
    radiationFreq = radiation_freq1;
    ui->pulseDurationBox->setValue(pulseDuration);
    ui->riseTimeBox->setValue(riseTime);
    ui->pressureBox->setValue(pressure);
    ui->radiationFrequencyBox->setValue(radiationFreq);
    ui->receivingFrequencyBox->setValue(receivingFreq);
}


void OperatingSystemParameters::on_rectRadioButton_clicked(bool checked)
{
    if (checked)
    {
        impulseType = 1;
        ui->riseTimeBox->hide();
    }
}


void OperatingSystemParameters::on_trapezRadioButton_clicked(bool checked)
{
    if (checked)
    {
        impulseType = 2;
        ui->riseTimeBox->show();
    }
}

void OperatingSystemParameters::on_unitRadioButton_clicked(bool checked)
{
    if (checked)
    {
        impulseType = 3;
        ui->riseTimeBox->hide();
    }
}
