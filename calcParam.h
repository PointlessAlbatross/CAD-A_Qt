#ifndef CALCPARAM_H
#define CALCPARAM_H

#include <QDialog>
#include <QApplication>
#include <QWidget>

#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class CalcParam : public QDialog
{
    Q_OBJECT

    int selectedOption;

    QComboBox* comboBox;
    QSpinBox* spinBox;


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

};

#endif // CALCPARAM_H
