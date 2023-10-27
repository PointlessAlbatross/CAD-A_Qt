#include "../headers/selectionOfCorrectiveElements.h"

SelectionOfCorrectiveElements::SelectionOfCorrectiveElements(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Параметры реверберации");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *VLayout1 = new QVBoxLayout();
    QLabel *label1 = new QLabel("Xn / |Z0| (q)");
    QLabel *label2 = new QLabel("Rn / |Z0| (q1)");
    VLayout1->addWidget(label1);
    VLayout1->addWidget(label2);

    QVBoxLayout *VLayout2 = new QVBoxLayout();
    qBox = new QDoubleSpinBox();
    qBox->setMinimum(0);
    qBox->setMaximum(60000);
    VLayout2->addWidget(qBox);

    q1Box = new QDoubleSpinBox();
    q1Box->setMinimum(0);
    q1Box->setMaximum(60000);
    VLayout2->addWidget(q1Box);

    layout1->addLayout(VLayout1);
    layout1->addLayout(VLayout2);
    mainLayout->addLayout(layout1);

    /***/

    QHBoxLayout *layout2 = new QHBoxLayout();
    QVBoxLayout *VLayout3 = new QVBoxLayout();
    QLabel *label3 = new QLabel("Центральная частота f, Гц");
    QLabel *label4 = new QLabel("Полоса Δf, Гц");
    VLayout3->addWidget(label3);
    VLayout3->addWidget(label4);

    QVBoxLayout *VLayout4 = new QVBoxLayout();
    freqBox = new QDoubleSpinBox();
    freqBox->setMinimum(0);
    freqBox->setMaximum(1000000);
    VLayout4->addWidget(freqBox);

    deltaFreqBox = new QDoubleSpinBox();
    deltaFreqBox->setMinimum(0);
    deltaFreqBox->setMaximum(1000000);
    VLayout4->addWidget(deltaFreqBox);

    layout2->addLayout(VLayout3);
    layout2->addLayout(VLayout4);
    mainLayout->addLayout(layout2);

    /***/

    QHBoxLayout *layout3 = new QHBoxLayout();
    QVBoxLayout *VLayout5 = new QVBoxLayout();
    QLabel *label5 = new QLabel("Ёмкость C0, нФ");
    QLabel *label6 = new QLabel("Ёмкость C, нФ");
    QLabel *label7 = new QLabel("Сопротивление R, Ом");
    QLabel *label8 = new QLabel("Индуктивность L, мкГн");
    VLayout3->addWidget(label5);
    VLayout3->addWidget(label6);
    VLayout3->addWidget(label7);
    VLayout3->addWidget(label8);

    QVBoxLayout *VLayout6 = new QVBoxLayout();
    capacityC0Box = new QDoubleSpinBox();
    capacityC0Box->setMinimum(0);
    capacityC0Box->setMaximum(1000000);
    VLayout4->addWidget(capacityC0Box);

    capacityCBox = new QDoubleSpinBox();
    capacityCBox->setMinimum(0);
    capacityCBox->setMaximum(1000000);
    VLayout4->addWidget(capacityCBox);

    resistanceRBox = new QDoubleSpinBox();
    resistanceRBox->setMinimum(0);
    resistanceRBox->setMaximum(1000000);
    VLayout4->addWidget(resistanceRBox);

    inductanceLBox = new QDoubleSpinBox();
    inductanceLBox->setMinimum(0);
    inductanceLBox->setMaximum(1000000);
    VLayout4->addWidget(inductanceLBox);

    layout2->addLayout(VLayout3);
    layout2->addLayout(VLayout4);
    mainLayout->addLayout(layout2);


    /***/

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *calculateButton = new QPushButton("Расчитать", this);
    buttonLayout->addWidget(calculateButton);
    connect(calculateButton, SIGNAL(clicked()), this, SLOT(on_calculateButton_clicked()));

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_saveButton_clicked()));

    QPushButton *cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_cancelButton_clicked()));

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    // выделение верхнего виджета
    qBox->setFocus();
    qBox->selectAll();
}

SelectionOfCorrectiveElements::~SelectionOfCorrectiveElements()
{

}

void SelectionOfCorrectiveElements::on_cancelButton_clicked()
{
    QWidget::close();
}

void SelectionOfCorrectiveElements::slot_mainToSelectionOfCorrectiveElements(double qSlot, double q1Slot,
                                                                             double f, double delta_f,
                                                                             double C0, double C,
                                                                             double R, double L)
{
    qBox->setValue(qSlot);
    q1Box->setValue(q1Slot);
    freqBox->setValue(f);
    deltaFreqBox->setValue(delta_f);
    capacityC0Box->setValue(C0);
    capacityCBox->setValue(C);
    resistanceRBox->setValue(R);
    inductanceLBox->setValue(L);
}


void SelectionOfCorrectiveElements::on_saveButton_clicked()
{
    emit signal_selectionOfCorrectiveElementsToMain_save(qBox->value(), q1Box->value(), freqBox->value(),
                                                         deltaFreqBox->value(), capacityC0Box->value(), capacityCBox->value(),
                                                         resistanceRBox->value(), inductanceLBox->value());
    QWidget::close();
}


void SelectionOfCorrectiveElements::on_calculateButton_clicked()
{
    emit signal_selectionOfCorrectiveElementsToMain_calculate(qBox->value(), q1Box->value(), freqBox->value(),
                                                         deltaFreqBox->value(), capacityC0Box->value(), capacityCBox->value(),
                                                         resistanceRBox->value(), inductanceLBox->value());
    QWidget::close();
}

