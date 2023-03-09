#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "operatingSystemParameters.h"
#include "arrangementOfElements.h"
#include "antennaArrayParametersRect.h"
#include "antennaArrayParametersHex.h"
#include "patternCharts.h"
#include <QMessageBox>
#include <QDebug>


    //Конструктор//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PARAM_WINDOW_FLAG = false;
    overlay_type = 0;
    ui->action_3->setText("Вид накладки:  4-угольники");
    duration = 1;
    pressure = 1;
    radiation_freq = 20550;
    receiving_freq = 20000;
    k = radiation_freq * 2 * M_PI / 1500;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered() // Растановка элементов
{
    if (PARAM_WINDOW_FLAG) // наличие установленных параметров
    {
        qDebug() << "Вызов растановки " <<Qt::endl;
        Arrangement_of_elements window;
        connect(this, &MainWindow::signal_main_to_arrange, &window, &Arrangement_of_elements::slotMainToArrange);
        emit signal_main_to_arrange(size_x, size_z,
                                    dist_x, dist_z,
                                    rad_circ_scr, dist,
                                    rad_ant, num_row, Max_elem, Curr_num_elem,  Weight_coef, Selected_elem,
                                    overlay_type);
        connect(&window, &Arrangement_of_elements::signalArrangeToMain, this, &MainWindow::slot_arrange_to_main);
        window.setModal(true);
        window.exec();
    }
}


void MainWindow::on_antenna_array_triggered()
{
    if (!overlay_type)
    {
        Antenna_Array_Parameters window;
        connect(this, &MainWindow::signal_main_to_param_rect, &window, &Antenna_Array_Parameters::slotMainToParamRect);
        if (PARAM_WINDOW_FLAG)
            emit signal_main_to_param_rect(size_x, size_z, dist_x,
                                      dist_z, rad_ant, num_row);
        connect(&window, &Antenna_Array_Parameters::signalParamRectToMain, this, &MainWindow::slot_param_rect_to_main);
        window.setModal(true);
        window.exec();
    }
    else if (overlay_type)
    {
        Antenna_Array_Parameters_Hex window;
        connect(this, &MainWindow::signal_main_to_param_hex, &window, &Antenna_Array_Parameters_Hex::slotMainToParamHex);
        if (PARAM_WINDOW_FLAG)
            emit signal_main_to_param_hex(rad_circ_scr, dist,
                                      rad_ant, num_row);
        connect(&window, &Antenna_Array_Parameters_Hex::signalParamHexToMain, this, &MainWindow::slot_param_hex_to_main);
        window.setModal(true);
        window.exec();

    }
}


void MainWindow::on_exit_action_triggered()
{
    QApplication::exit();
}

    //Слот param to main
void MainWindow::slot_param_rect_to_main(double size_x1, double size_z1,
                      double dist_x1, double dist_z1,
                      double rad_ant1, int num_row1, QVector<int> Max_elem1)
{
    size_x = size_x1; size_z = size_z1; dist_x = dist_x1;
    dist_z = dist_z1; rad_ant = rad_ant1; num_row = num_row1;
    PARAM_WINDOW_FLAG = true; Max_elem = Max_elem1;
    Curr_num_elem = Max_elem1;
    Weight_coef.resize(num_row);
    for (int i = 0; i < num_row; i++)
        Weight_coef[i].resize(Max_elem[i]);
    for (int i = 0; i < Weight_coef.size(); i++)
    {
        for (int j = 0; j < Weight_coef[i].size(); j++)
            Weight_coef[i][j] = 1;
    }
    for (unsigned int i = 0; i < Selected_elem.size(); i++)
    {
        Selected_elem[i].resize(num_row);
        for(int j = 0; j < num_row; j++ )
            Selected_elem[i][j].resize(Max_elem[j]);
    }
}

void MainWindow::slot_param_hex_to_main(double rad_circ_scr_1, double dist_1, double rad_ant_1, int num_row_1, QVector<int> Max_elem_1)
{
    rad_circ_scr = rad_circ_scr_1; dist = dist_1;
    rad_ant = rad_ant_1; num_row = num_row_1;
    PARAM_WINDOW_FLAG = true; Max_elem = Max_elem_1;
    Curr_num_elem = Max_elem_1;
    Weight_coef.resize(num_row);
    for (int i = 0; i < num_row; i++)
        Weight_coef[i].resize(Max_elem[i]);
    for (int i = 0; i < Weight_coef.size(); i++)
    {
        for (int j = 0; j < Weight_coef[i].size(); j++)
            Weight_coef[i][j] = 1;
    }
    for (unsigned int i = 0; i < Selected_elem.size(); i++)
    {
        Selected_elem[i].resize(num_row);
        for(int j = 0; j < num_row; j++ )
            Selected_elem[i][j].resize(Max_elem[j]);
    }
}

void MainWindow::slot_operating_system_parameters_to_main(int duration1, int pressure1, int receiving_freq1, int radiation_freq1)
{
    duration = duration1;
    pressure = pressure1;
    receiving_freq = receiving_freq1;
    radiation_freq = radiation_freq1;
    k = radiation_freq1 * 2 * M_PI / 1500;
    qDebug() <<"k = " << k << Qt::endl;
}

void MainWindow::slot_arrange_to_main(QVector<int> Curr_num_elem1, QVector<QVector<double> > Weight_coef1, QVector<QVector<std::tuple<int, int, int> > > Button_pos1,
                                      int size_x_pix1, int size_z_pix1, int dist_x_pix1, int dist_z_pix1,
                                      int rad_circ_scr_pix1, int dist_hex_pix1)
{
    Curr_num_elem = Curr_num_elem1;
    Weight_coef = Weight_coef1;
    Button_pos = Button_pos1;
    size_x_pix = size_x_pix1;
    size_z_pix = size_z_pix1;
    dist_x_pix = dist_x_pix1;
    dist_z_pix = dist_z_pix1;
    rad_circ_scr_pix = rad_circ_scr_pix1;
    dist_hex_pix = dist_hex_pix1;
}



void MainWindow::on_action_2_triggered() // Рабочие параметры системы
{
    Operating_system_parameters window;
    connect(this, &MainWindow::signal_main_to_operating_system_parameters, &window, &Operating_system_parameters::slotMainToOperatingSystemParameters);
    emit signal_main_to_operating_system_parameters(duration, pressure, receiving_freq, radiation_freq);
    connect(&window, &Operating_system_parameters::signalOperatingSystemParametersToMain, this, &MainWindow::slot_operating_system_parameters_to_main);
    window.setModal(true);
    window.exec();
}

void MainWindow::on_action_3_triggered()
{
    if (!overlay_type)
    {
        ui->action_3->setText("Вид накладки:  6-угольники");
        overlay_type = 1;
    }
    else
    {
        ui->action_3->setText("Вид накладки:  4-угольники");
        overlay_type = 0;
    }
}


void MainWindow::on_charts_action_triggered()
{
    Pattern_charts window;
    connect(this, &MainWindow::signal_main_to_charts, &window, &Pattern_charts::slotMainToCharts);
    emit signal_main_to_charts(Curr_num_elem, Weight_coef, Button_pos, k,
                               size_x, size_z, dist_x, dist_z,
                               size_x_pix, size_z_pix,
                               rad_circ_scr, dist,
                               rad_circ_scr_pix, dist_hex_pix, overlay_type);
    window.setModal(true);
    window.exec();
}

