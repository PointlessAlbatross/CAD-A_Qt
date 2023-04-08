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

void WorkingEnvironmentSettings::on_pushButtonSave_clicked()
{
    emit signal_workingEnvironmentSettingsToMain (ui->depthSeaBox->value(),
                                         ui->windBox->value(),
                                         ui->salinityBox->value(),
                                         ui->tempBox->value(),
                                         ui->volumeDispBox->value(),
                                         ui->surfReflBox->value(),
                                         ui->botReflBox->value());
    QWidget::close();
}

void WorkingEnvironmentSettings::slot_mainToWorkingEnvironmentSettings(double depthSea1, double windSpeed1,
                                                                       double salinity1, double tempWater1,
                                                                       double volumeDisp1,
                                                                       double surfReflCoef1, double botReflCoef1
                                                                       )
{
    ui->depthSeaBox->setValue(depthSea1);
    ui->windBox->setValue(windSpeed1);
    ui->salinityBox->setValue(salinity1);
    ui->tempBox->setValue(tempWater1);
    ui->volumeDispBox->setValue(volumeDisp1);
    ui->surfReflBox->setValue(surfReflCoef1);
    ui->botReflBox->setValue(botReflCoef1);
}

void WorkingEnvironmentSettings::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

