#include "../headers/reverberationParameters.h"

ReverberationParameters::ReverberationParameters(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Параметры реверберации");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *VLayout1 = new QVBoxLayout();
    label1 = new QLabel("labelParam1");
    label2 = new QLabel("labelParam2");
    label3 = new QLabel("labelParam3");
    VLayout1->addWidget(label1);
    VLayout1->addWidget(label2);
    VLayout1->addWidget(label3);

    QVBoxLayout *VLayout2 = new QVBoxLayout();
    param1Box = new QDoubleSpinBox();
    param1Box->setMinimum(0);
    param1Box->setMaximum(60000);
    VLayout2->addWidget(param1Box);

    param2Box = new QDoubleSpinBox();
    param2Box->setMinimum(0);
    param2Box->setMaximum(60000);
    VLayout2->addWidget(param2Box);


    param3Box = new QDoubleSpinBox();
    param3Box->setMinimum(0);
    param3Box->setMaximum(60000);
    VLayout2->addWidget(param3Box);

    layout1->addLayout(VLayout1);
    layout1->addLayout(VLayout2);
    mainLayout->addLayout(layout1);

    /***/

    QHBoxLayout *layout2 = new QHBoxLayout();
    QVBoxLayout *VLayout3 = new QVBoxLayout();
    label4 = new QLabel("labelChannel1");
    label5 = new QLabel("labelChannel2");
    VLayout3->addWidget(label4);
    VLayout3->addWidget(label5);

    QVBoxLayout *VLayout4 = new QVBoxLayout();
    channel1Box = new QSpinBox();
    channel1Box->setMinimum(1);
    channel1Box->setMaximum(30);
    VLayout4->addWidget(channel1Box);

    channel2Box = new QSpinBox();
    channel2Box->setMinimum(1);
    channel2Box->setMaximum(30);
    VLayout4->addWidget(channel2Box);

    layout2->addLayout(VLayout3);
    layout2->addLayout(VLayout4);
    mainLayout->addLayout(layout2);

    /***/

    QVBoxLayout *checkBoxLayout = new QVBoxLayout;
    surfCheckBox = new QCheckBox("Певерхностная реверберация");
    surroundCheckBox = new QCheckBox("Объемная реверберация");
    botCheckBox = new QCheckBox("Донная реверберация");
    sumCheckBox = new QCheckBox("Суммарная реверберация");

    checkBoxLayout->addWidget(surfCheckBox);
    checkBoxLayout->addWidget(surroundCheckBox);
    checkBoxLayout->addWidget(botCheckBox);
    checkBoxLayout->addWidget(sumCheckBox);
    mainLayout->addLayout(checkBoxLayout);

    /***/
    QHBoxLayout *layout3 = new QHBoxLayout();
    QLabel *label6 = new QLabel("Количество точек расчета");
    numDotBox = new QSpinBox();
    numDotBox->setMinimum(0);
    numDotBox->setMaximum(1000000);
    layout3->addWidget(label6);
    layout3->addWidget(numDotBox);
    mainLayout->addLayout(layout3);

    /***/

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

ReverberationParameters::~ReverberationParameters()
{

}


//Мощности
void ReverberationParameters::slot_mainToReverberationParameters1(double param1, double param2, double param3, int channel1, int numDot1,
                                                                  std::array<bool, 4> ReverbChecks1, int typeReverb)
{
    ReverbChecks = ReverbChecks1;
    surfCheckBox->setChecked(ReverbChecks1[0]);
    surroundCheckBox->setChecked(ReverbChecks1[1]);
    botCheckBox->setChecked(ReverbChecks1[2]);
    sumCheckBox->setChecked(ReverbChecks1[3]);
    switch (typeReverb) {
    case 1: //частотная
        reverbFreq1 = param1;
        param1Box->setValue(param1);
        label1->setText("Нижняя частота расчета, Гц: ");

        reverbFreq2 = param2;
        param2Box->setValue(param2);
        label2->setText("Верхняя частота расчета, Гц: ");

        reverbDist3 = param3;
        param3Box->setValue(param3);
        label3->setText("Расстояние в цикле излучения, м: ");

        reverbChannel1 = channel1;
        channel1Box->setValue(channel1);
        label4->setText("Номер канала для расчета: ");

        channel2Box->hide();
        label5->hide();
        break;
    case 2: //временная
        reverbFreq3 = param1;
        param1Box->setValue(param1);
        label1->setText("Частота расчета, Гц: ");

        reverbDist1 = param2;
        param2Box->setValue(param2);
        label2->setText("От растояния, м: ");

        reverbDist2 = param3;
        param3Box->setValue(param3);
        label3->setText("До растояния, м: ");

        reverbChannel1 = channel1;
        channel1Box->setValue(channel1);
        label4->setText("Номер канала для расчета: ");

        channel2Box->hide();
        label5->hide();


        break;

    default:
        break;
    }
    REVERB_TYPE = typeReverb;
    numDot = numDot1;
    numDotBox->setValue(numDot1);
}

//Корреляция
void ReverberationParameters::slot_mainToReverberationParameters2(double param1, double param2, double param3, int channel1, int channel2,
                                                                  std::array<bool, 4> ReverbChecks1, int typeReverb)
{

}

void ReverberationParameters::on_pushButtonSave_clicked()
{
    emit signal_reverberationParametersToMain1(param1Box->value(), param2Box->value(), param3Box->value(),
                                               channel1Box->value(), numDotBox->value(),
                                               ReverbChecks, REVERB_TYPE, 0);

    QWidget::close();
}


void ReverberationParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}


void ReverberationParameters::on_pushButtonCompute_clicked()
{
    emit signal_reverberationParametersToMain1(param1Box->value(), param2Box->value(), param3Box->value(),
                                               channel1Box->value(), numDotBox->value(),
                                               ReverbChecks, REVERB_TYPE, 1);
    QWidget::close();
}


void ReverberationParameters::on_surfCheckBox_stateChanged(int arg1)
{
    ReverbChecks[0] = arg1;
}


void ReverberationParameters::on_surroundCheckBox_stateChanged(int arg1)
{
    ReverbChecks[1] = arg1;
}


void ReverberationParameters::on_botCheckBox_stateChanged(int arg1)
{
    ReverbChecks[2] = arg1;
}


void ReverberationParameters::on_sumCheckBox_stateChanged(int arg1)
{
    ReverbChecks[3] = arg1;
}

