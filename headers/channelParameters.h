#ifndef CHANNELPARAMETERS_H
#define CHANNELPARAMETERS_H

#include <QDialog>
#include <array>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>

namespace Ui {
class ChannelParameters;
}

class ChannelParameters : public QDialog
{
    Q_OBJECT

    std::array<std::array<bool, 16>, 30> Table;

    QTableWidget *tableWidget;

public:
    explicit ChannelParameters(QWidget *parent = nullptr);
    ~ChannelParameters();
public slots:
    void slot_mainToChannelParameters(std::array<std::array<bool, 16>, 30> Table);

signals:
    void signal_channelParametersToMain(std::array<std::array<bool, 16>, 30> Table);

private slots:

    void on_tableWidget_cellClicked(int row, int column);

    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonClear_clicked();
};

#endif // CHANNELPARAMETERS_H
