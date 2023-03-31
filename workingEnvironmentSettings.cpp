#include "workingEnvironmentSettings.h"
#include "ui_workingEnvironmentSettings.h"

WorkingEnvironmentSettings::WorkingEnvironmentSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkingEnvironmentSettings)
{
    ui->setupUi(this);
}

WorkingEnvironmentSettings::~WorkingEnvironmentSettings()
{
    delete ui;
}
