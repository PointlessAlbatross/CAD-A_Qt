#include "calcParam.h"
#include "ui_calcParam.h"

CalcParam::CalcParam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalcParam)
{
    ui->setupUi(this);
}

CalcParam::~CalcParam()
{
    delete ui;
}

void CalcParam::slot_mainToCalcParam(int opt, int dot)
{
    selectedOption = opt;
    ui->comboBox->setCurrentIndex(opt - 1);
    ui->spinBox->setValue(dot);
}

void CalcParam::on_pushButtonSave_clicked()
{
    emit signal_calcParamToMain(selectedOption, ui->spinBox->value());
    QWidget::close();
}


void CalcParam::on_pushButtonCancel_clicked()
{
    QWidget::close();
}


void CalcParam::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0) // метод прямоугольников
        selectedOption = 1;
    if(index == 1) // метод трапеций
        selectedOption = 2;
    if(index == 2) // метод Симпсона
        selectedOption = 3;
    if(index == 3) // метод Монте-Карло
        selectedOption = 4;

}

