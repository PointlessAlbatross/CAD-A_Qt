#include "radiation_pattern_parameters.h"
#include "ui_radiation_pattern_parameters.h"

Radiation_pattern_parameters::Radiation_pattern_parameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Radiation_pattern_parameters)
{
    ui->setupUi(this);
}

Radiation_pattern_parameters::~Radiation_pattern_parameters()
{
    delete ui;
}
