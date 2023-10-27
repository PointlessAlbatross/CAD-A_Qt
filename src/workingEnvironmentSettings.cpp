#include "../headers/workingEnvironmentSettings.h"


WorkingEnvironmentSettings::WorkingEnvironmentSettings(QWidget *parent) :
    QDialog(parent)
{

    setWindowTitle("Параметры среды");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *label1 = new QLabel("Глубина моря, м:");
    QLabel *label2 = new QLabel("Скорость ветра, м/c:");
    QLabel *label3 = new QLabel("Соленость воды, промилле:");
    QLabel *label4 = new QLabel("Температура воды, град:");

    depthSeaBox = new QDoubleSpinBox();
    depthSeaBox->setMinimum(0.0);
    depthSeaBox->setMaximum(100000.0);
    windBox = new QDoubleSpinBox();
    /*Нужны минимумы и максимумы для спинбоксов*/

    salinityBox = new QDoubleSpinBox();
    tempBox = new QDoubleSpinBox();

    QLabel *label5 = new QLabel("Коэфициент объемного рассеивания (как степень 10)");
    volumeDispBox = new QDoubleSpinBox();

    QLabel *label6 = new QLabel("Коэф. зеркального отражения поверх.:");
    QLabel *label7 = new QLabel("Коэф. зеркального отражения дном:");
    surfReflBox = new QDoubleSpinBox();
    botReflBox = new QDoubleSpinBox();

    QVBoxLayout *verticalLayout1 = new QVBoxLayout();
    QVBoxLayout *verticalLayout2 = new QVBoxLayout();
    QFormLayout *formLayout = new QFormLayout();

    QRadioButton *radioButton1 = new QRadioButton("Выровненный неоднородный грунт");
    QRadioButton *radioButton2 = new QRadioButton("Каменистое мелководье");
    QRadioButton *radioButton3 = new QRadioButton("Средний грунт");
    QRadioButton *radioButton4 = new QRadioButton("Ил, песок");

    verticalLayout1->addWidget(radioButton1);
    verticalLayout1->addWidget(radioButton2);
    verticalLayout1->addWidget(radioButton3);
    verticalLayout1->addWidget(radioButton4);

    QLabel *labelV1 = new QLabel("[1]");
    QLabel *labelV2 = new QLabel("[2]");
    QLabel *labelV3 = new QLabel("[3]");
    QLabel *labelV4 = new QLabel("[4]");
    verticalLayout2->addWidget(labelV1);
    verticalLayout2->addWidget(labelV2);
    verticalLayout2->addWidget(labelV3);
    verticalLayout2->addWidget(labelV4);

    formLayout->addRow(label1, depthSeaBox);
    formLayout->addRow(label2, windBox);
    formLayout->addRow(label3, salinityBox);
    formLayout->addRow(label4, tempBox);
    formLayout->addRow(label5, volumeDispBox);
    formLayout->addRow(label6, surfReflBox);
    formLayout->addRow(label7, botReflBox);

    QWidget *layoutContainer = new QWidget();
    QHBoxLayout *layoutContainerLayout = new QHBoxLayout(layoutContainer);
    layoutContainerLayout->addLayout(verticalLayout1);
    layoutContainerLayout->addLayout(verticalLayout2);

    formLayout->addRow(layoutContainer);

    mainLayout->addLayout(formLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton *cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

WorkingEnvironmentSettings::~WorkingEnvironmentSettings()
{

}

void WorkingEnvironmentSettings::on_pushButtonSave_clicked()
{
    emit signal_workingEnvironmentSettingsToMain (depthSeaBox->value(),
                                         windBox->value(),
                                         salinityBox->value(),
                                         tempBox->value(),
                                         volumeDispBox->value(),
                                         surfReflBox->value(),
                                         botReflBox->value());
    QWidget::close();
}

void WorkingEnvironmentSettings::slot_mainToWorkingEnvironmentSettings(double depthSea1, double windSpeed1,
                                                                       double salinity1, double tempWater1,
                                                                       double volumeDisp1,
                                                                       double surfReflCoef1, double botReflCoef1
                                                                       )
{
    depthSeaBox->setValue(depthSea1);
    windBox->setValue(windSpeed1);
    salinityBox->setValue(salinity1);
    tempBox->setValue(tempWater1);
    volumeDispBox->setValue(volumeDisp1);
    surfReflBox->setValue(surfReflCoef1);
    botReflBox->setValue(botReflCoef1);
}

void WorkingEnvironmentSettings::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

