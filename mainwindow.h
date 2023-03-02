#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <antenna_array_parameters_rect.h>
#include <antenna_array_parameters_hex.h>
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_action_triggered();

    void on_antenna_array_triggered();

    void on_exit_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_charts_action_triggered();

private:
    Ui::MainWindow *ui;

    int overlay_type;

    double rad_circ_scr;
    double dist;

    double size_x;
    double size_z;
    double dist_x;
    double dist_z;

    double rad_ant;

    int size_x_pix;
    int size_z_pix;
    int dist_x_pix;
    int dist_z_pix;

    int rad_circ_scr_pix;
    int dist_hex_pix;

    int duration;
    int pressure;
    int radiation_freq;
    int receiving_freq;
    double k; // Волновое число

    int num_row;
    QVector<int> Max_elem;

    std::array<QVector<QVector<bool>>, 16> Selected_elem;
    QVector<int> Curr_num_elem;
    QVector<QVector<double>> Weight_coef;
    QVector<QVector<std::tuple<int, int, int> > > Button_pos;


    bool PARAM_WINDOW_FLAG;
signals:
    void signal_main_to_param_rect(double size_x, double size_z,
                double dist_x, double dist_z,
                double rad_ant, int num_row);
    void signal_main_to_param_hex(double size_x, double dist,
                double rad_ant, int num_row);
    void signal_main_to_operating_system_parameters(int duration, int pressure, int receiving_freq,
                                                    int radiation_freq);
    void signal_main_to_arrange(double size_x, double size_z, double dist_x, double dist_z,
                double rad_circ_scr, double dist,
                double rad_ant, int num_row, QVector<int> Max_elem, QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef,
                std::array<QVector<QVector<bool>>, 16> Selected_elem,
                                int overlay_type);
    void signal_main_to_charts(QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef, QVector<QVector<std::tuple<int, int, int> > > Button_pos,
                               double k,
                               double size_x, double size_z, double dist_x, double dist_z,
                               int size_x_pix, int size_z_pix,
                               double rad_circ_scr, double dist_hex,
                               int rad_circ_scr_pix, int dist_hex_pix,
                               int overlay_type);
public slots:
    void slot_param_rect_to_main(double size_x, double size_z,
              double dist_x, double dist_z,
              double rad_ant, int num_row,
              QVector<int> Max_elem);
    void slot_param_hex_to_main(double rad_circ_scr, double dist,
              double rad_ant, int num_row,
              QVector<int> Max_elem);
    void slot_operating_system_parameters_to_main(int duration, int pressure, int receiving_freq,
                                                  int radiation_freq);
    void slot_arrange_to_main(QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef, QVector <QVector<std::tuple<int, int, int>>> Button_pos,
                              int size_x_pix, int size_z_pix, int dist_x_pix, int dist_z_pix,
                              int rad_circ_scr_pix, int dist_hex_pix);
};
#endif // MAINWINDOW_H
