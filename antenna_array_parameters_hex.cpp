#include "antenna_array_parameters_hex.h"
#include "ui_antenna_array_parameters_hex.h"

void Antenna_Array_Parameters_Hex::arr_capacity(QVector<int> & Ar,
                  const QVector<int> & Ar1)
{
    for (int i = 0; i < num_row / 2; i++)
        Ar[i] = Ar1[num_row / 2 - i];
    for (int i = num_row / 2; i < num_row; i++)
        Ar[i] = Ar1[i - num_row / 2];
}


int Antenna_Array_Parameters_Hex::max_capacity(int i)
{
    size_t n = 0;
    double rad_circ_scr_n = dist * tan(M_PI/6) ;
    double rad_circ_scr_n_top = 0;
    double l_mid = 2 * rad_ant *
        sqrt(1 - pow(((rad_circ_scr / 2 + dist * tan(M_PI/6) + i * (tan(M_PI/6) * dist + 1.5*rad_circ_scr)) / rad_ant), 2));
    double l_top = 2 * rad_ant *
        sqrt(1 - pow(((rad_circ_scr + dist * 1/cos(M_PI/6) + i * (dist * 1/cos(M_PI/6) + 1.5*rad_circ_scr)) / rad_ant), 2));
    if (i % 2 == 0) // элемент четный
    {
        while ((rad_circ_scr_n + rad_circ_scr*sqrt(3) + dist * 1/tan(M_PI/6)) < l_mid and
        (rad_circ_scr_n + rad_circ_scr*sqrt(3) + dist) < l_top)
        {
            rad_circ_scr_n += (rad_circ_scr*sqrt(3) + dist * 1/tan(M_PI/6));
            if (n)
                rad_circ_scr_n_top += (rad_circ_scr*sqrt(3) + dist);
            n++;
        }
        if (n % 2 != 0 or !n)
            return n;
        else
            return n-1;
    }
    else
    {
        while ((rad_circ_scr_n + rad_circ_scr*sqrt(3) + dist * 1/tan(M_PI/6)) < l_mid and
        (rad_circ_scr_n + rad_circ_scr*sqrt(3) + dist) < l_top)
        {
            rad_circ_scr_n += (rad_circ_scr*sqrt(3) + dist * 1/tan(M_PI/6));
            if (n)
                rad_circ_scr_n_top += (rad_circ_scr*sqrt(3) + dist);
            n++;
        }
        if (n % 2 == 0)
            return n;
        else
            return n-1;
    }
}


Antenna_Array_Parameters_Hex::Antenna_Array_Parameters_Hex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Antenna_Array_Parameters_Hex)
{
    ui->setupUi(this);
}


Antenna_Array_Parameters_Hex::~Antenna_Array_Parameters_Hex()
{
    delete ui;
}

void Antenna_Array_Parameters_Hex::on_saveButton_clicked() // сохранить
{
    rad_circ_scr = ui->doubleSpinBox_1->value();
    dist = ui->doubleSpinBox_2->value();
    rad_ant = ui->doubleSpinBox_3->value();
    num_row = ui->spinBox->value();
    if (num_row > 1 and num_row % 2 == 0)
        num_row += 1;
    qDebug()<<"size "<<rad_circ_scr<<Qt::endl;
    QVector<int> Arr(num_row);
    QVector<int> Arr1(num_row / 2 + num_row % 2);
    for (int i = 0; i < num_row / 2 + num_row % 2; i++)
        Arr1[i] = max_capacity(i);
    arr_capacity(Arr, Arr1);
    Max_elem = Arr;
    qDebug()<<Max_elem<<Qt::endl;
    emit signal_param_hex_to_main(rad_circ_scr, dist,
              rad_ant, num_row, Max_elem);
    QWidget::close();

}


void Antenna_Array_Parameters_Hex::on_cancelButton_clicked() // отмена
{
    QWidget::close();
}

void Antenna_Array_Parameters_Hex::slot_main_to_param_hex(double rad_circ_scr_1, double dist_1, double rad_ant_1, int num_row_1)
{
    qDebug()<<"Вызов слота main_to_param_hex "<<Qt::endl;
    rad_circ_scr = rad_circ_scr_1; dist = dist_1;
    rad_ant = rad_ant_1; num_row = num_row_1;
    PARAM_WINDOW_FLAG = true;
    ui->doubleSpinBox_1->setValue(rad_circ_scr);
    ui->doubleSpinBox_2->setValue(dist);
    ui->doubleSpinBox_3->setValue(rad_ant);
    ui->spinBox->setValue(num_row);
}


