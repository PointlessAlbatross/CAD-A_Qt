#ifndef CALCPARAM_H
#define CALCPARAM_H

#include <QDialog>
#include <QApplication>
#include <QComboBox>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class CalcParam;
}

class CalcParam : public QDialog
{
    Q_OBJECT

    int selectedOption;

public:
    explicit CalcParam(QWidget *parent = nullptr);
    ~CalcParam();
signals:
    void signal_calcParamToMain(int opt, int dot);
public slots:
    void slot_mainToCalcParam(int opt, int dot);

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::CalcParam *ui;
};

#endif // CALCPARAM_H
