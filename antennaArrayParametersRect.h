#ifndef ANTENNA_ARRAY_PARAMETERS_RECT_H
#define ANTENNA_ARRAY_PARAMETERS_RECT_H

#include <QDialog>
#include <QDebug>
#include <vector>
#include <cmath>

namespace Ui {
class AntennaArrayParametersRect;
}


class AntennaArrayParametersRect : public QDialog
{
    Q_OBJECT

public:
    explicit AntennaArrayParametersRect(QWidget *parent = nullptr);
    ~AntennaArrayParametersRect();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AntennaArrayParametersRect *ui;
    void arrCapacity(QVector<int> & Ar,
                      const QVector<int> & Ar1);
    int maxCapacity(int i);

    double sizeX;
    double sizeZ;
    double distX;
    double distZ;
    double radAnt;
    int numRow;
    QVector<int> MaxElem;

    bool PARAM_WINDOW_FLAG;

signals:
    void signalParamRectToMain(double size_x, double size_z,
                double dist_x, double dist_z, double rad_ant, int num_row,
                QVector<int> Max_elem);
public slots:
    void slotMainToParamRect(double size_x, double size_z,
              double dist_x, double dist_z,
              double rad_ant, int num_row);

};

#endif // ANTENNA_ARRAY_PARAMETERS_RECT_H
