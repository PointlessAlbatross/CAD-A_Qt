#include "operating_system_parameters.h"
#include "ui_operating_system_parameters.h"

Operating_system_parameters::Operating_system_parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Operating_system_parameters)
{
    ui->setupUi(this);
}

Operating_system_parameters::~Operating_system_parameters()
{
    delete ui;
}

void Operating_system_parameters::on_pushButton_clicked()
{
    emit signal_operating_system_parameters_to_main (ui->durationBox->value(), ui->pressureBox->value(),
                                                     ui->radiationFrequencyBox->value(), ui->receivingFrequencyBox->value());
    QWidget::close();
}


void Operating_system_parameters::on_pushButton_2_clicked()
{
    QWidget::close();
}

void Operating_system_parameters::slot_main_to_operating_system_parameters(int duration1, int pressure1, int radiation_freq1, int receiving_freq1)
{
    duration = duration1;
    pressure = pressure1;
    receiving_freq = receiving_freq1;
    radiation_freq = radiation_freq1;
    ui->durationBox->setValue(duration);
    ui->pressureBox->setValue(pressure);
    ui->radiationFrequencyBox->setValue(radiation_freq);
    ui->receivingFrequencyBox->setValue(receiving_freq);
}

