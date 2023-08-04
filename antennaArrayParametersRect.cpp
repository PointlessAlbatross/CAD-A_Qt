#include "antennaArrayParametersRect.h"
#include "mainwindow.h"


AntennaArrayParametersRect::AntennaArrayParametersRect(QWidget *parent):
    QDialog(parent)
{
    PARAM_WINDOW_FLAG = false;

    setWindowTitle("Четырехугольный элемент");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QHBoxLayout *layout1 = new QHBoxLayout();
    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    QVBoxLayout *VLayout1 = new QVBoxLayout();
    QLabel *label1 = new QLabel("Размер по X, м");
    QLabel *label2 = new QLabel("Размер по Z, м");
    VLayout1->addWidget(label1);
    VLayout1->addWidget(label2);

    QVBoxLayout *VLayout2 = new QVBoxLayout();
    sizeXBox = new QDoubleSpinBox();
    sizeXBox->setMinimum(0);
    sizeXBox->setMaximum(1);
    sizeXBox->setDecimals(3);
    sizeXBox->setSingleStep(0.001);
    VLayout2->addWidget(sizeXBox);

    sizeZBox = new QDoubleSpinBox();
    sizeZBox->setMinimum(0);
    sizeZBox->setMaximum(1);
    sizeZBox->setDecimals(3);
    sizeZBox->setSingleStep(0.001);
    VLayout2->addWidget(sizeZBox);

    Hlayout1->addLayout(VLayout1);
    Hlayout1->addLayout(VLayout2);

    /***/

    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    QVBoxLayout *VLayout3 = new QVBoxLayout();
    QLabel *label3 = new QLabel("Зазор по X, м");
    QLabel *label4 = new QLabel("Зазор по Z, м");
    VLayout3->addWidget(label3);
    VLayout3->addWidget(label4);

    QVBoxLayout *VLayout4 = new QVBoxLayout();
    distXBox = new QDoubleSpinBox();
    distXBox->setMinimum(0);
    distXBox->setMaximum(1);
    distXBox->setDecimals(3);
    distXBox->setSingleStep(0.001);
    VLayout4->addWidget(distXBox);

    distZBox = new QDoubleSpinBox();
    distZBox->setMinimum(0);
    distZBox->setMaximum(1);
    distZBox->setDecimals(3);
    distZBox->setSingleStep(0.001);
    VLayout4->addWidget(distZBox);

    Hlayout2->addLayout(VLayout3);
    Hlayout2->addLayout(VLayout4);

    layout1->addLayout(Hlayout1);
    layout1->addLayout(Hlayout2);

    mainLayout->addLayout(layout1);

    /**/

    QHBoxLayout *layout2 = new QHBoxLayout();
    QVBoxLayout *VLayout5 = new QVBoxLayout();
    QLabel *label5 = new QLabel("Радиус антенны, м");
    QLabel *label6 = new QLabel("Число рядов");
    QLabel *label7 = new QLabel("Угол поворота решетки, град");
    VLayout5->addWidget(label5);
    VLayout5->addWidget(label6);
    VLayout5->addWidget(label7);

    QVBoxLayout *VLayout6 = new QVBoxLayout();
    radAntBox = new QDoubleSpinBox();
    radAntBox->setMinimum(0);
    radAntBox->setMaximum(1);
    radAntBox->setSingleStep(0.01);
    VLayout6->addWidget(radAntBox);

    numRowBox = new QSpinBox();
    numRowBox->setMinimum(1);
    numRowBox->setMaximum(20);
    VLayout6->addWidget(numRowBox);

    angleRotateBox = new QDoubleSpinBox();
    angleRotateBox->setMinimum(-180);
    angleRotateBox->setMaximum(180);
    VLayout6->addWidget(angleRotateBox);

    layout2->addLayout(VLayout5);
    layout2->addLayout(VLayout6);
    mainLayout->addLayout(layout2);

    /**/

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    buttonLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(on_pushButtonSave_clicked()));

    QPushButton *cancelButton = new QPushButton("Отменить", this);
    buttonLayout->addWidget(cancelButton);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(on_pushButtonCancel_clicked()));

    mainLayout->addLayout(buttonLayout);



    // выделение верхнего виджета
    sizeXBox->setFocus();
    sizeXBox->selectAll();
}

/*!
 * \brief AntennaArrayParametersRect::arrCapacity
 * Метод для зеркального количества элементов
 * \param Ar Верхние ряды
 * \param Ar1 Нижние ряды
 */
void AntennaArrayParametersRect::arrCapacity(QVector<int> & Ar,
                  const QVector<int> & Ar1) {
    if (numRow & 1) // Нечетное число рядов
    {
    for (int i = 0; i < numRow / 2; i++)
    Ar[i] = Ar1[numRow / 2  - i];
    for (int i =numRow / 2; i < numRow; i++)
    Ar[i] = Ar1[i - numRow / 2];
    }
    else // Четное число рядов
    {
        for (int i = 0; i < numRow / 2; i++)
            Ar[i] = Ar1[numRow / 2 - 1 - i];
        for (int i = numRow / 2; i < numRow; i++)
            Ar[i] = Ar1[i - numRow / 2];
    }
}

 int AntennaArrayParametersRect::maxCapacity(int i)
 {

     size_t n = 0;
     double xn = 0;

     if(numRow % 2 == 0){// число рядов четное
         double l = 2 * radAnt *
                 sqrt(1 - pow(((sizeZ  + i * (distZ + sizeZ)) / radAnt), 2));
         while ((xn + sizeX + distX) < l) {
             xn += (sizeX + distX);
             n++;
         }
     }
     else if(numRow & 1){ // число рядов не четное
         double l = 2 * radAnt *
                 sqrt(1 - pow(((sizeZ / 2 + i * (distZ + sizeZ)) / radAnt), 2));
         while ((xn + sizeX + distX) < l) {
             xn += (sizeX + distX);
             n++;
         }
     }
     return n;
 }

 void AntennaArrayParametersRect::slotMainToParamRect(double size_x1, double size_z1,
                                                   double dist_x1, double dist_z1,
                                                   double rad_ant1, int num_row1)
 {
     qDebug()<<"Вызов слота main_to_param "<<Qt::endl;
     sizeX = size_x1; sizeZ = size_z1; distX = dist_x1;
     distZ = dist_z1; radAnt = rad_ant1; numRow = num_row1;
     PARAM_WINDOW_FLAG = true;
     sizeXBox->setValue(sizeX);
     sizeZBox->setValue(sizeZ);
     distXBox->setValue(distX);
     distZBox->setValue(distZ);
     radAntBox->setValue(radAnt);
     numRowBox->setValue(numRow);
 }


AntennaArrayParametersRect::~AntennaArrayParametersRect()
{

}


void AntennaArrayParametersRect::on_pushButtonSave_clicked()
{
    sizeX = sizeXBox->value();
    sizeZ = sizeZBox->value();
    distX = distXBox->value();
    distZ = distZBox->value();
    radAnt = radAntBox->value();
    numRow = numRowBox->value();
    qDebug()<<"size "<<sizeX<<Qt::endl;
    QVector<int> Arr(numRow);
    QVector<int> Arr1(numRow / 2 + numRow % 2);
    for (int i = 0; i < numRow / 2 + numRow % 2; i++)
        Arr1[i] = maxCapacity(i);
    arrCapacity(Arr, Arr1);
    MaxElem = Arr;
    qDebug()<<MaxElem<<Qt::endl;
    emit signalParamRectToMain(sizeX, sizeZ, distX, distZ,
                radAnt, numRow, MaxElem);
    QWidget::close();
}


void AntennaArrayParametersRect::on_pushButtonCancel_clicked()
{
    QWidget::close();
}
