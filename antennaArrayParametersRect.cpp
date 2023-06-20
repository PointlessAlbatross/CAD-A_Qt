#include "antennaArrayParametersRect.h"
#include "ui_antennaArrayParametersRect.h"
#include "mainwindow.h"

    //Конструктор//
AntennaArrayParametersRect::AntennaArrayParametersRect(QWidget *parent):
    QDialog(parent),
    ui(new Ui::AntennaArrayParametersRect)
{
    PARAM_WINDOW_FLAG = false;
    ui->setupUi(this);
    // выделение верхнего виджета
    ui->sizeXBox->setFocus();
    ui->sizeXBox->selectAll();
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
     ui->sizeXBox->setValue(sizeX);
     ui->sizeZBox->setValue(sizeZ);
     ui->distXBox->setValue(distX);
     ui->distZBox->setValue(distZ);
     ui->radAntBox->setValue(radAnt);
     ui->numRowBox->setValue(numRow);
 }


AntennaArrayParametersRect::~AntennaArrayParametersRect()
{
    delete ui;
}


void AntennaArrayParametersRect::on_pushButton_clicked()
{
    sizeX = ui->sizeXBox->value();
    sizeZ = ui->sizeZBox->value();
    distX = ui->distXBox->value();
    distZ = ui->distZBox->value();
    radAnt = ui->radAntBox->value();
    numRow = ui->numRowBox->value();
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


void AntennaArrayParametersRect::on_pushButton_2_clicked()
{
    QWidget::close();
}
