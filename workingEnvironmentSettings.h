#ifndef WORKINGENVIRONMENTSETTINGS_H
#define WORKINGENVIRONMENTSETTINGS_H

#include <QDialog>

namespace Ui {
class WorkingEnvironmentSettings;
}

class WorkingEnvironmentSettings : public QDialog
{
    Q_OBJECT

public:
    explicit WorkingEnvironmentSettings(QWidget *parent = nullptr);
    ~WorkingEnvironmentSettings();
signals:
    void signal_workingEnvironmentSettingsToMain(double depthSea1, double windSpeed1,
                                                 double salinity1, double tempWater1,
                                                 double volumeDisp1,
                                                 double surfReflCoef1, double botReflCoef1
                                                 );


public slots:
    void slot_mainToWorkingEnvironmentSettings(double depthSea1, double windSpeed1,
                                               double salinity1, double tempWater1,
                                               double volumeDisp1,
                                               double surfReflCoef1, double botReflCoef1
                                               );
private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::WorkingEnvironmentSettings *ui;
};

#endif // WORKINGENVIRONMENTSETTINGS_H
