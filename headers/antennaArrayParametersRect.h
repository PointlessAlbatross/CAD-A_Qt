#ifndef ANTENNA_ARRAY_PARAMETERS_RECT_H
#define ANTENNA_ARRAY_PARAMETERS_RECT_H

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


class AntennaArrayParametersRect : public QDialog
{
    Q_OBJECT

    QDoubleSpinBox *sizeXBox;
    QDoubleSpinBox *sizeZBox;
    QDoubleSpinBox *distXBox;
    QDoubleSpinBox *distZBox;
    QDoubleSpinBox *radAntBox;
    QSpinBox *numRowBox;
    QDoubleSpinBox *angleRotateBox;

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


public:
    explicit AntennaArrayParametersRect(QWidget *parent = nullptr);
    ~AntennaArrayParametersRect();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();



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
