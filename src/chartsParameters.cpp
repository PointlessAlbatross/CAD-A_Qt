#include "../headers/chartsParameters.h"

ChartsParameters::ChartsParameters(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Параметры графиков");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *layout1 = new QHBoxLayout();
    QLabel *label = new QLabel("Номер канала для ДН");
    layout1->addWidget(label);
    channelBox = new QSpinBox();
    channelBox->setMinimum(1);
    channelBox->setMaximum(30);
    layout1->addWidget(channelBox);
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

ChartsParameters::~ChartsParameters()
{

}

void ChartsParameters::slot_mainToChartsParameters(int chartsChannel)
{
    channelBox->setValue(chartsChannel);
}

void ChartsParameters::on_pushButtonSave_clicked()
{
    emit signal_chartsParametersToMain(channelBox->value());
    QWidget::close();
}


void ChartsParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

