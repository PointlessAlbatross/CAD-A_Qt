#include "line_charts.h"
#include "ui_line_charts.h"

Line_charts::Line_charts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Line_charts)
{
    ui->setupUi(this);
}

Line_charts::~Line_charts()
{
    delete ui;
}

void slot_main_to_charts(QVector<int> Curr_num_elem1, QVector<QVector<double> > Weight_coef1,
                         QVector<QVector<std::tuple<int, int, int> > > Button_pos1,
                         double k1,
                         double size_x1, double size_z1, double dist_x1, double dist_z1,
                         int size_x_pix1, int size_z_pix1, int dist_x_pix1, int dist_z_pix1
                         )
{
    Curr_num_elem = Curr_num_elem1;
    Weight_coef = Weight_coef1;
    Button_pos = Button_pos1;
    k = k1;
    size_x = size_x1;
    size_z = size_z1;
    dist_x = dist_x1;
    dist_z = dist_z1;
    size_x_pix = size_x_pix1;
    size_z_pix = size_z_pix1;
    dist_x_pix = dist_x_pix1;
    dist_z_pix = dist_z_pix1;
}
