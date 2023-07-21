#include "operatingSystemParameters.h"

OperatingSystemParameters::OperatingSystemParameters(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Рабочие параметры системы");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *VLayout1 = new QVBoxLayout();
    QLabel *label1 = new QLabel("Частота излучения   f,  Гц  :");
    QLabel *label2 = new QLabel("Частота приема   f,  Гц  :");
    VLayout1->addWidget(label1);
    VLayout1->addWidget(label2);

    QVBoxLayout *VLayout2 = new QVBoxLayout();
    radiationFrequencyBox = new QSpinBox();
    radiationFrequencyBox->setMinimum(100);
    radiationFrequencyBox->setMaximum(1000000);
    VLayout2->addWidget(radiationFrequencyBox);

    receivingFrequencyBox = new QSpinBox();
    receivingFrequencyBox->setMinimum(100);
    receivingFrequencyBox->setMaximum(1000000);
    VLayout2->addWidget(receivingFrequencyBox);

    layout1->addLayout(VLayout1);
    layout1->addLayout(VLayout2);
    mainLayout->addLayout(layout1);

    QVBoxLayout *VLayout3 = new QVBoxLayout();
    rectRadioButton = new QRadioButton("Прямоугольный импульс");
    trapezRadioButton = new QRadioButton("Трапециидальный импульс");
    unitRadioButton = new QRadioButton("Единичный спектр");

    connect(rectRadioButton, &QRadioButton::clicked, this, &OperatingSystemParameters::on_rectRadioButton_clicked);
    connect(trapezRadioButton, &QRadioButton::clicked, this, &OperatingSystemParameters::on_trapezRadioButton_clicked);
    connect(unitRadioButton, &QRadioButton::clicked, this, &OperatingSystemParameters::on_unitRadioButton_clicked);

    VLayout3->addWidget(rectRadioButton);
    VLayout3->addWidget(trapezRadioButton);
    VLayout3->addWidget(unitRadioButton);

    mainLayout->addLayout(VLayout3);

    QHBoxLayout *layout2 = new QHBoxLayout();
    QVBoxLayout *VLayout4 = new QVBoxLayout();
    QLabel *label3 = new QLabel("Длительность посылки,  мс  :");
    label4 = new QLabel("Длительность фронта,  мс  :");
    QLabel *label5 = new QLabel("Излучаемое давление, Па  :");

    VLayout4->addWidget(label3);
    VLayout4->addWidget(label4);
    VLayout4->addWidget(label5);

    QVBoxLayout *VLayout5 = new QVBoxLayout();
    pulseDurationBox = new QSpinBox();
    pulseDurationBox->setMinimum(1);
    pulseDurationBox->setMaximum(1000);
    VLayout5->addWidget(pulseDurationBox);

    riseTimeBox = new QSpinBox();
    riseTimeBox->setMinimum(1);
    riseTimeBox->setMaximum(1000);
    VLayout5->addWidget(riseTimeBox);

    pressureBox = new QSpinBox();
    pressureBox->setMinimum(1);
    pressureBox->setMaximum(1000000);
    VLayout5->addWidget(pressureBox);


    layout2->addLayout(VLayout4);
    layout2->addLayout(VLayout5);
    mainLayout->addLayout(layout2);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton *cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);




    radiationFrequencyBox->setFocus();
    radiationFrequencyBox->selectAll();
}

OperatingSystemParameters::~OperatingSystemParameters()
{

}

void OperatingSystemParameters::on_pushButtonSave_clicked()
{
    emit signalOperatingSystemParametersToMain (pulseDurationBox->value(), riseTime, pressureBox->value(),
                                                     radiationFrequencyBox->value(), receivingFrequencyBox->value(), impulseType);
    QWidget::close();
}


void OperatingSystemParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

void OperatingSystemParameters::slotMainToOperatingSystemParameters(int pulseDuration1, int riseTime1, int pressure1, int radiation_freq1, int receiving_freq1, int impulseType1)
{
    impulseType = impulseType1;
    switch (impulseType1) {
    case 1:
        rectRadioButton->setChecked(true);
        riseTimeBox->hide();
        label4->hide();
        break;
    case 2:
        trapezRadioButton->setChecked(true);
        break;
    case 3:
        unitRadioButton->setChecked(true);
        riseTimeBox->hide();
        label4->hide();
        //label3
        break;
    default:
        break;
    }
    pulseDuration = pulseDuration1;
    riseTime = riseTime1;
    pressure = pressure1;
    receivingFreq = receiving_freq1;
    radiationFreq = radiation_freq1;
    pulseDurationBox->setValue(pulseDuration);
    riseTimeBox->setValue(riseTime);
    pressureBox->setValue(pressure);
    radiationFrequencyBox->setValue(radiationFreq);
    receivingFrequencyBox->setValue(receivingFreq);
}


void OperatingSystemParameters::on_rectRadioButton_clicked(bool checked)
{
    if (checked)
    {
        impulseType = 1;
        riseTimeBox->hide();
        label4->hide();
    }
}


void OperatingSystemParameters::on_trapezRadioButton_clicked(bool checked)
{
    if (checked)
    {
        impulseType = 2;
        riseTimeBox->show();
        label4->show();
    }
}

void OperatingSystemParameters::on_unitRadioButton_clicked(bool checked)
{
    if (checked)
    {
        impulseType = 3;
        riseTimeBox->hide();
        label4->hide();
    }
}
