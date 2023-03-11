#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "operatingSystemParameters.h"
#include "arrangementOfElements.h"
#include "antennaArrayParametersRect.h"
#include "antennaArrayParametersHex.h"
#include "selectionOfCorrectiveElements.h"
#include "patternCharts.h"
#include <QMessageBox>
#include <QDebug>


    //Конструктор//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    q = 0;
    q1 = 0;
    freq = 0;       // f
    deltaFreq = 0;  // delta_f
    capacity_0 = 0; // C0
    capacity = 0;   // C
    resistance = 0; // R
    inductance = 0; // L

    ui->setupUi(this);
    PARAM_WINDOW_FLAG = false;
    overlayType = 0;
    ui->action_3->setText("Вид накладки:  4-угольники");
    duration = 1;
    pressure = 1;
    radiationFreq = 20550;
    receivingFreq = 20000;
    k = radiationFreq * 2 * M_PI / 1500;
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
        connect(this, &MainWindow::signalMainToArrange, &window, &Arrangement_of_elements::slotMainToArrange);
        emit signalMainToArrange(sizeX, sizeZ,
                                    distX, distZ,
                                    radCircScr, distHex,
                                    radAnt, num_row, Max_elem, CurrNumElem,  WeightCoef, SelectedElem,
                                    overlayType);
        connect(&window, &Arrangement_of_elements::signalArrangeToMain, this, &MainWindow::slotArrangeToMain);
        window.setModal(true);
        window.exec();
    }
}


void MainWindow::on_antenna_array_triggered()
{
    if (!overlayType)
    {
        AntennaArrayParametersRect window;
        connect(this, &MainWindow::signalMainToParamRect, &window, &AntennaArrayParametersRect::slotMainToParamRect);
        if (PARAM_WINDOW_FLAG)
            emit signalMainToParamRect(sizeX, sizeZ, distX,
                                      distZ, radAnt, num_row);
        connect(&window, &AntennaArrayParametersRect::signalParamRectToMain, this, &MainWindow::slotParamRectToMain);
        window.setModal(true);
        window.exec();
    }
    else if (overlayType)
    {
        AntennaArrayParametersHex window;
        connect(this, &MainWindow::signalMainToParamHex, &window, &AntennaArrayParametersHex::slotMainToParamHex);
        if (PARAM_WINDOW_FLAG)
            emit signalMainToParamHex(radCircScr, distHex,
                                      radAnt, num_row);
        connect(&window, &AntennaArrayParametersHex::signalParamHexToMain, this, &MainWindow::slotParamHexToMain);
        window.setModal(true);
        window.exec();

    }
}


void MainWindow::on_exit_action_triggered()
{
    QApplication::exit();
}

    //Слот param to main
void MainWindow::slotParamRectToMain(double size_x1, double size_z1,
                      double dist_x1, double dist_z1,
                      double rad_ant1, int num_row1, QVector<int> Max_elem1)
{
    sizeX = size_x1; sizeZ = size_z1; distX = dist_x1;
    distZ = dist_z1; radAnt = rad_ant1; num_row = num_row1;
    PARAM_WINDOW_FLAG = true; Max_elem = Max_elem1;
    CurrNumElem = Max_elem1;
    WeightCoef.resize(num_row);
    for (int i = 0; i < num_row; i++)
        WeightCoef[i].resize(Max_elem[i]);
    for (int i = 0; i < WeightCoef.size(); i++)
    {
        for (int j = 0; j < WeightCoef[i].size(); j++)
            WeightCoef[i][j] = 1;
    }
    for (unsigned int i = 0; i < SelectedElem.size(); i++)
    {
        SelectedElem[i].resize(num_row);
        for(int j = 0; j < num_row; j++ )
            SelectedElem[i][j].resize(Max_elem[j]);
    }
}

void MainWindow::slotParamHexToMain(double rad_circ_scr_1, double distHex_1, double rad_ant_1, int num_row_1, QVector<int> Max_elem_1)
{
    radCircScr = rad_circ_scr_1; distHex = distHex_1;
    radAnt = rad_ant_1; num_row = num_row_1;
    PARAM_WINDOW_FLAG = true; Max_elem = Max_elem_1;
    CurrNumElem = Max_elem_1;
    WeightCoef.resize(num_row);
    for (int i = 0; i < num_row; i++)
        WeightCoef[i].resize(Max_elem[i]);
    for (int i = 0; i < WeightCoef.size(); i++)
    {
        for (int j = 0; j < WeightCoef[i].size(); j++)
            WeightCoef[i][j] = 1;
    }
    for (unsigned int i = 0; i < SelectedElem.size(); i++)
    {
        SelectedElem[i].resize(num_row);
        for(int j = 0; j < num_row; j++ )
            SelectedElem[i][j].resize(Max_elem[j]);
    }
}

void MainWindow::slotOperatingSystemParametersToMain(int duration1, int pressure1, int receiving_freq1, int radiation_freq1)
{
    duration = duration1;
    pressure = pressure1;
    receivingFreq = receiving_freq1;
    radiationFreq = radiation_freq1;
    k = radiation_freq1 * 2 * M_PI / 1500;
    qDebug() <<"k = " << k << Qt::endl;
}

void MainWindow::slotArrangeToMain(QVector<int> Curr_num_elem1, QVector<QVector<double> > Weight_coef1, QVector<QVector<std::tuple<int, int, int> > > Button_pos1,
                                      int size_x_pix1, int size_z_pix1, int dist_x_pix1, int dist_z_pix1,
                                      int rad_circ_scr_pix1, int dist_hex_pix1)
{
    CurrNumElem = Curr_num_elem1;
    WeightCoef = Weight_coef1;
    ButtonPos = Button_pos1;
    sizeXPix = size_x_pix1;
    sizeZPix = size_z_pix1;
    distXPix = dist_x_pix1;
    distZPix = dist_z_pix1;
    radCircScrPix = rad_circ_scr_pix1;
    distHexPix = dist_hex_pix1;
}

void MainWindow::slot_selectionOfCorrectiveElementsToMain_save(double qSlot, double q1Slot, double f, double delta_f, double C0, double C, double R, double L)
{
    q = qSlot;
    q1 = q1Slot;
    freq = f;
    deltaFreq = delta_f;
    capacity_0 = C0;
    capacity = C;
    resistance = R;
    inductance = L;
}

void MainWindow::slot_selectionOfCorrectiveElementsToMain_calculate(double qSlot, double q1Slot, double f,
                                                                    double delta_f, double C0, double C,
                                                                    double R, double L)
{
    // Расчет эквивалентных параметров
    double f0 = f - delta_f / 2.0;
    double f1 = f + delta_f / 2.0;
    double w_r = f0;
    auto k0Fn = [R, C0, L, C](double w)
    {
        double b = R * w * C0;
        double X = w * L - 1 / (w * C);
        double a = 1 - X * w * C0;
        return pow(a, 2) + pow(b, 2);
    };
    double abs_k0Max = k0Fn(w_r);
    for (double w = f0; w < f1; w += delta_f / 100.0)
    {
        if (k0Fn(w)>abs_k0Max)
        {
            abs_k0Max = k0Fn(w);
            w_r = w;
        }
    }
    double abs_Z0 = 1 / (w_r * C0);
    auto kFn = [R, C0, L, C, qSlot, q1Slot, abs_Z0] (double w)
    {
        double b = R * w * C0;
        double X = w * L - 1 / (w * C);
        double a = 1 - X * w * C0;
        double A = a + 1 / (abs_Z0 * (pow(qSlot, 2) + pow(q1Slot, 2)))*(R*q1Slot + X*qSlot);
        double B = b - 1 / (abs_Z0 * (pow(qSlot, 2) + pow(q1Slot, 2)))*(R*q1Slot - X*qSlot);
        return pow(A, 2) + pow(B, 2);
    };
    for (double w = f0; w < f1; w += delta_f / 100.0)
    {
        abs_K.push_back(20*log10(kFn(w)/k0Fn(w_r)));
        abs_K0.push_back(20*log10(k0Fn(w)/k0Fn(w_r)));
    }
    qDebug() << abs_K <<Qt::endl;
    qDebug() << abs_K0 <<Qt::endl;
}



void MainWindow::on_action_2_triggered() // Рабочие параметры системы
{
    Operating_system_parameters window;
    connect(this, &MainWindow::signalMainToOperatingSystemParameters, &window, &Operating_system_parameters::slotMainToOperatingSystemParameters);
    emit signalMainToOperatingSystemParameters(duration, pressure, receivingFreq, radiationFreq);
    connect(&window, &Operating_system_parameters::signalOperatingSystemParametersToMain, this, &MainWindow::slotOperatingSystemParametersToMain);
    window.setModal(true);
    window.exec();
}

void MainWindow::on_action_3_triggered()
{
    if (!overlayType)
    {
        ui->action_3->setText("Вид накладки:  6-угольники");
        overlayType = 1;
    }
    else
    {
        ui->action_3->setText("Вид накладки:  4-угольники");
        overlayType = 0;
    }
}


void MainWindow::on_charts_action_triggered()
{
    Pattern_charts window;
    connect(this, &MainWindow::signalMainToCharts, &window, &Pattern_charts::slotMainToCharts);
    emit signalMainToCharts(CurrNumElem, WeightCoef, ButtonPos, k,
                               sizeX, sizeZ, distX, distZ,
                               sizeXPix, sizeZPix,
                               radCircScr, distHex,
                               radCircScrPix, distHexPix, overlayType);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_corrective_action_triggered()
{
    selectionOfCorrectiveElements window;
    connect(this, &MainWindow::signal_mainToSelectionOfCorrectiveElements, &window, &selectionOfCorrectiveElements::slot_mainToSelectionOfCorrectiveElements);
    emit signal_mainToSelectionOfCorrectiveElements(q, q1, freq, deltaFreq, capacity_0,
                                                    capacity, resistance, inductance);
    connect(&window, &selectionOfCorrectiveElements::signal_selectionOfCorrectiveElementsToMain_save, this, &MainWindow::slot_selectionOfCorrectiveElementsToMain_save);
    connect(&window, &selectionOfCorrectiveElements::signal_selectionOfCorrectiveElementsToMain_calculate, this, &MainWindow::slot_selectionOfCorrectiveElementsToMain_calculate);
    window.setModal(true);
    window.exec();
}

