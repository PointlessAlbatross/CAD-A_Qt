#ifndef CHARTSPARAMETERS_H
#define CHARTSPARAMETERS_H

#include <QDialog>

namespace Ui {
class ChartsParameters;
}

class ChartsParameters : public QDialog
{
    Q_OBJECT

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



private:
    Ui::ChartsParameters *ui;
};

#endif // CHARTSPARAMETERS_H
