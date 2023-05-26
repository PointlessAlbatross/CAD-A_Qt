#include "echoSignal.h"
#include "ui_echoSignal.h"

EchoSignal::EchoSignal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EchoSignal)
{
    ui->setupUi(this);
}

EchoSignal::~EchoSignal()
{
    delete ui;
}

//emit signal_mainToEchoSignal(echoFreq1, echoFreq2, echoDist3, echoChannel, numDotEcho, 1, elevationAng, azimuthAng, relatSpeed, Rekv);
//emit signal_mainToEchoSignal(echoDist1, echoDist2, echoFreq3, echoChannel, numDotEcho, 2, elevationAng, azimuthAng, relatSpeed, Rekv);

void EchoSignal::slot_mainToEchoSignal(double param1, double param2, double param3, int channel, int numDot, int typeEchoSign, double elevation, double azimuth, double relative_speed, double R_ekv)
{

    ui->elevationBox->setValue(elevation);
    ui->azimuthBox->setValue(azimuth);
    ui->relativeSpedBox->setValue(relative_speed);
    ui->equivalentRadBox->setValue(R_ekv);
    ui->channelBox->setValue(channel);

    echo_type = typeEchoSign;
    ui->numDotBox->setValue(numDot);

    switch (typeEchoSign) {
    case 1: //частотная
        ui->param1Box->setValue(param1);
        ui->labelParam_1->setText("Нижняя частота расчета, Гц: ");

        ui->param2Box->setValue(param2);
        ui->labelParam_2->setText("Верхняя частота расчета, Гц: ");

        ui->param3Box->setValue(param3);
        ui->labelParam_3->setText("Расстояние в цикле излучения, м: ");



        break;
    case 2: //временная
        ui->param1Box->setValue(param1);
        ui->labelParam_1->setText("От растояния, м: ");

        ui->param2Box->setValue(param2);
        ui->labelParam_2->setText("До растояния, м: ");

        ui->param3Box->setValue(param3);
        ui->labelParam_3->setText("Частота расчета, Гц: ");

        break;

    default:
        break;
    }
}

void EchoSignal::on_pushButtonCompute_clicked()
{
    emit signal_echoSignalToMain(ui->param1Box->value(), ui->param2Box->value(), ui->param3Box->value(), ui->channelBox->value(),
                                 ui->numDotBox->value(), echo_type, 1,
                ui->elevationBox->value(), ui->azimuthBox->value(),  ui->relativeSpedBox->value(), ui->equivalentRadBox->value());
    QWidget::close();
}


void EchoSignal::on_pushButtonSave_clicked()
{

    emit signal_echoSignalToMain(ui->param1Box->value(), ui->param2Box->value(), ui->param3Box->value(), ui->channelBox->value(),
                                 ui->numDotBox->value(), echo_type, 0,
                ui->elevationBox->value(), ui->azimuthBox->value(),  ui->relativeSpedBox->value(), ui->equivalentRadBox->value());
    QWidget::close();
}


void EchoSignal::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

