#ifndef CHARTSPARAMETERS_H
#define CHARTSPARAMETERS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>


class ChartsParameters : public QDialog
{
    Q_OBJECT

    QSpinBox *channelBox;

public:
    explicit ChartsParameters(QWidget *parent = nullptr);
    ~ChartsParameters();

public slots:
    void slot_mainToChartsParameters(int chartsChannel);

signals:
    void signal_chartsParametersToMain(int chartsChannel);

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();
};

#endif // CHARTSPARAMETERS_H
