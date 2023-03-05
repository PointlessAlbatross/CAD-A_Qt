#ifndef ANTENNAARRAYPARAMETERSHEX_H
#define ANTENNAARRAYPARAMETERSHEX_H

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

    void arrCapacity(QVector<int> & Ar,
                      const QVector<int> & Ar1);
    int maxCapacity(int i);

    double radCircScr;
    double radAnt;
    double dist;
    int numRow;
    QVector<int> MaxElem;

    bool PARAM_WINDOW_FLAG;

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

signals:
    void signalParamHexToMain(double rad_circ_scr, double dist,
                                  double rad_ant, int num_row,
                                  QVector<int> Max_elem);

public slots:
    void slotMainToParamHex(double rad_circ_scr, double dist,
              double rad_ant, int num_row);

};

#endif // ANTENNAARRAYPARAMETERSHEX_H
