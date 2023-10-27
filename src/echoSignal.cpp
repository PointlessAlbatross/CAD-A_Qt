#include "../headers/echoSignal.h"

EchoSignal::EchoSignal(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Параметры эхосигнала");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *VLayout1 = new QVBoxLayout();
    QLabel *labelParam_4 = new QLabel("Угол места цели, град");
    QLabel *labelParam_5 = new QLabel("Азимут цели, град");
    QLabel *labelParam_6 = new QLabel("Относительная скорость, м/с");
    QLabel *labelParam_7 = new QLabel("Эквивалентный радиус цели, м");
    VLayout1->addWidget(labelParam_4);
    VLayout1->addWidget(labelParam_5);
    VLayout1->addWidget(labelParam_6);
    VLayout1->addWidget(labelParam_7);

    QVBoxLayout *VLayout2 = new QVBoxLayout();
    elevationBox = new QDoubleSpinBox();
    elevationBox->setMinimum(0);
    elevationBox->setMaximum(180);
    VLayout2->addWidget(elevationBox);

    azimuthBox = new QDoubleSpinBox();
    azimuthBox->setMinimum(-90);
    azimuthBox->setMaximum(90);
    VLayout2->addWidget(azimuthBox);


    relativeSpedBox = new QDoubleSpinBox();
    relativeSpedBox->setMinimum(0);
    relativeSpedBox->setMaximum(60000);
    VLayout2->addWidget(relativeSpedBox);

    equivalentRadBox = new QDoubleSpinBox();
    equivalentRadBox->setMinimum(0);
    equivalentRadBox->setMaximum(100);
    VLayout2->addWidget(equivalentRadBox);

    layout1->addLayout(VLayout1);
    layout1->addLayout(VLayout2);
    mainLayout->addLayout(layout1);

    QHBoxLayout *layout2 = new QHBoxLayout();
    QVBoxLayout *VLayout3 = new QVBoxLayout();
    labelParam_1 = new QLabel("labelParam_1");
    labelParam_2 = new QLabel("labelParam_2");
    labelParam_3 = new QLabel("labelParam_3");

    VLayout3->addWidget(labelParam_1);
    VLayout3->addWidget(labelParam_2);
    VLayout3->addWidget(labelParam_3);

    QVBoxLayout *VLayout4 = new QVBoxLayout();
    param1Box = new QDoubleSpinBox();
    param1Box->setMinimum(0);
    param1Box->setMaximum(60000);
    VLayout4->addWidget(param1Box);

    param2Box = new QDoubleSpinBox();
    param2Box->setMinimum(0);
    param2Box->setMaximum(60000);
    VLayout4->addWidget(param2Box);


    param3Box = new QDoubleSpinBox();
    param3Box->setMinimum(0);
    param3Box->setMaximum(60000);
    VLayout4->addWidget(param3Box);

    layout2->addLayout(VLayout3);
    layout2->addLayout(VLayout4);
    mainLayout->addLayout(layout2);

    QHBoxLayout *layout3 = new QHBoxLayout();
    QVBoxLayout *VLayout5 = new QVBoxLayout();
    QLabel *labelParam_8 = new QLabel("Количество точек расчета");
    QLabel *labelParam_9 = new QLabel("Номер канала");

    VLayout5->addWidget(labelParam_8);
    VLayout5->addWidget(labelParam_9);

    QVBoxLayout *VLayout6 = new QVBoxLayout();
    numDotBox = new QSpinBox();
    numDotBox->setMinimum(0);
    numDotBox->setMaximum(180);
    VLayout6->addWidget(numDotBox);

    channelBox = new QSpinBox();
    channelBox->setMinimum(-90);
    channelBox->setMaximum(90);
    VLayout6->addWidget(channelBox);


    layout3->addLayout(VLayout5);
    layout3->addLayout(VLayout6);
    mainLayout->addLayout(layout3);

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *computeButton = new QPushButton("Расчитать", this);
    buttonLayout->addWidget(computeButton);
    connect(computeButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCompute_clicked()));

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton *cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

EchoSignal::~EchoSignal()
{

}

//emit signal_mainToEchoSignal(echoFreq1, echoFreq2, echoDist3, echoChannel, numDotEcho, 1, elevationAng, azimuthAng, relatSpeed, Rekv);
//emit signal_mainToEchoSignal(echoDist1, echoDist2, echoFreq3, echoChannel, numDotEcho, 2, elevationAng, azimuthAng, relatSpeed, Rekv);

void EchoSignal::slot_mainToEchoSignal(double param1, double param2, double param3, int channel, int numDot, int typeEchoSign, double elevation, double azimuth, double relative_speed, double R_ekv)
{
    elevationBox->setValue(elevation);
    azimuthBox->setValue(azimuth);
    relativeSpedBox->setValue(relative_speed);
    equivalentRadBox->setValue(R_ekv);
    channelBox->setValue(channel);

    echo_type = typeEchoSign;
    numDotBox->setValue(numDot);
    switch (typeEchoSign) {
    case 1: //частотная
        param1Box->setValue(param1);
        labelParam_1->setText("Нижняя частота расчета, Гц: ");
        param2Box->setValue(param2);
        labelParam_2->setText("Верхняя частота расчета, Гц: ");

        param3Box->setValue(param3);
        labelParam_3->setText("Расстояние в цикле излучения, м: ");



        break;
    case 2: //временная
        param1Box->setValue(param1);
        labelParam_1->setText("От растояния, м: ");

        param2Box->setValue(param2);
        labelParam_2->setText("До растояния, м: ");

        param3Box->setValue(param3);
        labelParam_3->setText("Частота расчета, Гц: ");

        break;

    default:
        break;
    }
}

void EchoSignal::on_pushButtonCompute_clicked()
{
    emit signal_echoSignalToMain(param1Box->value(), param2Box->value(), param3Box->value(), channelBox->value(),
                                 numDotBox->value(), echo_type, 1,
                elevationBox->value(), azimuthBox->value(),  relativeSpedBox->value(), equivalentRadBox->value());
    QWidget::close();
}


void EchoSignal::on_pushButtonSave_clicked()
{

    emit signal_echoSignalToMain(param1Box->value(), param2Box->value(), param3Box->value(), channelBox->value(),
                                 numDotBox->value(), echo_type, 0,
                elevationBox->value(), azimuthBox->value(),  relativeSpedBox->value(), equivalentRadBox->value());
    QWidget::close();
}


void EchoSignal::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

