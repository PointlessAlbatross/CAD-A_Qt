#include "selectWeight.h"
#include <QDebug>

SelectWeight::SelectWeight(QWidget *parent) :
    QDialog(parent)
{

    setWindowTitle("Выбор весового коэффициента");


    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* buttonLayout1 = new QHBoxLayout();
    label = new QLabel("Накладка номер");
    buttonLayout1->addWidget(label);
    label_num = new QLabel("num");
    buttonLayout1->addWidget(label_num);
    mainLayout->addLayout(buttonLayout1);

    QHBoxLayout* buttonLayout2 = new QHBoxLayout();
    weightLabel = new QLabel("Весовой коэфициент:", this);
    buttonLayout2->addWidget(weightLabel);

    weightBox = new QDoubleSpinBox(this);
    buttonLayout2->addWidget(weightBox);
    weightBox->setMaximum(1);
    mainLayout->addLayout(buttonLayout2);

    QHBoxLayout* buttonLayout3 = new QHBoxLayout();

    QPushButton* saveButton = new QPushButton("Сохранить", this);
    buttonLayout3->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton* cancelButton = new QPushButton("Отменить", this);
    buttonLayout3->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout3);

    setLayout(mainLayout);

    weightBox->setFocus(); ///< выбирает окошко для ввода числа
    weightBox->selectAll(); ///< выделяет содержимое окошка
}

SelectWeight::~SelectWeight()
{

}

/*!
 * \brief SelectWeight::slotArrangeToSelectWeigth
 * Слот, вызываемый при включении окна и передает параметры из главного окна в даннное окно
 * \param[in] weigth1 Весовой коэфициент элемента
 * \param[in] i1 Строка элемента
 * \param[in] j1 Столбец элемента
 * \param[in] n1 Порядковый номер элемента
 */
void SelectWeight::slotArrangeToSelectWeigth(double weigth1, int i1, int j1, int n1)
{
    weigth = weigth1;
    i = i1;
    j = j1;
    n = n1;
    weightBox->setValue(weigth);
    label_num->setText(QString::number(i+1) + "." + QString::number(j+1) + "  (" + QString::number(n) + ")");
}

/*!
 * \brief SelectWeight::on_pushButtonSave_clicked
 * Метод вызываемый при нажатии кнопки "Сохранить"
 */
void SelectWeight::on_pushButtonSave_clicked()
{
    emit signalSelectWeightToArrange(weightBox->value(), i, j);
    QDialog::close();
}

/*!
 * \brief SelectWeight::on_pushButtonCancel_clicked
 * Метод вызываемый при нажатии кнопки "Сохранить"
 */
void SelectWeight::on_pushButtonCancel_clicked()
{
    QDialog::close();
}

