#include "reverberationParameters.h"
#include "ui_reverberationParameters.h"

ReverberationParameters::ReverberationParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReverberationParameters)
{
    ui->setupUi(this);
}

ReverberationParameters::~ReverberationParameters()
{
    delete ui;
}


//Мощности
void ReverberationParameters::slot_mainToReverberationParameters1(double param1, double param2, double param3, int channel1, int numDot1,
                                                                  std::array<bool, 4> ReverbChecks1, int typeReverb)
{
    ReverbChecks = ReverbChecks1;
    ui->surfCheckBox->setChecked(ReverbChecks1[0]);
    ui->surroundCheckBox->setChecked(ReverbChecks1[1]);
    ui->botCheckBox->setChecked(ReverbChecks1[2]);
    ui->sumCheckBox->setChecked(ReverbChecks1[3]);
    switch (typeReverb) {
    case 1: //частотная
        reverbFreq1 = param1;
        ui->param1Box->setValue(param1);
        ui->labelParam_1->setText("Нижняя частота расчета, Гц: ");

        reverbFreq2 = param2;
        ui->param2Box->setValue(param2);
        ui->labelParam_2->setText("Верхняя частота расчета, Гц: ");

        reverbDist3 = param3;
        ui->param3Box->setValue(param3);
        ui->labelParam_3->setText("Расстояние в цикле излучения, м: ");

        reverbChannel1 = channel1;
        ui->channel1Box->setValue(channel1);
        ui->lablelChannel_1->setText("Номер канала для расчета: ");

        ui->channel2Box->hide();
        ui->lablelChannel_2->hide();
        break;
    case 2: //временная
        reverbFreq3 = param1;
        ui->param1Box->setValue(param1);
        ui->labelParam_1->setText("Частота расчета, Гц: ");

        reverbDist1 = param2;
        ui->param2Box->setValue(param2);
        ui->labelParam_2->setText("От растояния, м: ");

        reverbDist2 = param3;
        ui->param3Box->setValue(param3);
        ui->labelParam_3->setText("До растояния, м: ");

        reverbChannel1 = channel1;
        ui->channel1Box->setValue(channel1);
        ui->lablelChannel_1->setText("Номер канала для расчета: ");

        ui->channel2Box->hide();
        ui->lablelChannel_2->hide();


        break;

    default:
        break;
    }
    REVERB_TYPE = typeReverb;
    numDot = numDot1;
    ui->numDotBox->setValue(numDot1);
}

//Корреляция
void ReverberationParameters::slot_mainToReverberationParameters2(double param1, double param2, double param3, int channel1, int channel2,
                                                                  std::array<bool, 4> ReverbChecks1, int typeReverb)
{

}

void ReverberationParameters::on_pushButtonSave_clicked()
{
    emit signal_reverberationParametersToMain1(ui->param1Box->value(), ui->param2Box->value(), ui->param3Box->value(),
                                               ui->channel1Box->value(), ui->numDotBox->value(),
                                               ReverbChecks, REVERB_TYPE, 0);

    QWidget::close();
}


void ReverberationParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}


void ReverberationParameters::on_pushButtonCompute_clicked()
{
    emit signal_reverberationParametersToMain1(ui->param1Box->value(), ui->param2Box->value(), ui->param3Box->value(),
                                               ui->channel1Box->value(), ui->numDotBox->value(),
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

