#ifndef WORKINGENVIRONMENTSETTINGS_H
#define WORKINGENVIRONMENTSETTINGS_H

#include <QDialog>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QRadioButton>


class WorkingEnvironmentSettings : public QDialog
{
    Q_OBJECT

    QDoubleSpinBox *depthSeaBox;
    QDoubleSpinBox *windBox;
    QDoubleSpinBox *salinityBox;
    QDoubleSpinBox *tempBox;
    QDoubleSpinBox *volumeDispBox;
    QDoubleSpinBox *surfReflBox;
    QDoubleSpinBox *botReflBox;

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
};

#endif // WORKINGENVIRONMENTSETTINGS_H
