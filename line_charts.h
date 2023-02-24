#ifndef LINE_CHARTS_H
#define LINE_CHARTS_H

#include <QDialog>

namespace Ui {
class Line_charts;
}

class Line_charts : public QDialog
{
    Q_OBJECT

public:
    explicit Line_charts(QWidget *parent = nullptr);
    ~Line_charts();

   public:
    QVector<int> Curr_num_elem;
    QVector<QVector<double>> Weight_coef;
    QVector<QVector<std::tuple<int, int, int> > > Button_pos;

    double size_x;
    double size_z;
    double dist_x;
    double dist_z;

    int size_x_pix;
    int size_z_pix;
    int dist_x_pix;
    int dist_z_pix;

    double k; // Волновое число

public slots:
    void slot_main_to_charts(QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef, QVector<QVector<std::tuple<int, int, int> > > Button_pos,
                             double k,
                             double size_x, double size_z, double dist_x, double dist_z,
                             int size_x_pix, int size_z_pix, int dist_x_pix, int dist_z_pix);
private:
    Ui::Line_charts *ui;
};


#endif // LINE_CHARTS_H
