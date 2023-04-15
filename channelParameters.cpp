#include "channelParameters.h"
#include "ui_channelParameters.h"

ChannelParameters::ChannelParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChannelParameters)
{
    ui->setupUi(this);
}

ChannelParameters::~ChannelParameters()
{
    delete ui;
}

void ChannelParameters::on_tableWidget_cellClicked(int row, int column)
{

}

