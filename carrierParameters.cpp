#include "carrierParameters.h"
#include <QDebug>
CarrierParameters::CarrierParameters(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Параметры графиков");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *VLayout1 = new QVBoxLayout();
    QLabel *label1 = new QLabel("Глубина хода, м");
    QLabel *label2 = new QLabel("Скорость хода, м");
    QLabel *label3 = new QLabel("Растояние между источником шума и центом антены, м");
    QLabel *label4 = new QLabel("шум движителя, м");
    VLayout1->addWidget(label1);
    VLayout1->addWidget(label2);
    VLayout1->addWidget(label3);
    VLayout1->addWidget(label4);

    QVBoxLayout *VLayout2 = new QVBoxLayout();
    HSubBox = new QDoubleSpinBox();
    HSubBox->setMinimum(5);
    HSubBox->setMaximum(1000);
    VLayout2->addWidget(HSubBox);

    LSubBox = new QDoubleSpinBox();
    LSubBox->setMinimum(0.5);
    LSubBox->setMaximum(100);
    VLayout2->addWidget(LSubBox);


    speedBox = new QDoubleSpinBox();
    speedBox->setMinimum(1);
    speedBox->setMaximum(30);
    VLayout2->addWidget(speedBox);

    noiseEngBox = new QDoubleSpinBox();
    noiseEngBox->setMinimum(0);
    noiseEngBox->setMaximum(30);
    VLayout2->addWidget(noiseEngBox);
    layout1->addLayout(VLayout1);
    layout1->addLayout(VLayout2);

    mainLayout->addLayout(layout1);
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton *cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout);
}

CarrierParameters::~CarrierParameters()
{

}

void CarrierParameters::slot_mainToCarrierParameters(double HSub1, double LSub1, double speed1, double noise1)
{
    HSubBox->setValue(HSub1);
    LSubBox->setValue(LSub1);
    speedBox->setValue(speed1);
    noiseEngBox->setValue(noise1);
}


void CarrierParameters::on_pushButtonSave_clicked()
{
    emit signal_carrierParametersToMain (HSubBox->value(),
                                         LSubBox->value(),
                                         speedBox->value(),
                                         noiseEngBox->value());
    QWidget::close();
}

void CarrierParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}
