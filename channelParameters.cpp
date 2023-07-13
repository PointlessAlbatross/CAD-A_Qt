#include "channelParameters.h"

ChannelParameters::ChannelParameters(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Определение параметров каналов");
    resize(500, 600);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel *label1 = new QLabel("Группы");
    label1->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label1);

    QHBoxLayout* buttonLayout1 = new QHBoxLayout();
    QLabel *label2 = new QLabel("К\n"
                                "а\n"
                                "н\n"
                                "а\n"
                                "л\n"
                                "ы");
    buttonLayout1->addWidget(label2);

    tableWidget = new QTableWidget();
    tableWidget->setRowCount(30);
    tableWidget->setColumnCount(16);
    buttonLayout1->addWidget(tableWidget);
    connect(tableWidget, &QTableWidget::cellClicked, this, &ChannelParameters::on_tableWidget_cellClicked);

    mainLayout->addLayout(buttonLayout1);

    // Гибкий разделитель для центрирования tableWidget
    QSpacerItem* spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred);
    mainLayout->addItem(spacer);


    QHBoxLayout* buttonLayout2 = new QHBoxLayout();

    QPushButton* saveButton = new QPushButton("Сохранить", this);
    buttonLayout2->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton* clearButton = new QPushButton("Очистить", this);
    buttonLayout2->addWidget(clearButton);
    connect(clearButton, SIGNAL(clicked()), this, SLOT(on_pushButtonClear_clicked()));

    QPushButton* cancelButton = new QPushButton("Отменить", this);
    buttonLayout2->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout2);

    setLayout(mainLayout);


    // Установка режима изменения размера столбцов
        for (int column = 0; column < tableWidget->columnCount(); ++column) {
            tableWidget->horizontalHeader()->setSectionResizeMode(column, QHeaderView::ResizeToContents);
        }
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //запрет на редактирование ячеек
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //запрет на выделение нескольких ячеек
}

ChannelParameters::~ChannelParameters()
{

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
                tableWidget->setItem(row, col, item);
            }
        }
    }

}

void ChannelParameters::on_tableWidget_cellClicked(int row, int col)
{
    if (Table[row][col] == true)
    {
        tableWidget->setItem(row, col, nullptr);
        Table[row][col] = false;
    }
    else
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString("V"));
        item->setTextAlignment(Qt::AlignCenter);
        tableWidget->setItem(row, col, item);
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
                tableWidget->setItem(row, col, nullptr);
            }
        }
    }
}

