#include "channelParameters.h"
#include "ui_channelParameters.h"

ChannelParameters::ChannelParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChannelParameters)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //запрет на редактирование ячеек
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //запрет на выделение нескольких ячеек
}

ChannelParameters::~ChannelParameters()
{
    delete ui;
}

void ChannelParameters::slot_mainToChannelParameters(std::array<std::array<bool, 16>, 30> TableChannel)
{
    for (unsigned int i = 0; i < TableChannel.size(); i++)
       {
           for (unsigned int j = 0; j < TableChannel[i].size(); j++)
               Table[i][j] = TableChannel[i][j];
       }

    for(unsigned int row = 0; row<TableChannel.size(); row++)
    {
        for(unsigned int col = 0; col<TableChannel[row].size(); col++)
        {
            if (TableChannel[row][col] == true)
            {
                QTableWidgetItem *item = new QTableWidgetItem(QString("V"));
                item->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(row, col, item);
            }
        }
    }

}

void ChannelParameters::on_tableWidget_cellClicked(int row, int col)
{
    if (Table[row][col] == true)
    {
        ui->tableWidget->setItem(row, col, nullptr);
        Table[row][col] = false;
    }
    else
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString("V"));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, col, item);
        Table[row][col] = true;
    }
}


void ChannelParameters::on_pushButtonSave_clicked()
{
    emit signal_channelParametersToMain (Table);
    QWidget::close();
}


void ChannelParameters::on_pushButtonCancel_clicked()
{
    QWidget::close();
}


void ChannelParameters::on_pushButtonClear_clicked()
{
    for(unsigned int row = 0; row<Table.size(); row++)
    {
        for(unsigned int col = 0; col<Table[row].size(); col++)
        {
            if (Table[row][col] == true)
            {
                Table[row][col] = false;
                ui->tableWidget->setItem(row, col, nullptr);
            }
        }
    }
}

