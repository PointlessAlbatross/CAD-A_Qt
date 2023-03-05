#include "antenna_array_parameters_hex.h"
#include "ui_antenna_array_parameters_hex.h"

void Antenna_Array_Parameters_Hex::arrCapacity(QVector<int> & Ar,
                  const QVector<int> & Ar1)
{
    for (int i = 0; i < numRow / 2; i++)
        Ar[i] = Ar1[numRow / 2 - i];
    for (int i = numRow / 2; i < numRow; i++)
        Ar[i] = Ar1[i - numRow / 2];
}


int Antenna_Array_Parameters_Hex::maxCapacity(int i)
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
    radCircScr = ui->doubleSpinBox_1->value();
    dist = ui->doubleSpinBox_2->value();
    radAnt = ui->doubleSpinBox_3->value();
    numRow = ui->spinBox->value();
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


void Antenna_Array_Parameters_Hex::on_cancelButton_clicked() // отмена
{
    QWidget::close();
}

void Antenna_Array_Parameters_Hex::slotMainToParamHex(double rad_circ_scr_1, double dist_1, double rad_ant_1, int num_row_1)
{
    qDebug()<<"Вызов слота main_to_param_hex "<<Qt::endl;
    radCircScr = rad_circ_scr_1; dist = dist_1;
    radAnt = rad_ant_1; numRow = num_row_1;
    PARAM_WINDOW_FLAG = true;
    ui->doubleSpinBox_1->setValue(radCircScr);
    ui->doubleSpinBox_2->setValue(dist);
    ui->doubleSpinBox_3->setValue(radAnt);
    ui->spinBox->setValue(numRow);
}


