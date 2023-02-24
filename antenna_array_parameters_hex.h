#ifndef ANTENNA_ARRAY_PARAMETERS_HEX_H
#define ANTENNA_ARRAY_PARAMETERS_HEX_H

#include <QDialog>
#include<QDebug>
#include <vector>
#include <cmath>

namespace Ui {
class Antenna_Array_Parameters_Hex;
}

class Antenna_Array_Parameters_Hex : public QDialog
{
    Q_OBJECT

public:
    explicit Antenna_Array_Parameters_Hex(QWidget *parent = nullptr);
    ~Antenna_Array_Parameters_Hex();

private:
    Ui::Antenna_Array_Parameters_Hex *ui;

    void arr_capacity(QVector<int> & Ar,
                      const QVector<int> & Ar1);
    int max_capacity(int i);

    double rad_circ_scr;
    double rad_ant;
    double dist;
    int num_row;
    QVector<int> Max_elem;

    bool PARAM_WINDOW_FLAG;

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

signals:
    void signal_param_hex_to_main(double rad_circ_scr, double dist,
                                  double rad_ant, int num_row,
                                  QVector<int> Max_elem);

public slots:
    void slot_main_to_param_hex(double rad_circ_scr, double dist,
              double rad_ant, int num_row);

};

#endif // ANTENNA_ARRAY_PARAMETERS_HEX_H
