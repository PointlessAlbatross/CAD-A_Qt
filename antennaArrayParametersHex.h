#ifndef ANTENNA_ARRAY_PARAMETERS_HEX_H
#define ANTENNA_ARRAY_PARAMETERS_HEX_H

#include <QDialog>
#include <QDebug>
#include <vector>
#include <cmath>

namespace Ui {
class AntennaArrayParametersHex;
}

class AntennaArrayParametersHex : public QDialog
{
    Q_OBJECT

public:
    explicit AntennaArrayParametersHex(QWidget *parent = nullptr);
    ~AntennaArrayParametersHex();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AntennaArrayParametersHex *ui;
    void arrCapacity(QVector<int> & Ar,
                      const QVector<int> & Ar1);
    int maxCapacity(int i);

    double radCircScr;
    double radAnt;
    double dist;
    int numRow;
    QVector<int> MaxElem;

    bool PARAM_WINDOW_FLAG;


signals:
    void signalParamHexToMain(double rad_circ_scr, double dist,
                                  double rad_ant, int num_row,
                                  QVector<int> Max_elem);

public slots:
    void slotMainToParamHex(double rad_circ_scr, double dist,
              double rad_ant, int num_row);

};

#endif // ANTENNA_ARRAY_PARAMETERS_HEX_H
