#include "select_weight.h"
#include "ui_select_weight.h"

Select_weight::Select_weight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Select_weight)
{
    ui->setupUi(this);
}

Select_weight::~Select_weight()
{
    delete ui;
}

void Select_weight::slot_arrange_to_select_weigth(double weigth1, int i1, int j1, int n1)
{
    weigth = weigth1;
    i = i1;
    j = j1;
    n = n1;
    ui->doubleSpinBox->setValue(weigth);
    ui->label_num->setText(QString::number(i+1) + "." + QString::number(j+1) + "  (" + QString::number(n) + ")");
}

void Select_weight::on_pushButton_clicked()
{
    emit signal_select_weight_to_arrange(ui->doubleSpinBox->value(), i, j);
    QWidget::close();
}


void Select_weight::on_pushButton_2_clicked()
{
    QWidget::close();
}

