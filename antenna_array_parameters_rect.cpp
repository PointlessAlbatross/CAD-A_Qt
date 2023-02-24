#include "antenna_array_parameters_rect.h"
#include "ui_antenna_array_parameters_rect.h"
#include "mainwindow.h"

void Antenna_Array_Parameters::arr_capacity(QVector<int> & Ar,
                  const QVector<int> & Ar1) {
    if (num_row & 1) // Нечетное число рядов
    {
    for (int i = 0; i < num_row / 2; i++)
    Ar[i] = Ar1[num_row / 2  - i];
    for (int i =num_row / 2; i < num_row; i++)
    Ar[i] = Ar1[i - num_row / 2];
    }
    else // Четное число рядов
    {
        for (int i = 0; i < num_row / 2; i++)
            Ar[i] = Ar1[num_row / 2 - 1 - i];
        for (int i = num_row / 2; i < num_row; i++)
            Ar[i] = Ar1[i - num_row / 2];
    }
}

 int Antenna_Array_Parameters::max_capacity(int i)
 {

     size_t n = 0;
     double xn = 0;

     if(num_row % 2 == 0){// число рядов четное
         double l = 2 * rad_ant *
                 sqrt(1 - pow(((size_z  + i * (dist_z + size_z)) / rad_ant), 2));
         while ((xn + size_x + dist_x) < l) {
             xn += (size_x + dist_x);
             n++;
         }
     }
     else if(num_row & 1){ // число рядов не четное
         double l = 2 * rad_ant *
                 sqrt(1 - pow(((size_z / 2 + i * (dist_z + size_z)) / rad_ant), 2));
         while ((xn + size_x + dist_x) < l) {
             xn += (size_x + dist_x);
             n++;
         }
     }
     return n;
 }

 void Antenna_Array_Parameters::slot_main_to_param_rect(double size_x1, double size_z1,
                                                   double dist_x1, double dist_z1,
                                                   double rad_ant1, int num_row1)
 {
     qDebug()<<"Вызов слота main_to_param "<<Qt::endl;
     size_x = size_x1; size_z = size_z1; dist_x = dist_x1;
     dist_z = dist_z1; rad_ant = rad_ant1; num_row = num_row1;
     PARAM_WINDOW_FLAG = true;
     ui->doubleSpinBox->setValue(size_x);
     ui->doubleSpinBox_2->setValue(size_z);
     ui->doubleSpinBox_3->setValue(dist_x);
     ui->doubleSpinBox_4->setValue(dist_z);
     ui->doubleSpinBox_5->setValue(rad_ant);
     ui->spinBox->setValue(num_row);
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
    size_x = ui->doubleSpinBox->value();
    size_z = ui->doubleSpinBox_2->value();
    dist_x = ui->doubleSpinBox_3->value();
    dist_z = ui->doubleSpinBox_4->value();
    rad_ant = ui->doubleSpinBox_5->value();
    num_row = ui->spinBox->value();
    qDebug()<<"size "<<size_x<<Qt::endl;
    QVector<int> Arr(num_row);
    QVector<int> Arr1(num_row / 2 + num_row % 2);
    for (int i = 0; i < num_row / 2 + num_row % 2; i++)
        Arr1[i] = max_capacity(i);
    arr_capacity(Arr, Arr1);
    Max_elem = Arr;
    qDebug()<<Max_elem<<Qt::endl;
    emit signal_param_rect_to_main(size_x, size_z, dist_x, dist_z,
                rad_ant, num_row, Max_elem);
    QWidget::close();
}


void Antenna_Array_Parameters::on_pushButton_2_clicked()
{
    QWidget::close();
}

