#include "selectWeight.h"
#include "ui_selectWeight.h"

SelectWeight::SelectWeight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectWeight)
{
    ui->setupUi(this);
    ui->weightBox->setFocus();
    ui->weightBox->selectAll();
}

SelectWeight::~SelectWeight()
{
    delete ui;
}

void SelectWeight::slotArrangeToSelectWeigth(double weigth1, int i1, int j1, int n1)
{
    weigth = weigth1;
    i = i1;
    j = j1;
    n = n1;
    ui->weightBox->setValue(weigth);
    ui->label_num->setText(QString::number(i+1) + "." + QString::number(j+1) + "  (" + QString::number(n) + ")");
}

void SelectWeight::on_pushButtonSave_clicked()
{
    emit signalSelectWeightToArrange(ui->weightBox->value(), i, j);
    QWidget::close();
}


void SelectWeight::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

