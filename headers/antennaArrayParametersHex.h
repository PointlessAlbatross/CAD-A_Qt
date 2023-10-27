#ifndef ANTENNA_ARRAY_PARAMETERS_HEX_H
#define ANTENNA_ARRAY_PARAMETERS_HEX_H

#include <QDialog>
#include <vector>
#include <cmath>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLabel>


class AntennaArrayParametersHex : public QDialog
{
    Q_OBJECT

    QDoubleSpinBox *radHexBox;
    QDoubleSpinBox *distHexBox;
    QDoubleSpinBox *radAntBox;
    QSpinBox *numRowBox;
    QDoubleSpinBox *angleRotateBox;


    void arrCapacity(QVector<int> & Ar,
                      const QVector<int> & Ar1);
    int maxCapacity(int i);

    double radCircScr;
    double radAnt;
    double dist;
    int numRow;
    QVector<int> MaxElem;

    bool PARAM_WINDOW_FLAG;

public:
    explicit AntennaArrayParametersHex(QWidget *parent = nullptr);
    ~AntennaArrayParametersHex();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();

signals:
    void signalParamHexToMain(double rad_circ_scr, double dist,
                                  double rad_ant, int num_row,
                                  QVector<int> Max_elem);

public slots:
    void slotMainToParamHex(double rad_circ_scr, double dist,
              double rad_ant, int num_row);

};

#endif // ANTENNA_ARRAY_PARAMETERS_HEX_H
