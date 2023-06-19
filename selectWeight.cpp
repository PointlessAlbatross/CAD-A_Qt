#include "selectWeight.h"
#include "ui_selectWeight.h"



SelectWeight::SelectWeight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectWeight)
{
    ui->setupUi(this);
    ui->weightBox->setFocus(); ///< выбирает окошко для ввода числа
    ui->weightBox->selectAll(); ///< выделяет содержимое окошка
}

SelectWeight::~SelectWeight()
{
    delete ui;
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
    ui->weightBox->setValue(weigth);
    ui->label_num->setText(QString::number(i+1) + "." + QString::number(j+1) + "  (" + QString::number(n) + ")");
}

/*!
 * \brief SelectWeight::on_pushButtonSave_clicked
 * Метод вызываемый при нажатии кнопки "Сохранить"
 */
void SelectWeight::on_pushButtonSave_clicked()
{
    emit signalSelectWeightToArrange(ui->weightBox->value(), i, j);
    QWidget::close();
}

/*!
 * \brief SelectWeight::on_pushButtonCancel_clicked
 * Метод вызываемый при нажатии кнопки "Сохранить"
 */
void SelectWeight::on_pushButtonCancel_clicked()
{
    QWidget::close();
}

