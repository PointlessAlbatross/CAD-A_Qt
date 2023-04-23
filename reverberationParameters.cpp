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
void ReverberationParameters::slot_mainToReverberationParameters1(double param1, double param2, double param3, int channel1, int numDot1, int typeReverb)
{
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
void ReverberationParameters::slot_mainToReverberationParameters2(double param1, double param2, double param3, int channel1, int channel2, int typeReverb)
{

}

void ReverberationParameters::on_pushButtonSave_clicked()
{
    switch (REVERB_TYPE) {
    case 1: //частотная

        break;
    case 2: //временная

        break;

    default:
        break;
    }
    QWidget::close();
}


void ReverberationParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}


void ReverberationParameters::on_pushButtonCompute_clicked()
{
    switch (REVERB_TYPE) {
    case 1: //частотная

        break;
    case 2: //временная

        break;

    default:
        break;
    }
    QWidget::close();
}

