#include "selectionOfCorrectiveElements.h"
#include "ui_selectionOfCorrectiveElements.h"

selectionOfCorrectiveElements::selectionOfCorrectiveElements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectionOfCorrectiveElements)
{
    ui->setupUi(this);
}

selectionOfCorrectiveElements::~selectionOfCorrectiveElements()
{
    delete ui;
}
