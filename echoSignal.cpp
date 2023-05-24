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
