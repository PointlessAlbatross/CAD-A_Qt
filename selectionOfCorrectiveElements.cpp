#include "selectionOfCorrectiveElements.h"
#include "ui_selectionOfCorrectiveElements.h"

selectionOfCorrectiveElements::selectionOfCorrectiveElements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectionOfCorrectiveElements)
{
    ui->setupUi(this);
    // выделение верхнего виджета
    ui->qBox->setFocus();
    ui->qBox->selectAll();
}

selectionOfCorrectiveElements::~selectionOfCorrectiveElements()
{
    delete ui;
}

void selectionOfCorrectiveElements::on_cancelButton_clicked()
{
    QWidget::close();
}

void selectionOfCorrectiveElements::slot_mainToSelectionOfCorrectiveElements(double qSlot, double q1Slot,
                                                                             double f, double delta_f,
                                                                             double C0, double C,
                                                                             double R, double L)
{
    ui->qBox->setValue(qSlot);
    ui->q1Box->setValue(q1Slot);
    ui->freqBox->setValue(f);
    ui->deltaFreqBox->setValue(delta_f);
    ui->capacityC0Box->setValue(C0);
    ui->capacityCBox->setValue(C);
    ui->resistanceRBox->setValue(R);
    ui->inductanceLBox->setValue(L);
}


void selectionOfCorrectiveElements::on_saveButton_clicked()
{
    emit signal_selectionOfCorrectiveElementsToMain_save(ui->qBox->value(), ui->q1Box->value(), ui->freqBox->value(),
                                                         ui->deltaFreqBox->value(), ui->capacityC0Box->value(), ui->capacityCBox->value(),
                                                         ui->resistanceRBox->value(), ui->inductanceLBox->value());
    QWidget::close();
}


void selectionOfCorrectiveElements::on_calculateButton_clicked()
{
    emit signal_selectionOfCorrectiveElementsToMain_calculate(ui->qBox->value(), ui->q1Box->value(), ui->freqBox->value(),
                                                         ui->deltaFreqBox->value(), ui->capacityC0Box->value(), ui->capacityCBox->value(),
                                                         ui->resistanceRBox->value(), ui->inductanceLBox->value());
    QWidget::close();
}

