#include "antenna_array_parameters_rect.h"
#include "ui_antenna_array_parameters_rect.h"
#include "mainwindow.h"

void Antenna_Array_Parameters::arrCapacity(QVector<int> & Ar,
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

 int Antenna_Array_Parameters::maxCapacity(int i)
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

 void Antenna_Array_Parameters::slotMainToParamRect(double size_x1, double size_z1,
                                                   double dist_x1, double dist_z1,
                                                   double rad_ant1, int num_row1)
 {
     qDebug()<<"Вызов слота main_to_param "<<Qt::endl;
     sizeX = size_x1; sizeZ = size_z1; distX = dist_x1;
     distZ = dist_z1; radAnt = rad_ant1; numRow = num_row1;
     PARAM_WINDOW_FLAG = true;
     ui->doubleSpinBox->setValue(sizeX);
     ui->doubleSpinBox_2->setValue(sizeZ);
     ui->doubleSpinBox_3->setValue(distX);
     ui->doubleSpinBox_4->setValue(distZ);
     ui->doubleSpinBox_5->setValue(radAnt);
     ui->spinBox->setValue(numRow);
 }


    //Конструктор//
Antenna_Array_Parameters::Antenna_Array_Parameters(QWidget *parent)://, double & size x) :
    QDialog(parent),
    ui(new Ui::Antenna_Array_Parameters)

{
    PARAM_WINDOW_FLAG = false;
    ui->setupUi(this);
}

Antenna_Array_Parameters::~Antenna_Array_Parameters()
{
    delete ui;
}


void Antenna_Array_Parameters::on_pushButton_clicked()
{
    sizeX = ui->doubleSpinBox->value();
    sizeZ = ui->doubleSpinBox_2->value();
    distX = ui->doubleSpinBox_3->value();
    distZ = ui->doubleSpinBox_4->value();
    radAnt = ui->doubleSpinBox_5->value();
    numRow = ui->spinBox->value();
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


void Antenna_Array_Parameters::on_pushButton_2_clicked()
{
    QWidget::close();
}

