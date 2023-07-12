#include "calcParam.h"
#include "ui_calcParam.h"

CalcParam::CalcParam(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Параметры расчетов");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* label = new QLabel("Метод интегрирования:", this);
    mainLayout->addWidget(label);

    comboBox = new QComboBox(this);
    comboBox->addItem("Метод прямоугольников");
    comboBox->addItem("Метод трапеций");
    comboBox->addItem("Метод Симпсона");
    comboBox->addItem("Метод Монте-Карло");
    mainLayout->addWidget(comboBox);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));

    QLabel* spinLabel = new QLabel("Число точек:", this);
    mainLayout->addWidget(spinLabel);

    spinBox = new QSpinBox(this);
    mainLayout->addWidget(spinBox);
    spinBox->setMaximum(10000000);

    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton* cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

CalcParam::~CalcParam()
{
}

void CalcParam::slot_mainToCalcParam(int opt, int dot)
{
    selectedOption = opt;
    comboBox->setCurrentIndex(opt - 1);
    spinBox->setValue(dot);
}

void CalcParam::on_pushButtonSave_clicked()
{
    emit signal_calcParamToMain(selectedOption, spinBox->value());
    QWidget::close();
}


void CalcParam::on_pushButtonCancel_clicked()
{
    QWidget::close();
}


void CalcParam::on_comboBox_currentIndexChanged(int index)
{
    selectedOption = index + 1;
}

