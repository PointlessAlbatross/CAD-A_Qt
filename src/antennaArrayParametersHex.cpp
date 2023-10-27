#include "../headers/antennaArrayParametersHex.h"


AntennaArrayParametersHex::AntennaArrayParametersHex(QWidget *parent) :
    QDialog(parent)
{
    PARAM_WINDOW_FLAG = false;


    setWindowTitle("Шестиугольный элемент");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *VLayout1 = new QVBoxLayout();
    QLabel *label1 = new QLabel("Радиус описанной окружности, м");
    QLabel *label2 = new QLabel("Зазор между элементами, м");
    QLabel *label3 = new QLabel("Радиус антенны, м");
    QLabel *label4 = new QLabel("Число рядов");
    QLabel *label5 = new QLabel("Угол поворота решетки, град");
    VLayout1->addWidget(label1);
    VLayout1->addWidget(label2);
    VLayout1->addWidget(label3);
    VLayout1->addWidget(label4);
    VLayout1->addWidget(label5);

    QVBoxLayout *VLayout2 = new QVBoxLayout();
    radHexBox = new QDoubleSpinBox();
    radHexBox->setMinimum(0);
    radHexBox->setMaximum(1);
    radHexBox->setDecimals(3);
    radHexBox->setSingleStep(0.001);
    VLayout2->addWidget(radHexBox);

    distHexBox = new QDoubleSpinBox();
    distHexBox->setMinimum(0);
    distHexBox->setMaximum(1);
    distHexBox->setDecimals(3);
    distHexBox->setSingleStep(0.001);
    VLayout2->addWidget(distHexBox);


    radAntBox = new QDoubleSpinBox();
    radAntBox->setMinimum(0);
    radAntBox->setMaximum(1);
    radAntBox->setSingleStep(0.01);
    VLayout2->addWidget(radAntBox);

    numRowBox = new QSpinBox();
    numRowBox->setMinimum(1);
    numRowBox->setMaximum(20);
    VLayout2->addWidget(numRowBox);

    angleRotateBox = new QDoubleSpinBox();
    angleRotateBox->setMinimum(-180);
    angleRotateBox->setMaximum(180);
    VLayout2->addWidget(angleRotateBox);

    layout1->addLayout(VLayout1);
    layout1->addLayout(VLayout2);

    mainLayout->addLayout(layout1);
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton *cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout);

    // выделение верхнего виджета
    radHexBox->setFocus();
    radHexBox->selectAll();
}

/*!
 * \brief AntennaArrayParametersHex::arrCapacity
 * Метод для зеркального количества элементов в антенне
 * \param Ar Верхние ряды
 * \param Ar1 Нижние ряды
 */
void AntennaArrayParametersHex::arrCapacity(QVector<int> & Ar,
                  const QVector<int> & Ar1)
{
    for (int i = 0; i < numRow / 2; i++)
        Ar[i] = Ar1[numRow / 2 - i];
    for (int i = numRow / 2; i < numRow; i++)
        Ar[i] = Ar1[i - numRow / 2];
}

/*!
 * \brief AntennaArrayParametersHex::maxCapacity
 * Метод вычисляющий максимальное количество элементов в ряду
 * \param i Номер ряда
 * \return Максимальное количество элементов
 */
int AntennaArrayParametersHex::maxCapacity(int i)
{
    size_t n = 0;
    double rad_circ_scr_n = dist * tan(M_PI/6) ;
    double rad_circ_scr_n_top = 0;
    double l_mid = 2 * radAnt *
        sqrt(1 - pow(((radCircScr / 2 + dist * tan(M_PI/6) + i * (tan(M_PI/6) * dist + 1.5*radCircScr)) / radAnt), 2));
    double l_top = 2 * radAnt *
        sqrt(1 - pow(((radCircScr + dist * 1/cos(M_PI/6) + i * (dist * 1/cos(M_PI/6) + 1.5*radCircScr)) / radAnt), 2));
    if (i % 2 == 0) // элемент четный
    {
        while ((rad_circ_scr_n + radCircScr*sqrt(3) + dist * 1/tan(M_PI/6)) < l_mid and
        (rad_circ_scr_n + radCircScr*sqrt(3) + dist) < l_top)
        {
            rad_circ_scr_n += (radCircScr*sqrt(3) + dist * 1/tan(M_PI/6));
            if (n)
                rad_circ_scr_n_top += (radCircScr*sqrt(3) + dist);
            n++;
        }
        if (n % 2 != 0 or !n)
            return n;
        else
            return n-1;
    }
    else
    {
        while ((rad_circ_scr_n + radCircScr*sqrt(3) + dist * 1/tan(M_PI/6)) < l_mid and
        (rad_circ_scr_n + radCircScr*sqrt(3) + dist) < l_top)
        {
            rad_circ_scr_n += (radCircScr*sqrt(3) + dist * 1/tan(M_PI/6));
            if (n)
                rad_circ_scr_n_top += (radCircScr*sqrt(3) + dist);
            n++;
        }
        if (n % 2 == 0)
            return n;
        else
            return n-1;
    }
}


AntennaArrayParametersHex::~AntennaArrayParametersHex()
{

}

/*!
 * \brief AntennaArrayParametersHex::on_saveButton_clicked
 * Кнопка сохранить
 */
void AntennaArrayParametersHex::on_pushButtonSave_clicked()
{
    radCircScr = radHexBox->value();
    dist = distHexBox->value();
    radAnt = radAntBox->value();
    numRow = numRowBox->value();
    if (numRow > 1 and numRow % 2 == 0)
        numRow += 1;
    qDebug()<<"size "<<radCircScr<<Qt::endl;
    QVector<int> Arr(numRow);
    QVector<int> Arr1(numRow / 2 + numRow % 2);
    for (int i = 0; i < numRow / 2 + numRow % 2; i++)
        Arr1[i] = maxCapacity(i);
    arrCapacity(Arr, Arr1);
    MaxElem = Arr;
    qDebug()<<MaxElem<<Qt::endl;
    emit signalParamHexToMain(radCircScr, dist,
              radAnt, numRow, MaxElem);
    QWidget::close();

}

/*!
 * \brief AntennaArrayParametersHex::on_cancelButton_clicked
 * Кнопка отмена
 */
void AntennaArrayParametersHex::on_pushButtonCancel_clicked() // отмена
{
    QWidget::close();
}

/*!
 * \brief AntennaArrayParametersHex::slotMainToParamHex
 * Слот принимающий данные из главного окна
 * \param rad_circ_scr_1 Радиус описанной окружности
 * \param dist_1 Зазор между элементами
 * \param rad_ant_1 Радиус антенной решетки
 * \param num_row_1 Количество рядов элементов
 */
void AntennaArrayParametersHex::slotMainToParamHex(double rad_circ_scr_1, double dist_1, double rad_ant_1, int num_row_1)
{
    qDebug()<<"Вызов слота main_to_param_hex "<<Qt::endl;
    radCircScr = rad_circ_scr_1; dist = dist_1;
    radAnt = rad_ant_1; numRow = num_row_1;
    PARAM_WINDOW_FLAG = true;
    radHexBox->setValue(radCircScr);
    distHexBox->setValue(dist);
    radAntBox->setValue(radAnt);
    numRowBox->setValue(numRow);
}
