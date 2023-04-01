#include "mainwindow.h"
#include "ui_mainwindow.h"



    //Конструктор//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Предустановленные параметры коррект элем
    q = 1;
    q1 = 0;
    freq = 15000;       // f
    deltaFreq = 30000;  // delta_f
    capacity_0 = 570; // C0
    capacity = 240;   // C
    resistance = 7.3; // R
    inductance = 460; // L

    //
    HSub = 100; // Глубина хода
    LSub = 7; // Расстояние между источником шума и антенной
    speed = 20; // Скорость хода

    //Предустановленные 4угольн элем
    sizeX = 0.05;
    sizeZ = 0.05;
    distX = 0.005;
    distZ = 0.005;

    //Предустановленные 6угольн элем
    radCircScr = 0.02;
    distHex = 0.005;

    radAnt = 0.2;
    num_row = 5;

    duration = 1;
    pressure = 1;
    radiationFreq = 20550;
    receivingFreq = 20000;
    k = radiationFreq * 2 * M_PI / 1500;


    ui->setupUi(this);
    PARAM_WINDOW_FLAG = true;
    antennaType = 0;
    ui->antennaTypeAction->setText("Тип антенны:  Амплитудная");
    overlayType = 0;
    ui->overlayAction->setText("Вид накладки:  4-угольники");
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
        ArrangementOfElements window;
        connect(this, &MainWindow::signalMainToArrange, &window, &ArrangementOfElements::slotMainToArrange);
        emit signalMainToArrange(sizeX, sizeZ,
                                    distX, distZ,
                                    radCircScr, distHex,
                                    radAnt, num_row, Max_elem, CurrNumElem,  WeightCoef, SelectedElem,
                                    antennaType, overlayType);
        connect(&window, &ArrangementOfElements::signalArrangeToMain, this, &MainWindow::slotArrangeToMain);
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
    for (int i = 0; i < 17; i++)
    {
        WeightCoef[i].resize(num_row);
        for (int j = 0; j < num_row; j++)
            WeightCoef[i][j].resize(Max_elem[j]);
    }
    for (int k = 0; k < 17; k++)
    {
        for (int i = 0; i < WeightCoef[k].size(); i++)
        {
            for (int j = 0; j < WeightCoef[k][i].size(); j++)
                WeightCoef[k][i][j] = 1;
        }
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
    for (int k = 0; k < 17; k++)
    {
        WeightCoef[k].resize(num_row);
        for (int i = 0; i < num_row; i++)
            WeightCoef[k][i].resize(Max_elem[i]);
        for (int i = 0; i < WeightCoef[k].size(); i++)
        {
            for (int j = 0; j < WeightCoef[k][i].size(); j++)
                WeightCoef[k][i][j] = 1;
        }
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

void MainWindow::slotArrangeToMain(QVector<int> Curr_num_elem1, std::array<QVector<QVector<double>>, 17> Weight_coef1, QVector<QVector<std::tuple<int, int, int> > > Button_pos1,
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

// Расчет эквивалентных параметров
void MainWindow::slot_selectionOfCorrectiveElementsToMain_calculate(double qSlot, double q1Slot, double f,
                                                                    double delta_f, double C0, double C,
                                                                    double R, double L)
{

    double f0 = f - delta_f / 2.0;
    double f1 = f + delta_f / 2.0;
    double w_r = f0;
    if(w_r == 0)
        w_r += 1;

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
        bool fl = false;
        if(w == 0)
        {
            w += 1;
            fl = true;
        }
        if (k0Fn(w)>abs_k0Max)
        {
            abs_k0Max = k0Fn(w);
            w_r = w;
        }
        if (fl)
            w -= 1;
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
    QVector<double> w_ar;
    for (double w = f0 * 2; w < f1; w += delta_f / 100.0)
    {
        bool fl = false;
        if(w == 0)
        {
            w += 1;
            fl = true;
        }

        abs_K.push_back(round(20*log10(kFn(w)/k0Fn(w_r)) * 100)/100);
        abs_K0.push_back(round(20*log10(k0Fn(w)/k0Fn(w_r)) * 100)/100);
        if (fl)
            w -= 1;
        w_ar.push_back(w);
    }
    qDebug() << w_ar <<Qt::endl;
    qDebug() << abs_K <<Qt::endl;
    qDebug() << abs_K0 <<Qt::endl;
    qDebug() << k0Fn(w_r) <<Qt::endl;
    qDebug() << w_r <<Qt::endl;
    qDebug() << abs_k0Max <<Qt::endl;
}





void MainWindow::on_action_2_triggered() // Рабочие параметры системы
{
    OperatingSystemParameters window;
    connect(this, &MainWindow::signalMainToOperatingSystemParameters, &window, &OperatingSystemParameters::slotMainToOperatingSystemParameters);
    emit signalMainToOperatingSystemParameters(duration, pressure, receivingFreq, radiationFreq);
    connect(&window, &OperatingSystemParameters::signalOperatingSystemParametersToMain, this, &MainWindow::slotOperatingSystemParametersToMain);
    window.setModal(true);
    window.exec();
}

void MainWindow::on_overlayAction_triggered()
{
    if (!overlayType)
    {
        ui->overlayAction->setText("Вид накладки:  6-угольники");
        overlayType = 1;
    }
    else
    {
        ui->overlayAction->setText("Вид накладки:  4-угольники");
        overlayType = 0;
    }
}

void MainWindow::on_antennaTypeAction_triggered()
{
    if (!antennaType)
    {
        ui->antennaTypeAction->setText("Тип антенны:  Фазовая");
        antennaType = 1;
    }
    else
    {
        ui->antennaTypeAction->setText("Тип антенны:  Амплитудная");
        antennaType = 0;
    }
}

void MainWindow::on_charts_action_triggered()
{
    PatternCharts window;
    connect(this, &MainWindow::signalMainToCharts, &window, &PatternCharts::slotMainToCharts);
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
    SelectionOfCorrectiveElements window;
    connect(this, &MainWindow::signal_mainToSelectionOfCorrectiveElements, &window, &SelectionOfCorrectiveElements::slot_mainToSelectionOfCorrectiveElements);
    emit signal_mainToSelectionOfCorrectiveElements(q, q1, freq, deltaFreq, capacity_0,
                                                    capacity, resistance, inductance);
    connect(&window, &SelectionOfCorrectiveElements::signal_selectionOfCorrectiveElementsToMain_save, this, &MainWindow::slot_selectionOfCorrectiveElementsToMain_save);
    connect(&window, &SelectionOfCorrectiveElements::signal_selectionOfCorrectiveElementsToMain_calculate, this, &MainWindow::slot_selectionOfCorrectiveElementsToMain_calculate);
    window.setModal(true);
    window.exec();
}





void MainWindow::on_elemTurbulentInterf_triggered()
{
    /*
    int quantityElem = 0;
    for (int i = 0; i < ButtonPos.size(); i++)
    {
       quantityElem += ButtonPos[i].size();
    }
    double S;
    if (overlayType == 0) // прямоугольники
        S = sizeX*sizeZ;
    else
        S = 3/2*sqrt(3)*pow(radCircScr,2);
    double q = 1.0;
    ElemetTurbPower.resize(ButtonPos.size()*ButtonPos.size());
    for (int i = 0; i < ButtonPos.size(); i++)
    {
        for (int j = 0; j < ButtonPos[i].size(); j++)
        {
           ElemetTurbPower[i+j] = q * radAnt / (4*pi*pow(S, 2));
        }
    }*/
}


void MainWindow::on_powerDiffuseInterf_triggered()
{
    /*
    double R2 = Hpa / abs(cos(THETA));
    auto Hd = [R2] (R, f)
    {
        1/R2 * pow(10, -0.1*beta(f)*R);
    }
    double R1 = Hpa / cos(THETA0);

    */
}


void MainWindow::on_workingEnvironmentSettingsAction_triggered()
{
    WorkingEnvironmentSettings window;
    connect(this, &MainWindow::signal_mainToWorkingEnvironmentSettings, &window, &WorkingEnvironmentSettings::slot_mainToWorkingEnvironmentSettings);
    emit signal_mainToWorkingEnvironmentSettings();
    connect(&window, &WorkingEnvironmentSettings::signal_workingEnvironmentSettingsToMain, this, &MainWindow::slot_workingEnvironmentSettingsToMain);
    window.setModal(true);
    window.exec();

}

void MainWindow::slot_workingEnvironmentSettingsToMain()
{

}



void MainWindow::on_carrierParametersAction_triggered()
{
    CarrierParameters window;
    connect(this, &MainWindow::signal_mainToCarrierParameters, &window, &CarrierParameters::slot_mainToCarrierParameters);
    emit signal_mainToCarrierParameters(HSub, LSub, speed);
    connect(&window, &CarrierParameters::signal_carrierParametersToMain, this, &MainWindow::slot_carrierParametersToMain);
    window.setModal(true);
    window.exec();
}

void MainWindow::slot_carrierParametersToMain(double HSub1, double LSub1, double speed1)
{
    HSub = HSub1;
    LSub = LSub1;
    speed = speed1;
}
