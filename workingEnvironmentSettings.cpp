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

void WorkingEnvironmentSettings::slot_mainToWorkingEnvironmentSettings()
{

}

void WorkingEnvironmentSettings::on_pushButtonSave_clicked()
{

}

