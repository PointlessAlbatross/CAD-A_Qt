#ifndef ARRANGEMENT_OF_ELEMENTS_H
#define ARRANGEMENT_OF_ELEMENTS_H

#include <QDialog>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>


namespace Ui {
class Arrangement_of_elements;
}
class Arrangement_of_elements : public QDialog
{
    Q_OBJECT

public:
    explicit Arrangement_of_elements(QWidget *parent = nullptr);
    ~Arrangement_of_elements();

private:
    Ui::Arrangement_of_elements *ui;
    QGraphicsScene *scene;

    int overlay_type;

    int diam_pix;
    int cnt;
    double size_x;
    double size_z;
    double dist_x;
    double dist_z;
    double rad_ant;

    double rad_circ_scr;
    double dist_hex;

    int size_x_pix;
    int size_z_pix;
    int dist_x_pix;
    int dist_z_pix;

    int rad_circ_scr_pix;
    int dist_hex_pix;

    int num_row;
    int channel_num;
    bool regime;
    QVector<int> Max_elem;
    QVector<int> Curr_num_elem;
    QVector<QVector<double>> Weight_coef;
    QVector <QVector<std::tuple<int, int, int>>> Button_pos;
    std::array<QVector<QVector<bool>>, 16> Selected_elem;


    void redrawing();
    void redrawing_rect();
    void redrawing_hex();
    void draw_circ();
    void draw_rect (int x, int z, int size_x_pix, int size_z_pix, int j1, int i1);
    void draw_hex (int x, int z, int rad_circ_scr_pix, int j1, int i1);
    int i1, j1, n1;
    double weight;


    void reshape_plus(int n);
    void reshape_minus(int n);
    void hide_reshape_buttons();
    void disabled_channel_button(bool b);
    bool eventFilter(QObject *watched, QEvent *event);


signals:
    void signal_arrange_to_select_weight (double, int, int, int);
    void signal_arrange_to_main(QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef, QVector <QVector<std::tuple<int, int, int>>> Button_pos,
                                int size_x_pix, int size_z_pix, int dist_x_pix, int dist_z_pix);


public slots:
    void slot_main_to_arrange(double size_x, double size_z, double dist_x, double dist_z,
                              double rad_circ_scr, double dist_hex,
                              double rad_ant, int num_row, QVector<int> Max_elem, QVector<int> Curr_num_elem, QVector<QVector<double>> Weight_coef,
                              std::array<QVector<QVector<bool>>, 16> Selected_elem,
                              int overlay_type);
    void slot_select_weight_to_arrange(double weight, int i1, int j1);
\

private slots:
    void on_radioButton_clicked(bool checked);
    void on_radioButton_2_clicked(bool checked);
    void on_ButtonPlus_1_clicked();
    void on_ButtonMinus_1_clicked();
    void on_ButtonPlus_2_clicked();
    void on_ButtonMinus_2_clicked();
    void on_ButtonPlus_3_clicked();
    void on_ButtonMinus_3_clicked();
    void on_ButtonPlus_4_clicked();
    void on_ButtonMinus_4_clicked();
    void on_ButtonPlus_5_clicked();
    void on_ButtonMinus_5_clicked();
    void on_ButtonPlus_6_clicked();
    void on_ButtonMinus_6_clicked();
    void on_ButtonPlus_7_clicked();
    void on_ButtonMinus_7_clicked();


    void on_ChannelNumButton_1_clicked();
    void on_ChannelNumButton_2_clicked();
    void on_ChannelNumButton_3_clicked();
    void on_ChannelNumButton_4_clicked();
    void on_ChannelNumButton_5_clicked();
    void on_ChannelNumButton_6_clicked();
    void on_ChannelNumButton_7_clicked();
    void on_ChannelNumButton_8_clicked();
    void on_ChannelNumButton_9_clicked();
    void on_ChannelNumButton_10_clicked();
    void on_ChannelNumButton_11_clicked();
    void on_ChannelNumButton_12_clicked();
    void on_ChannelNumButton_13_clicked();
    void on_ChannelNumButton_14_clicked();
    void on_ChannelNumButton_15_clicked();
    void on_ChannelNumButton_16_clicked();
    void on_saveButton_clicked();
};

#endif // ARRANGEMENT_OF_ELEMENTS_H
