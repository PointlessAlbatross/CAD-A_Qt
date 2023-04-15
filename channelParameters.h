#ifndef CHANNELPARAMETERS_H
#define CHANNELPARAMETERS_H

#include <QDialog>
#include <array>

namespace Ui {
class ChannelParameters;
}

class ChannelParameters : public QDialog
{
    Q_OBJECT

    std::array<std::array<double, 16>, 30> Table;


public:
    explicit ChannelParameters(QWidget *parent = nullptr);
    ~ChannelParameters();

private slots:

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::ChannelParameters *ui;
};

#endif // CHANNELPARAMETERS_H
