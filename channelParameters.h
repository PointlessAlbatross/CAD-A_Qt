#ifndef CHANNELPARAMETERS_H
#define CHANNELPARAMETERS_H

#include <QDialog>
#include <array>
#include <QTableWidgetItem>

namespace Ui {
class ChannelParameters;
}

class ChannelParameters : public QDialog
{
    Q_OBJECT

    std::array<std::array<bool, 16>, 30> Table;

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

private:
    Ui::ChannelParameters *ui;
};

#endif // CHANNELPARAMETERS_H
