#include "../headers/mainwindow.h"
#include "../ui_mainwindow.h"
#include "../headers/cadAMath.h"



    //Конструктор//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//![]
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
    noiseEng = 1; // Шум движителя

    //
    depthSea = 400;  // глубина моря
    windSpeed = 10;
    salinity = 32;
    tempWater = 4;
    volumeDisp = -7;
    surfReflCoef = 0.9;
    botReflCoef = 0.5;

    //Предустановленные 4угольн элем
    sizeX = 0.033;
    sizeZ = 0.033;
    distX = 0.002;
    distZ = 0.002;

    //Предустановленные 6угольн элем
    radCircScr = 0.03; // радиус описанной окружности
    distHex = 0.004;

    radAnt = 0.18;
    num_row = 8;

    impulseType = 1; // тип импульса
    pulseDuration = 50; // длительность импульса
    riseTime = 100; // длительность фронта
    pressure = 100000; // излучаемое давление
    receivingFreq = 20550; //частота приема
    radiationFreq = 20000; //частота излучения
    k = receivingFreq * 2 * M_PI / 1500;
    for (unsigned int i = 0; i < TableChannel.size(); i++)
    {
        for (unsigned int j = 0; j < TableChannel[i].size(); j++)
            TableChannel[i][j] = false;
    }

    reverbDist1 = 100;
    reverbDist2 = 5000;
    reverbDist3 = 500;
    reverbFreq1 = 100; //частота расчета1
    reverbFreq2 = 25000; //частота расчета2
    reverbFreq3 = 20550; //частота расчета3
    reverbChannel1 = 1;
    reverbChannel2 = 2;
    ReverbChecks = {true, true, true, true};
    ReverbCalc = {false, false};
    numDot = 200;
    Rekv = 10;

    echoDist1 = 100;
    echoDist2 = 5000;
    echoDist3 = 500;
    echoFreq1 = 100; //частота расчета1
    echoFreq2 = 25000; //частота расчета2
    echoFreq3 = 20550; //частота расчета3
    echoChannel = 1;
    elevationAng = 90; //угол места
    azimuthAng = 0; // азимут
    relatSpeed = 0;
    Rekv = 10;
    EchoCalc = {false, false};

    integrateOption = 1;
    integrateDot = 1000;
//![2]

    ui->setupUi(this);
    PARAM_WINDOW_FLAG = true;
    antennaType = 0;
    ui->antennaTypeAction->setText("Тип антенны:  Амплитудная");
    overlayType = 0;
    ui->overlayAction->setText("Вид накладки:  4-угольники");
    updateRawDataWindow();

    numDotEcho = 200;

    chartsChannel = 1;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateRawDataWindow()
{
    ui->antenna_Info->clear();
    if(overlayType) // 6-угольная антенна
    {
        if (antennaType)
            ui->antenna_Info->appendPlainText("Фазовая антенна");
        else
            ui->antenna_Info->appendPlainText("Амплитудная антенна");

        ui->antenna_Info->appendPlainText("Шестиугольные элементы\n");

        ui->antenna_Info->appendPlainText("Радиус, мм = " + QString::number(radAnt * 1000));
        ui->antenna_Info->appendPlainText("X, мм = " + QString::number(radCircScr * 1000));
        ui->antenna_Info->appendPlainText("зазор dX, мм = " + QString::number(distHex * 1000) + "\n");

        ui->antenna_Info->appendPlainText("частота, Гц = " + QString::number(receivingFreq));
        ui->antenna_Info->appendPlainText("k, 1/м = " + QString::number(k));
    }
    else
    {
        if (antennaType)
            ui->antenna_Info->appendPlainText("Фазовая антенна");
        else
            ui->antenna_Info->appendPlainText("Амплитудная антенна");
        ui->antenna_Info->appendPlainText("Четырехугольные элементы\n");

        ui->antenna_Info->appendPlainText("Число накладок: " + QString::number(numElem));

        ui->antenna_Info->appendPlainText("Радиус, мм = " + QString::number(radAnt * 1000));
        ui->antenna_Info->appendPlainText("X, мм = " + QString::number(sizeX * 1000));
        ui->antenna_Info->appendPlainText("зазор dX, мм = " + QString::number(distX * 1000));
        ui->antenna_Info->appendPlainText("Z, = " + QString::number(sizeZ * 1000));
        ui->antenna_Info->appendPlainText("зазор dZ, мм = " + QString::number(distZ * 1000) + "\n");

        ui->antenna_Info->appendPlainText("частота, Гц = " + QString::number(receivingFreq));
        ui->antenna_Info->appendPlainText("k, 1/м = " + QString::number(k));
    }
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
    updateRawDataWindow();
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
    updateRawDataWindow();
}

void MainWindow::slotOperatingSystemParametersToMain(int pulseDuration1, int riseTime1, int pressure1, int radiation_freq1, int receiving_freq1,  int impulseType1)
{
    impulseType = impulseType1;
    pulseDuration = pulseDuration1;
    riseTime = riseTime1;
    pressure = pressure1;
    receivingFreq = receiving_freq1;
    radiationFreq = radiation_freq1;
    k = radiation_freq1 * 2 * M_PI / 1500;
    qDebug() <<"k = " << k << Qt::endl;
    updateRawDataWindow();
}

void MainWindow::slotArrangeToMain(QVector<int> Curr_num_elem1, std::array<QVector<QVector<double>>, 17> Weight_coef1, QVector<QVector<QPair<double,double>>> Center_pos1,
                                   std::array<QPair<double, double>, 16> Centroids1, std::array<double,16> Arr_sensitivity, std::array<QVector<QVector<bool>>, 16> SelectedElem1,
                                   int numElem1)
{
    CurrNumElem = Curr_num_elem1;
    WeightCoef = Weight_coef1;
    CenterPos = Center_pos1;
    Centroids = Centroids1;
    Arr_sensitivityGroup = Arr_sensitivity;
    SelectedElem = SelectedElem1;
    updateRawDataWindow();
    numElem = numElem1;

    updateRawDataWindow();

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
    /*qDebug() << w_ar <<Qt::endl;
    qDebug() << abs_K <<Qt::endl;
    qDebug() << abs_K0 <<Qt::endl;
    qDebug() << k0Fn(w_r) <<Qt::endl;
    qDebug() << w_r <<Qt::endl;
    qDebug() << abs_k0Max <<Qt::endl;
    */
}





void MainWindow::on_action_2_triggered() // Рабочие параметры системы
{
    OperatingSystemParameters window;
    connect(this, &MainWindow::signalMainToOperatingSystemParameters, &window, &OperatingSystemParameters::slotMainToOperatingSystemParameters);
    emit signalMainToOperatingSystemParameters(pulseDuration, riseTime, pressure, radiationFreq, receivingFreq, impulseType);
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
    updateRawDataWindow();
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
    updateRawDataWindow();
}

void MainWindow::on_charts_action_triggered()
{
    PatternCharts window;
    connect(this, &MainWindow::signalMainToCharts, &window, &PatternCharts::slotMainToCharts);
    emit signalMainToCharts(CurrNumElem, WeightCoef, CenterPos, k,
                               sizeX, sizeZ, distX, distZ,
                               radCircScr, distHex, overlayType,
                            VecSurfFreq, VecSurfDist, VecBotFreq, VecBotDist,
                            VecSurrFreq, VecSurrDist, VecSumFreq, VecSumDist,
                            ReverbChecks, ReverbCalc, VecFreq, VecDist,
                            VecFreqE, VecEchoFreq, VecDistE, VecEchoDist,
                            EchoCalc,
                            TableChannel, Arr_sensitivityGroup, SubarrayCenter, SelectedElem, Centroids, antennaType,
                            chartsChannel);
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

double MainWindow::D(double theta, double phi)
{
    if (overlayType == 0) // Четырехугольник
    {
        double a;
        if (phi != 0)
           a = sin( k * (sizeX+distX) / 2 * sin(theta) * sin (phi) )/ (k*(sizeX+distX) / 2.0 * (sin(theta) * sin (phi)));
        else
           a = 1;
        double b = sin ( k * (sizeZ+distZ) / 2 * cos (theta)) / (k * (sizeZ+distZ) / 2.0 * cos (theta));
        return a * b;
    }
    else if (overlayType != 0)  // Шестиугольник
    {
        double a1,b1;
        if (phi != 0)
        {
            a1 = 2 * j1(k * (sqrt(3)*radCircScr+distHex)/2 * sqrt(pow(sin(theta)*sin(phi), 2)+pow(cos(theta), 2)));
            b1 = k * (sqrt(3)*radCircScr+distHex)/2 * sqrt(pow(sin(theta) * sin(phi), 2) + pow(cos(theta), 2));
            return a1/b1;
        }

    }
    return 1;
}



double MainWindow::g(double f1) // спектр мощности излучаемого сигнала на частоте f;
{
    double f = f1 / 1000.0;
    double ps = pressure; // излучаемое давление
    double fs = radiationFreq / 1000.0; // частота излучения
    double ts = pulseDuration / 1000.0; // длительность имульса
    double tf = riseTime / 1000.0; // длительность фронта
    double g1 = 0;
    switch (impulseType)
    {
        case 1:
            g1 = sin(M_PI * (f - fs) * ts) / (M_PI * (f - fs) * ts) *
                (ps * sqrt(2.0)) * ts / 2.0;
            break;
        case 2:
            g1 = sin (M_PI * (f - fs) * (ts - tf)) / (M_PI * (f - fs) * (ts - tf)) *
                sin(M_PI * (f - fs) * ts) / (M_PI * (f - fs) * ts) *
                (ps * sqrt(2.0)) * (ts - tf) / 2.0;
            break;
        case 3:
            g1 = ps * sqrt(2.0);
            break;
        default:
            break;
    }
    return abs(g1);
}


std::complex<double> MainWindow::DLt(double theta, double phi, int chn) //диаграмма направленности канала
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); // Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0;
    for (int grp = 0; grp < 16; grp++)
    {
        D_numerator += TableChannel[chn][grp] * Arr_sensitivityGroup[grp] *
                exp((1.0*i) * k * (SubarrayCenter[chn].first * (sin(theta) * sin (phi) - sin(theta_t) * sin(phi_t)) +
                                   SubarrayCenter[chn].second * (cos(theta) - cos (theta_t)) ) * DUt(theta, phi, grp));
        D_denumerator += TableChannel[chn][grp] * Arr_sensitivityGroup[grp];
    }
    return D_numerator / D_denumerator;
}


std::complex<double> MainWindow::DUt(double theta, double phi, int grp) //диаграмма направленности группы
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); // Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0;
    for (int a = 0; a < CenterPos.size(); a++)
    {
        for(int b = 0; b < CenterPos[a].size(); b++)
        {
                //[1] Числитель
                D_numerator += (WeightCoef[grp][a][b]* SelectedElem[grp][a][b]* exp( (1.0*i) * k * ((CenterPos[a][b].first - Centroids[grp].first ) * ( sin(theta)*sin(phi) - sin(theta_t)*sin(phi_t) )
                                                   + (CenterPos[a][b].second - Centroids[grp].second) * (cos (theta) - cos(theta_t))) ) *
                         D(theta_t, phi_t) * ( 1.0 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0 );
                //[2] Знаменатель
                D_denumerator += WeightCoef[grp][a][b] * D(theta_t, phi_t) * ( 1 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0;
        }
    }
    return D_numerator / D_denumerator;
}

std::complex<double> MainWindow::Dt(double theta, double phi, int grp)
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); // Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0;
    for (int a = 0; a < CenterPos.size(); a++)
    {
        for(int b = 0; b < CenterPos[a].size(); b++)
        {
                //[1] Числитель
                D_numerator += (WeightCoef[grp][a][b] * exp( (1.0*i) * k * (CenterPos[a][b].first * ( sin(theta)*sin(phi) - sin(theta_t)*sin(phi_t) )
                                                   + CenterPos[a][b].second * (cos (theta) - cos(theta_t))) ) *
                         D(theta_t, phi_t) * ( 1.0 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0 );
                //[2] Знаменатель
                D_denumerator += WeightCoef[grp][a][b] * D(theta_t, phi_t) * ( 1 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0;
        }
    }
    return D_numerator / D_denumerator;
}



void MainWindow::on_elemTurbulentInterf_triggered()
{
    /*
    int quantityElem = 0;
    for (int i = 0; i < CenterPos.size(); i++)
    {
       quantityElem += CenterPos[i].size();
    }
    double S;
    if (overlayType == 0) // прямоугольники
        S = sizeX*sizeZ;
    else
        S = 3/2*sqrt(3)*pow(radCircScr,2);
    double q = 1.0;
    ElemetTurbPower.resize(CenterPos.size()*CenterPos.size());
    for (int i = 0; i < CenterPos.size(); i++)
    {
        for (int j = 0; j < CenterPos[i].size(); j++)
        {
           ElemetTurbPower[i+j] = q * radAnt / (4*pi*pow(S, 2));
        }
    }*/
}



//Мощность рассеянной помехи

void MainWindow::on_powerDiffuseInterf_triggered()
{
    //ui->label->setText("Идет вычисление спектра мощности рассеяной помехи");
    ui->consoleText->clear();
    int chn1 = 0;
    qDebug() << "freq" << receivingFreq;
    double Freq = receivingFreq;
    auto beta = [this] (double f1) // коэф простр затухания
    {
        double f = f1/1000;
        //return 0.036*pow(f/1000.0, 1.5); //формула Шихе-Хелли
        const double a = 8.68e3;
        const double A = 2.34e-6; // постоянная ионной релаксации
        double S = salinity;
        double T = tempWater;
        double fp = 21.9 * pow(10, 6-1520/(T+273)); // частота релаксации при атмосферном давлении, кГц
        const double B = 3.38e-6; // постоянная вязкости пресной воды
        const double b1 = 6.54e-4; // градиент изменения коэффициента затухания под влиянием статического давления
        double p = HSub / 10.0; //гидростатическое давление

        return a * (A * S * fp * pow(f, 2) / (pow(fp, 2) + pow(f, 2)) + B * pow(f, 2) / fp) * (1 - b1 * p);
        // формула Шулкина-Марша
    };
    qDebug() << "beta" << beta(Freq);


    auto R2 = [this](double theta, bool isSurf) -> double
    {
        if (isSurf)
            return this->HSub / abs(cos(theta));
        else
            return (this->depthSea - this->HSub) / abs(cos(theta));
    };

    auto R1 = [this](double theta, bool isSurf) -> double
    {
        if (isSurf)
            return sqrt(pow((this->HSub *tan(theta)+this->LSub), 2)+pow(this->HSub, 2));
        else
            return sqrt(pow(((this->depthSea - this->HSub) *tan(theta)+this->LSub), 2)+pow((this->depthSea - this->HSub), 2));
    };

    auto Hd = [beta] (double R, double f) -> double
    {
        return 1/(pow(R,2)) * pow(10, -0.1*beta(f)*R*1e-3);
    };
    //[] обратное поверхностное рассеивание
    auto X = [this](double theta, double phi, double theta_0, double phi_0)
    {
        return pow(k, 2) * ( pow(sin(theta), 2) + pow(sin(theta_0), 2) - 2 * sin(theta) * sin (theta_0) * cos(phi - phi_0));
    };

    auto q = [this] (double theta, double theta_0)
    {
        return k * (cos(theta) + cos(theta_0));
    };

    auto ms = [X, q, this] (double theta, double phi)
    {
        double theta_0 = M_PI_2, phi_0 = 0;
        double delta2 = 0.001 * (3 + 5.12 * windSpeed);
        return 4 * (1 / 2.0 *(1 + pow(X(theta, phi, theta_0, phi_0), 2) / pow (q(theta, theta_0), 2)))
                * exp(-1*pow(X(theta, phi, theta_0, phi_0), 2) / (2 * delta2 * pow(q(theta, theta_0), 2)));
    };
    //[]
    auto mb = [] (double theta)
    {
        double m = 1.56;
        double n = 1.008;
        double num = m * cos(theta) - sqrt(pow(n, 2) - pow(sin(theta), 2));
        double denum = m * cos(theta) + sqrt(pow(n, 2) - pow(sin(theta), 2));
        return num / denum;
    };
    //[]
    auto Ps_unint = [Freq, Hd, R1, R2, beta, ms, chn1, this] (double phi, double theta) -> std::complex<double>
    {
        double r1 = R1(theta, true);
        double r2 = R2(theta, true);
        std::complex<double> D_t = Dt(theta, phi, chn1);
        return pow(this->noiseEng, 2) * pow(D_t, 2) * Hd(r1, Freq) * Hd(r2, Freq) *
                ms(theta, phi) * pow(this->HSub, 2) *sin(theta) / pow(cos(theta), 3);
    };
    auto Pb_unint = [Freq, Hd, R1, R2, beta, mb, chn1, this] (double phi, double theta) -> std::complex<double>
    {
        double r1 = R1(theta, false);
        double r2 = R2(theta, false);
        std::complex<double> D_t = Dt(theta, phi, chn1);
        return pow(this->noiseEng, 2) * pow(D_t, 2) * Hd(r1, Freq) * Hd(r2, Freq) *
                mb(theta) * pow(this->depthSea - this->HSub, 2)*sin(theta) / abs(pow(cos(theta), 3));
    };

    auto Ps_unint_ph = [Freq, Hd, R1, R2, beta, ms, chn1, this] (double phi, double theta) -> std::complex<double>
    {
        double r1 = R1(theta, true);
        double r2 = R2(theta, true);
        std::complex<double> D_t = DLt(theta, phi, chn1);
        return pow(this->noiseEng, 2) * pow(D_t, 2) * Hd(r1, Freq) * Hd(r2, Freq) *
                ms(theta, phi) * pow(this->HSub, 2) *sin(theta) / pow(cos(theta), 3);
    };
    auto Pb_unint_ph = [Freq, Hd, R1, R2, beta, mb, chn1, this] (double phi, double theta) -> std::complex<double>
    {
        double r1 = R1(theta, false);
        double r2 = R2(theta, false);
        std::complex<double> D_t = DLt(theta, phi, chn1);
        return pow(this->noiseEng, 2) * pow(D_t, 2) * Hd(r1, Freq) * Hd(r2, Freq) *
                mb(theta) * pow(this->depthSea - this->HSub, 2)*sin(theta) / abs(pow(cos(theta), 3));
    };


    if (!antennaType)
    {
        QElapsedTimer timer;
        timer.start();
        chn1 = 0;
        auto Psurf = integrate2(Ps_unint, 0.0, M_PI_2, -M_PI_2, M_PI_2, integrateDot);
        qDebug() << "Поверхность:"<<abs(Psurf)<<Qt::endl;
        auto Pbot = integrate2(Pb_unint, M_PI_2, M_PI, -M_PI_2, M_PI_2, integrateDot);
        qDebug() << "Дно:"<<abs(Pbot)<<Qt::endl;
        qint64 elapsed = timer.elapsed();
        qDebug() <<"Elapsed time:"<<elapsed<<"ms";


        qDebug() <<"плотность мощности рассеянной помехи";
        qDebug() <<"Elapsed time:"<<elapsed<<"ms";
        qDebug() << "Поверхность:"<<abs(Psurf)<<Qt::endl;
        ui->consoleText->appendPlainText("Канал  Поверхность     Дно             Сумма\n");
        ui->consoleText->appendPlainText(QString::number(1) + "          "
                                         + QString::number(abs(Psurf), 'e', 2) + "            "
                                         + QString::number(abs(Pbot), 'e', 2) + "      "
                                         + QString::number(abs(Pbot) + abs(Psurf), 'e', 2) + "\n");

    }
    else
    {
        qDebug() <<"плотность мощности рассеянной помехи";
        QElapsedTimer timer;
        timer.start();
        for (int chn1 = 0; chn1 < 30; chn1++)
        {
            if (!checkChannel(chn1))
                    continue;
            qDebug() <<"плотность мощности рассеянной помехи";
            auto Psurf = integrate2(Ps_unint_ph, 0.0, M_PI_2, -M_PI_2, M_PI_2, integrateDot);
            qDebug() << "Поверхность:"<<abs(Psurf)<<Qt::endl;
            auto Pbot = integrate2(Pb_unint_ph, M_PI_2, M_PI, -M_PI_2, M_PI_2, integrateDot);
            qDebug() << "Дно:"<<abs(Pbot)<<Qt::endl;
            qint64 elapsed = timer.elapsed();
            qDebug() <<"Elapsed time:"<<elapsed<<"ms";

            ui->consoleText->appendPlainText("Канал  Поверхность     Дно             Сумма\n");
            ui->consoleText->appendPlainText(QString::number(chn1 + 1) + "          "
                                             + QString::number(abs(Psurf), 'e', 2) + "            "
                                             + QString::number(abs(Pbot), 'e', 2) + "      "
                                             + QString::number(abs(Pbot) + abs(Psurf), 'e', 2) + "\n");

        }
        qint64 elapsed = timer.elapsed();
        qDebug() <<"Elapsed time:"<<elapsed<<"ms";
        qDebug() <<"Вычисления выполнены";
        ui->label->setText("Вычисления выполнены");
    }
}


void MainWindow::on_workingEnvironmentSettingsAction_triggered()
{
    WorkingEnvironmentSettings window;
    connect(this, &MainWindow::signal_mainToWorkingEnvironmentSettings, &window, &WorkingEnvironmentSettings::slot_mainToWorkingEnvironmentSettings);
    emit signal_mainToWorkingEnvironmentSettings(depthSea, windSpeed, salinity, tempWater,
                                                 volumeDisp, surfReflCoef, botReflCoef);
    connect(&window, &WorkingEnvironmentSettings::signal_workingEnvironmentSettingsToMain, this, &MainWindow::slot_workingEnvironmentSettingsToMain);
    window.setModal(true);
    window.exec();

}

void MainWindow::slot_workingEnvironmentSettingsToMain(double depthSea1, double windSpeed1,
                                                       double salinity1, double tempWater1,
                                                       double volumeDisp1,
                                                       double surfReflCoef1, double botReflCoef1
                                                       )
{
    depthSea = depthSea1;
    windSpeed = windSpeed1;
    salinity = salinity1;
    tempWater = tempWater1;
    volumeDisp = volumeDisp1;
    surfReflCoef = surfReflCoef1;
    botReflCoef = botReflCoef1;
}



void MainWindow::on_carrierParametersAction_triggered()
{
    CarrierParameters window;
    connect(this, &MainWindow::signal_mainToCarrierParameters, &window, &CarrierParameters::slot_mainToCarrierParameters);
    emit signal_mainToCarrierParameters(HSub, LSub, speed, noiseEng);
    connect(&window, &CarrierParameters::signal_carrierParametersToMain, this, &MainWindow::slot_carrierParametersToMain);
    window.setModal(true);
    window.exec();
}

void MainWindow::slot_carrierParametersToMain(double HSub1, double LSub1, double speed1, double noiseEng1)
{
    HSub = HSub1;
    LSub = LSub1;
    speed = speed1;
    noiseEng = noiseEng1;
}

void MainWindow::slot_channelParametersToMain(std::array<std::array<bool, 16>, 30> Table)
{
    for (unsigned int i = 0; i < TableChannel.size(); i++)
    {
        for (unsigned int j = 0; j < TableChannel[i].size(); j++)
            TableChannel[i][j] = Table[i][j];
    }

    for (int chn = 0; chn < 30; chn++)
    {
        double Z_CL_num = 0, Y_CL_num = 0;
        int Denum = 0;
        for (int grp = 0; grp < 16; grp++)
        {
            if(!TableChannel[chn][grp])
                continue;
            Z_CL_num += Centroids[grp].first * Arr_sensitivityGroup[grp];
            Y_CL_num += Centroids[grp].second  * Arr_sensitivityGroup[grp];
            Denum += Arr_sensitivityGroup[grp];
        }
        if (Denum > 0)
        {
            // координаты центра канала
            SubarrayCenter[chn].second = Z_CL_num / Denum;
            SubarrayCenter[chn].first = Y_CL_num / Denum;
        }
    }
    //debug
    qDebug() << "channels";
    for (int chn = 0; chn < 30; chn++)
    {
        qDebug() << SubarrayCenter[chn].first << SubarrayCenter[chn].second;
    }
    updateRawDataWindow();

}


void MainWindow::on_paramChanelAction_triggered()
{
    if(antennaType == 1) // фазовая антенна
    {
        ChannelParameters window;
        connect(this, &MainWindow::signal_mainToChannelParameters, &window, &ChannelParameters::slot_mainToChannelParameters);
        emit signal_mainToChannelParameters(TableChannel);
        connect(&window, &ChannelParameters::signal_channelParametersToMain, this, &MainWindow::slot_channelParametersToMain);
        window.setModal(true);
        window.exec();
    }
}


void MainWindow::powerSurfReverb(int typeRev)
{
    auto beta = [this] (double f1) // коэф простр затухания
    {
        double f = f1/1000;
        return 0.036*pow(f, 1.5); //формула Шихе-Хелли
        /*
        const double a = 8.68e3;
        const double A = 2.34e-6; // постоянная ионной релаксации
        double S = salinity;
        double T = tempWater;
        double fp = 21.9 * pow(10, 6-1520/(T+273)); // частота релаксации при атмосферном давлении, кГц
        const double B = 3.38e-6; // постоянная вязкости пресной воды
        const double b1 = 6.54e-4; // градиент изменения коэффициента затухания под влиянием статического давления
        double p = HSub / 10.0; //гидростатическое давление

        return a * (A * S * fp * pow(f, 2) / (pow(fp, 2) + pow(f, 2)) + B * pow(f, 2) / fp) * (1 - b1 * p);
        // формула Шулкина-Марша
        */
    };
    auto D = [this] (double R)
    {
        return sqrt(pow(R, 2) + pow (HSub, 2));
    };

    auto Hd = [beta, this] (double D, double f) -> double
    {
        return 1/(pow(D,2)) * pow(10, -0.1*beta(f)*D*1e-3) * g(f) * Rekv;
    };
    if (typeRev == 1) //частотная
    {
        VecFreq.clear();
        VecSurfFreq.clear();
        double dist = reverbDist3;
        for(double FRev = reverbFreq1; FRev < reverbFreq2; FRev += (reverbFreq2 - reverbFreq1) / numDot)
        {
            VecFreq.push_back(FRev);
            qDebug() << "g(f)" << g(FRev);
            double H_d = Hd(D(dist), FRev);
            VecSurfFreq.push_back(H_d);
        }
        qDebug() << "VecSurfFreq" << VecSurfFreq;
    }
    if (typeRev == 2)  //временная
    {
        VecDist.clear();
        VecSurfDist.clear();
        double frequency = reverbFreq3;
        for(double DRev = reverbDist1; DRev < reverbDist2; DRev += (reverbDist2 - reverbDist1) / double(numDot))
        {
            VecDist.push_back(DRev);
            double H_d = Hd(D(DRev), frequency);
            VecSurfDist.push_back(H_d);
        }
    }
}


void MainWindow::powerBotReverb(int type)
{
    auto beta = [this] (double f1) // коэф простр затухания
    {
        double f = f1/1000;
        return 0.036*pow(f, 1.5); //формула Шихе-Хелли
        /*
        const double a = 8.68e3;
        const double A = 2.34e-6; // постоянная ионной релаксации
        double S = salinity;
        double T = tempWater;
        double fp = 21.9 * pow(10, 6-1520/(T+273)); // частота релаксации при атмосферном давлении, кГц
        const double B = 3.38e-6; // постоянная вязкости пресной воды
        const double b1 = 6.54e-4; // градиент изменения коэффициента затухания под влиянием статического давления
        double p = HSub / 10.0; //гидростатическое давление

        return a * (A * S * fp * pow(f, 2) / (pow(fp, 2) + pow(f, 2)) + B * pow(f, 2) / fp) * (1 - b1 * p);
        // формула Шулкина-Марша
        */
    };

    auto D = [this] (double R)
    {
        return sqrt(pow(R, 2) + pow (depthSea - HSub, 2));
    };
    auto Hd = [beta, this] (double D, double f) -> double
    {
        return 1/(pow(D,2)) * pow(10, -0.1*beta(f)*D*1e-3) * g(f) * Rekv;
    };

    if (type == 1) //частотная
    {
        VecFreq.clear();
        VecBotFreq.clear();
        double dist = reverbDist3;
        for(double FRev = reverbFreq1; FRev < reverbFreq2; FRev += (reverbFreq2 - reverbFreq1) / numDot)
        {
            VecFreq.push_back(FRev);
            double H_d = Hd(D(dist), FRev);
            VecBotFreq.push_back(H_d);
        }
    }
    if (type == 2)  //временная
    {
        VecDist.clear();
        VecBotDist.clear();
        double frequency = reverbFreq3;
        for(double DRev = reverbDist1; DRev < reverbDist2; DRev += (reverbDist2 - reverbDist1) / numDot)
        {
            VecDist.push_back(DRev);
            double H_d = Hd(D(DRev), frequency) * g(frequency);
            VecBotDist.push_back(H_d);
        }
    }
}

void MainWindow::powerSurroundReverb(int type)
{
    auto beta = [this] (double f1) // коэф простр затухания
    {
        double f = f1/1000;
        return 0.036*pow(f, 1.5); //формула Шихе-Хелли
        /*
        const double a = 8.68e3;
        const double A = 2.34e-6; // постоянная ионной релаксации
        double S = salinity;
        double T = tempWater;
        double fp = 21.9 * pow(10, 6-1520/(T+273)); // частота релаксации при атмосферном давлении, кГц
        const double B = 3.38e-6; // постоянная вязкости пресной воды
        const double b1 = 6.54e-4; // градиент изменения коэффициента затухания под влиянием статического давления
        double p = HSub / 10.0; //гидростатическое давление

        return a * (A * S * fp * pow(f, 2) / (pow(fp, 2) + pow(f, 2)) + B * pow(f, 2) / fp) * (1 - b1 * p);
        // формула Шулкина-Марша
        */
    };

    auto D = [this] (double R)
    {
        return sqrt(pow(R, 2) + pow (R - HSub, 2));
    };
    auto Hd = [beta, this] (double D, double f) -> double
    {
        return 1/(pow(D,2)) * pow(10, -0.1*beta(f)*D*1e-3)* g(f) * Rekv;
    };

    if (type == 1) //частотная
    {
        VecSurrFreq.clear();
        VecFreq.clear();
        double dist = reverbDist3;
        for(double FRev = reverbFreq1; FRev < reverbFreq2; FRev += (reverbFreq2 - reverbFreq1) / numDot)
        {
            VecFreq.push_back(FRev);
            double H_d1 = Hd(D(dist), FRev);
            VecSurrFreq.push_back(H_d1);
        }
    }
    if (type == 2)  //временная
    {
        VecSurrDist.clear();
        VecDist.clear();
        double frequency = reverbFreq3;
        for(double DReverb = reverbDist1; DReverb < reverbDist2; DReverb += (reverbDist2 - reverbDist1) / numDot)
        {
            VecDist.push_back(DReverb);
            double H_d2 = Hd(D(DReverb), frequency);
            VecSurrDist.push_back(H_d2);
        }
    }
}

void MainWindow::powerSumReverb(int type)
{
    if (type == 1) //частотная
    {
        VecSumFreq.clear();
        for(int num = 0; num < m_cadAMath.maxOfThree(VecSurfFreq.size(), VecBotFreq.size(), VecSurrFreq.size()); num++)
        {
            double sum = 0;
            if (ReverbChecks[0]) //поверхностная реверберация
            {
                sum += VecSurfFreq[num];
            }

            if (ReverbChecks[1]) //донная реверберация
            {
                sum += VecBotFreq[num];
            }
            else

            if (ReverbChecks[2]) //объемная реверберация
            {
                sum += VecSurrFreq[num];
            }

            VecSumFreq.push_back(sum);
        }
    }
    else if (type == 2)  //временная
    {
        VecSumDist.clear();
        for(int num = 0; num < m_cadAMath.maxOfThree(VecSurfDist.size(), VecBotDist.size(), VecSurrDist.size()); num++)
        {
            double sum = 0;
            if (ReverbChecks[0]) //поверхностная реверберация
            {
                sum += VecSurfDist[num];
            }


            if (ReverbChecks[1]) //донная реверберация
            {
                sum += VecBotDist[num];
            }
            else

            if (ReverbChecks[2]) //объемная реверберация
            {
                sum += VecSurrDist[num];
            }

            VecSumDist.push_back(sum);
        }
    }



}

bool MainWindow::checkChannel(int i)
{
    int sum = 0;
    for (unsigned int j = 0; j < TableChannel[i].size(); j++)
        sum += TableChannel[i][j];
    return sum;
}


void MainWindow::slot_reverberationParametersToMain1(double param1, double param2, double param3, int channel1, int numDot1,
                                                     std::array<bool, 4> ReverbChecks1, int typeReverb, bool isCalculate)
{
    ReverbChecks = ReverbChecks1;
    numDot = numDot1;
    reverbChannel1 = channel1;
    if (isCalculate)
    {
        switch (typeReverb) {
        case 1: //частотная
            ReverbCalc[0] = true;
            reverbFreq1 = param1;
            reverbFreq2 = param2;
            reverbDist3 = param3;

            break;
        case 2: //временная
            ReverbCalc[1] = true;
            reverbFreq3 = param1;
            reverbDist1 = param2;
            reverbDist2 = param3;

            break;
        default:
            break;
        }
        if (ReverbChecks[0]) //поверхностная реверберация
        {
            powerSurfReverb(typeReverb);
        }

        if (ReverbChecks[1]) //поверхностная реверберация
        {
            powerBotReverb(typeReverb);
        }

        if (ReverbChecks[2]) //поверхностная реверберация
        {
            powerSurroundReverb(typeReverb);
        }

        if (ReverbChecks[3]) //поверхностная реверберация
        {
            powerSumReverb(typeReverb);
        }
    }
    else
    {
        switch (typeReverb) {
        case 1: //частотная
            reverbFreq1 = param1;
            reverbFreq2 = param2;
            reverbDist3 = param3;
            numDot = numDot1;
            reverbChannel1 = channel1;

            break;
        case 2: //временная
            reverbFreq3 = param1;
            reverbDist1 = param2;
            reverbDist2 = param3;
            numDot = numDot1;
            reverbChannel1 = channel1;
            break;
        default:
            break;
        }
    }
}

void MainWindow::slot_reverberationParametersToMain2(double param1, double param2, double param3, int channel1, int channel2, int numDot,
                                                     std::array<bool, 4> ReverbChecks1,  int typeReverb, bool isCalculate)
{

}



void MainWindow::on_actionRevervPowFreq_triggered() //Реверберационная->мощности->частотная
{
    ReverberationParameters window;
    connect(this, &MainWindow::signal_mainToReverberationParameters1, &window, &ReverberationParameters::slot_mainToReverberationParameters1);
    emit signal_mainToReverberationParameters1(reverbFreq1, reverbFreq2, reverbDist3, reverbChannel1, numDot, ReverbChecks, 1);
    connect(&window, &ReverberationParameters::signal_reverberationParametersToMain1, this, &MainWindow::slot_reverberationParametersToMain1);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_actionRevervPowTime_triggered() //Реверберационная->мощности->временная
{
    ReverberationParameters window;
    connect(this, &MainWindow::signal_mainToReverberationParameters1, &window, &ReverberationParameters::slot_mainToReverberationParameters1);
    emit signal_mainToReverberationParameters1(reverbFreq3, reverbDist1, reverbDist2, reverbChannel1, numDot, ReverbChecks, 2);
    connect(&window, &ReverberationParameters::signal_reverberationParametersToMain1, this, &MainWindow::slot_reverberationParametersToMain1);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_echoFreqAction_triggered()
{
    EchoSignal window;
    connect(this, &MainWindow::signal_mainToEchoSignal, &window, &EchoSignal::slot_mainToEchoSignal);
    emit signal_mainToEchoSignal(echoFreq1, echoFreq2, echoDist3, echoChannel, numDotEcho, 1, elevationAng, azimuthAng, relatSpeed, Rekv);
    connect(&window, &EchoSignal::signal_echoSignalToMain, this, &MainWindow::slot_echoSignalToMain);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_echoDistAction_triggered()
{
    EchoSignal window;
    connect(this, &MainWindow::signal_mainToEchoSignal, &window, &EchoSignal::slot_mainToEchoSignal);
    emit signal_mainToEchoSignal(echoDist1, echoDist2, echoFreq3, echoChannel, numDotEcho, 2, elevationAng, azimuthAng, relatSpeed, Rekv);
    connect(&window, &EchoSignal::signal_echoSignalToMain, this, &MainWindow::slot_echoSignalToMain);
    window.setModal(true);
    window.exec();
}

void MainWindow::slot_echoSignalToMain(double param1, double param2, double param3, int channel,
                                       int numDot1,  int typeEchoSign,
                                       bool isCalculate, double elevation, double azimuth,
                                       double relative_speed, double R_ekv)
{
    numDotEcho = numDot1;
    elevationAng = elevation;
    azimuthAng = azimuth;
    relatSpeed = relative_speed;
    Rekv = R_ekv;
    echoChannel = channel;
    switch (typeEchoSign) {
    case 1: //частотная
        echoFreq1 = param1;
        echoFreq2 = param2;
        echoDist3 = param3;

        break;
    case 2: //временная
        echoDist1 = param1;
        echoDist2 = param2;
        echoFreq3 = param3;
        break;
    default:
        break;
    }
    if (isCalculate)
    {
        powerEchoSignal(typeEchoSign);
    }

}

void MainWindow::slot_chartsParametersToMain(int chartsChannel1)
{
    chartsChannel = chartsChannel1;
}

void MainWindow::slot_calcParamToMain(int opt, int integDot)
{
    integrateOption = opt;
    integrateDot = integDot;
}

void MainWindow::powerEchoSignal(int type)
{
    auto K_dopl = [this] (double theta, double phi)
    {
        double const c = 1500;
        double Kd = (1 + relatSpeed * sin(theta) * cos(phi) / c) / (1 - relatSpeed * sin(theta) * cos(phi) / c);
        return Kd;
    };

    auto beta = [this] (double f1) // коэф простр затухания
    {
        double f = f1/1000;
        //return 0.036*pow(f, 1.5); //формула Шихе-Хелли

        const double a = 8.68e3;
        const double A = 2.34e-6; // постоянная ионной релаксации
        double S = salinity;
        double T = tempWater;
        double fp = 21.9 * pow(10, 6-1520/(T+273)); // частота релаксации при атмосферном давлении, кГц
        const double B = 3.38e-6; // постоянная вязкости пресной воды
        const double b1 = 6.54e-4; // градиент изменения коэффициента затухания под влиянием статического давления
        double p = HSub / 10.0; //гидростатическое давление

        return a * (A * S * fp * pow(f, 2) / (pow(fp, 2) + pow(f, 2)) + B * pow(f, 2) / fp) * (1 - b1 * p);
        // формула Шулкина-Марша
    };

    auto Hd = [beta, this] (double D, double f) -> double
    {
        return 1/(pow(D,2)) * pow(10, -0.1*beta(f)*D*1e-3);
    };

    auto P_sign = [this, Hd, K_dopl] (double f, double R, double theta, double phi)
    {
        double ts = pulseDuration / 1000.0; // длительность имульса
        std::complex<double> D_rec; // модуль нормированной диаграммы направленности приемной решетки;
        if (antennaType) // фазовая антенна
        {
            //![фазовая]
            D_rec = DLt(theta, phi, echoChannel - 1);
        }
        else if (!antennaType) // амплитудная антенна
        {
            D_rec = Dt(theta, phi, 0);
        }
        std::complex<double> D_rad = Dt(theta, phi, 16); // модуль нормированной диаграммы направленности излучающей решетки;

        double Ps = 1/ ts * abs(pow(D_rad, 2)) * abs(pow(D_rec, 2)) * 2 * pow(g(f / K_dopl(theta, phi)), 2) * pow(Hd(R, f), 2) * pow(Rekv, 2) / 4;
        return Ps;
    };


    if (type == 1) //частотная
    {
        VecFreqE.clear();
        VecEchoFreq.clear();
        double dist = echoDist3;
        for(double FEcho = echoFreq1; FEcho < echoFreq2; FEcho += (echoFreq2 - echoFreq1) / numDotEcho)
        {
            VecFreqE.push_back(FEcho);
            //![]
            double Psig = P_sign(FEcho, dist, elevationAng * M_PI / 180.0, azimuthAng * M_PI / 180.0);
            VecEchoFreq.push_back(Psig);
        }
        qDebug() << "VecEchoFreq: " << VecEchoFreq;
        EchoCalc[0] = true;
    }
    if (type == 2)  //временная
    {
        VecDistE.clear();
        VecEchoDist.clear();
        double frequency = echoFreq3;
        for(double DEcho = echoDist1; DEcho < echoDist2; DEcho += (echoDist2 - echoDist1) / numDotEcho)
        {
            VecDistE.push_back(DEcho);
            double Psig = P_sign(frequency, DEcho, elevationAng * M_PI / 180.0, azimuthAng * M_PI / 180.0);
            VecEchoDist.push_back(Psig);
        }
        qDebug() << "VecEchoDist: " << VecEchoDist;
        EchoCalc[1] = true;
    }


}

std::complex<double> MainWindow::integrate2(std::function<std::complex<double> (double, double)> f, double a1, double b1, double a2, double b2, int N)
{
    if (integrateOption == 1) // метод прямоугольников
        return m_cadAMath.rectInt2(f, a1, b1, a2, b2, N);
    if (integrateOption == 2) // метод трапеций
        return m_cadAMath.trapez2(f, a1, b1, a2, b2, N);
    if (integrateOption == 3) // метод Симпсона
        return m_cadAMath.simpson2(f, a1, b1, a2, b2, N);
    if (integrateOption == 4) // метод Монте-Карло
        return m_cadAMath.monteCarlo2(f, a1, b1, a2, b2, N);
}

void MainWindow::on_chartsParameters_triggered()
{
    ChartsParameters window;
    connect(this, &MainWindow::signal_mainToChartsParameters, &window, &ChartsParameters::slot_mainToChartsParameters);
    emit signal_mainToChartsParameters(chartsChannel);
    connect(&window, &ChartsParameters::signal_chartsParametersToMain, this, &MainWindow::slot_chartsParametersToMain);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_actionCalcParam_triggered()
{
    CalcParam window;
    connect(this, &MainWindow::signal_mainToCalcParam, &window, &CalcParam::slot_mainToCalcParam);
    emit signal_mainToCalcParam(integrateOption, integrateDot);
    connect(&window, &CalcParam::signal_calcParamToMain, this, &MainWindow::slot_calcParamToMain);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_action3D_triggered()
{
    Plot3D window;
    connect(this, &MainWindow::signal_MainToPlot3D, &window, &Plot3D::slot_MainToPlot3D);
    emit signal_MainToPlot3D(CurrNumElem, WeightCoef, CenterPos, k,
                            sizeX, sizeZ, distX, distZ,
                            radCircScr, distHex, overlayType,
                            TableChannel, Arr_sensitivityGroup, SubarrayCenter, SelectedElem, Centroids, antennaType,
                            chartsChannel);
    window.setModal(true);
    window.exec();
}

