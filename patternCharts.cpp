#include "patternCharts.h"
#include "ui_patternCharts.h"
#include <QDebug>
#include "cadAMath.h"

PatternCharts::PatternCharts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatternCharts)
{
    ui->setupUi(this);
}

PatternCharts::~PatternCharts()
{
    delete ui;
}


/*!
 * \brief PatternCharts::D
 * Метод для вычисления характеристики направленности отдельного элемента
 * \param theta Вертикальный угол
 * \param phi Горизонтальный угол
 * \return Направленность антенны при заданном угле
 */
double PatternCharts::D(double theta, double phi)
{
    if (overlayType == 0) /// Четырехугольник
    {
        double a;
        if (phi != 0)
           a = sin( k * (sizeX+distX) / 2.0 * sin(theta) * sin (phi) )/ (k*(sizeX+distX) / 2.0 * (sin(theta) * sin (phi)));
        else
           a = 1;
        double b = sin ( k * (sizeZ+distZ) / 2.0 * cos (theta)) / (k * (sizeZ+distZ) / 2.0 * cos (theta));
        return a * b;
    }
    else if (overlayType != 0)  /// Шестиугольник
    {
        double a1,b1;
        if (phi != 0)
        {
            a1 = 2 * j1(k * (sqrt(3)*radCircScr+distHex)/2.0 * sqrt(pow(sin(theta)*sin(phi), 2)+pow(cos(theta), 2)));
            b1 = k * (sqrt(3)*radCircScr+distHex)/2.0 * sqrt(pow(sin(theta) * sin(phi), 2) + pow(cos(theta), 2));
            return a1/b1;
        }

    }
    return 1;
}
/*!
 * \brief PatternCharts::Dt
 * Метод для вычисления характеристики направленности для амплитудной антенны
 * \param theta Вертикальный угол
 * \param phi Горизонтальный угол
 * \return Направленность антенны при заданном угле
 */
std::complex<double> PatternCharts::Dt(double theta, double phi)
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); ///< Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0; ///< Числитель и знаменатель
    for (int a = 0; a < CenterPos.size(); a++)
    {
        for(int b = 0; b < CenterPos[a].size(); b++)
        {
                //![1] Числитель
                D_numerator += (WeightCoef[0][a][b] * exp( (1.0*i) * k * (CenterPos[a][b].first * ( sin(theta)*sin(phi) - sin(theta_t)*sin(phi_t) )
                                                   + CenterPos[a][b].second * (cos (theta) - cos(theta_t))) ) *
                        D(theta_t, phi_t) * ( 1.0 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0 );
                //![2] Знаменатель
                D_denumerator += WeightCoef[0][a][b] * D(theta_t, phi_t) * ( 1 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0;
        }
    }
    return D_numerator / D_denumerator;
}

/*!
 * \brief PatternCharts::DLt
 * Метод для вычисления характеристики направленности для каналов фазовой антенны
 * \param theta Вертикальный угол
 * \param phi Горизонтальный угол
 * \param chn Номер канала
 * \return Направленность канала при заданном угле
 */
std::complex<double> PatternCharts::DLt(double theta, double phi, int chn)
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); ///< Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0; ///< Числитель и знаменатель
    for (int grp = 0; grp < 16; grp++)
    {
        if (!TableChannel[chn][grp])
            continue;
        D_numerator += Arr_sensitivityGroup[grp] *
                exp((1.0*i) * k * (SubarrayCenter[chn].first * (sin(theta) * sin (phi) - sin(theta_t) * sin(phi_t)) +
                                   SubarrayCenter[chn].second * (cos(theta) - cos (theta_t)) ) * DUt(theta, phi, grp))*( 1.0 + abs( sin( atan2(theta, phi) ))) / 2.0;
        D_denumerator += Arr_sensitivityGroup[grp] * DUt(theta_t, phi_t, grp)*( 1.0 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0;
    }
    return D_numerator / D_denumerator;
}

/*!
 * \brief PatternCharts::DUt
 * Метод для вычисления характеристики направленности для групп фазовой антенны
 * \param theta
 * \param phi
 * \param grp
 * \return
 */
std::complex<double> PatternCharts::DUt(double theta, double phi, int grp)
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); ///< Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0; ///< Числитель и знаменатель
    for (int a = 0; a < CenterPos.size(); a++)
    {
        for(int b = 0; b < CenterPos[a].size(); b++)
        {
                if (!SelectedElem[grp][a][b])
                    continue;
                //![1] Числитель
                D_numerator += (WeightCoef[grp][a][b] * exp( (1.0*i) * k * ((CenterPos[a][b].first - Centroids[grp].first ) * ( sin(theta)*sin(phi) - sin(theta_t)*sin(phi_t) )
                                                   + (CenterPos[a][b].second - Centroids[grp].second) * (cos (theta) - cos(theta_t))) ) *
                         D(theta, phi) * ( 1.0 + abs( sin( atan2(theta, phi) ))) / 2.0 );
                //![2] Знаменатель
                D_denumerator += WeightCoef[grp][a][b] * D(theta_t, phi_t) * ( 1 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0;
        }
    }
    return D_numerator / D_denumerator;
}




void PatternCharts::drawChart()
{
    for(int reg_chart = 1; reg_chart <= 2; reg_chart++)
    {
        QLineSeries *series = new QLineSeries();
        if (!antennaType){
            // амплитудная
                   switch (reg_chart) {
                   case 1:
                       phi = 0;
                       for (double deg = 0; deg <= 181; deg += 0.1)
                           series->append(deg, abs(Dt(deg / 180.0 * M_PI, phi)));
                       break;
                   case 2:
                       theta = M_PI_2;
                       for (double deg = -90; deg <= 91; deg += 0.1)
                           series->append(deg, abs(Dt(theta, deg / 180.0 * M_PI)));
                       break;
                   }
        }
        else if (antennaType)
        {
            switch (reg_chart) {
            case 1:
                phi = 0;
                for (double deg = 0; deg <= 181; deg += 0.1)
                    series->append(deg, abs(DUt(deg / 180.0 * M_PI, phi, chartsChannel)));
                break;
            case 2:
                theta = M_PI_2;
                for (double deg = -90; deg <= 91; deg += 0.1)
                    series->append(deg, abs(DUt(theta, deg / 180.0 * M_PI, chartsChannel)));
                break;
            }
        }


        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);

        QValueAxis *axisX = new QValueAxis;
        switch (reg_chart) {
            case 1:
                chart->setTitle("вертикальное сечение");
                axisX->setRange(0, 180);
                axisX->setTitleText("угол Θ, град");
                break;
            case 2:
                chart->setTitle("азимутальное сечение");
                axisX->setRange(-90, 90);
                axisX->setTitleText("угол φ, град");
                break;
        }
        axisX->setTickCount(11);
        axisX->setLabelFormat("%i");

        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0.0, 1.01);
        axisY->setTickCount(11);
        axisY->setLabelFormat("%.3f");
        axisY->setLabelsVisible(true);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        switch (reg_chart) {
            case 1:
                ui->formLayout_1->addWidget(chartView);
                break;
            case 2:
                ui->formLayout_2->addWidget(chartView);
                break;
        }

    }
}

/*
void PatternCharts::drawPhaseChart()
{
    double stepGraph = 0.01;
    for(int reg_chart = 1; reg_chart <= 2; reg_chart++)
    {
        QVector<std::complex<double>> input;
        QVector<std::complex<double>> result;
        QLineSeries *series = new QLineSeries();
        switch (reg_chart) {
        case 1:
            phi = 0;
            for (double deg = 0; deg <= 181; deg += stepGraph)
                input.push_back(Dt(deg / 180.0 * M_PI, phi));
            result = m_cadAMath.ifft(input);
            for (double deg = 0, cnt = 0 ; deg <= 181; deg += stepGraph, cnt += 1)
                series->append(deg, atan2(result[cnt].real(), result[cnt].imag()) * 180 / M_PI);
            break;
        case 2:
            double theta = M_PI_2;
            for (double deg = -90; deg <= 91; deg += stepGraph)
                input.push_back(Dt(theta, deg / 180.0 * M_PI));
            result = m_cadAMath.ifft(input);
            for (double deg = -90, cnt = 0; deg <= 91; deg += stepGraph, cnt += 1)
                series->append(deg, atan2(result[cnt].real(), result[cnt].imag()) * 180 / M_PI);
            break;
        }

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);

        QValueAxis *axisX = new QValueAxis;
        switch (reg_chart) {
            case 1:
                chart->setTitle("вертикальное сечение");
                axisX->setRange(0, 180);
                axisX->setTitleText("угол Θ, град");
                break;
            case 2:
                chart->setTitle("азимутальное сечение");
                axisX->setRange(-90, 90);
                axisX->setTitleText("угол φ, град");
                break;
        }
        axisX->setTickCount(11);
        axisX->setLabelFormat("%i");

        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(-180, 180);
        axisY->setTickCount(11);
        axisY->setLabelFormat("%.3f");
        axisY->setLabelsVisible(true);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        switch (reg_chart) {
            case 1:
                ui->formLayout_1->addWidget(chartView);
                break;
            case 2:
                ui->formLayout_2->addWidget(chartView);
                break;
        }

    }
}
*/

void PatternCharts::drawPolarChart()
{
    for (int reg_chart = 1; reg_chart <= 2; reg_chart++)
    {

        const qreal angularMin = 0;
        const qreal angularMax = 360;

        QSplineSeries *series = new QSplineSeries();
        switch (reg_chart) {
        case 1:
            phi = 0;
            for (double deg = angularMin; deg <= angularMax; deg += 0.1)
                series->append(deg, abs(Dt(deg / 180.0 * M_PI, phi)));
        break;
        case 2:
            theta = M_PI_2;
                for (double deg = angularMin; deg <= angularMax; deg += 0.1)
                    series->append(deg, abs(Dt(theta, deg / 180.0 * M_PI)));
        break;
        }

        QPolarChart *chart = new QPolarChart();
        chart->legend()->hide();
        chart->addSeries(series);

        QValueAxis *angularAxis = new QValueAxis();
        angularAxis->setRange(angularMin, angularMax);
        angularAxis->setTickCount(13);
        angularAxis->setLabelFormat("%d");
        angularAxis->setLabelsVisible(true);
        chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

        QValueAxis *radialAxis = new QValueAxis();
        radialAxis->setRange(0.0, 1.01);
        radialAxis->setTickCount(11);
        radialAxis->setLabelFormat("%.3f");
        radialAxis->setLabelsVisible(true);
        chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

        QChartView *chartView = new QChartView();
        chartView->setChart(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        switch (reg_chart) {
        case 1:
            ui->formLayout_1->addWidget(chartView);
            break;
        case 2:
            ui->formLayout_2->addWidget(chartView);
            break;
        }
    }
}

void PatternCharts::drawReverb(QVector<double> VecSurfFreq, QVector<double> VecSurfDist, QVector<double> VecBotFreq,
                               QVector<double> VecBotDist, QVector<double> VecSurrFreq, QVector<double> VecSurrDist,
                               QVector<double> VecSumFreq, QVector<double> VecSumDist, std::array<bool, 4> ReverbChecks,
                               std::array<bool, 2> ReverbCalc, QVector<double> VecFreq, QVector<double> VecDist)
{


    if (ReverbCalc[0]) // Осуществлялся частотный расчет
    {
        QWidget *newPage = new QWidget();
        QFormLayout *formLayout = new QFormLayout(newPage);
        QChart *chart = new QChart();
        chart->legend()->setAlignment(Qt::AlignBottom);

        if (ReverbChecks[0])
        {
            QLineSeries *surfSeries = new QLineSeries();
            for (int i = 0; i < VecFreq.size(); i++)
            {
                surfSeries->append(VecFreq[i], VecSurfFreq[i]);
                surfSeries->setColor(Qt::red);
                surfSeries->setName("Поверхностная реверберация");
            }
        chart->addSeries(surfSeries);
        }

        if (ReverbChecks[1])
        {
            QLineSeries *botSeries = new QLineSeries();
            for (int i = 0; i < VecFreq.size(); i++)
            {
                botSeries->append(VecFreq[i], VecBotFreq[i]);
                botSeries->setColor(Qt::blue);
                botSeries->setName("Донная реверберация");
            }
        chart->addSeries(botSeries);
        }

        if (ReverbChecks[2])
        {
            QLineSeries *surrSeries = new QLineSeries();
            for (int i = 0; i < VecFreq.size(); i++)
            {
                surrSeries->append(VecFreq[i], VecSurrFreq[i]);
                surrSeries->setColor(Qt::darkGreen);
                surrSeries->setName("Объемная реверберация");
            }
        chart->addSeries(surrSeries);
        }

        if (ReverbChecks[3])
        {
            QLineSeries *sumSeries = new QLineSeries();
            for (int i = 0; i < VecFreq.size(); i++)
            {
                sumSeries->append(VecFreq[i], VecSumFreq[i]);
                sumSeries->setColor(Qt::magenta);
                sumSeries->setName("Суммарная реверберация");
            }
        chart->addSeries(sumSeries);
        }


        // Создание осей графика
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("f, Гц");
        QLogValueAxis *axisY = new QLogValueAxis();
        axisX->setTickCount(11);
        auto num1 = std::max_element(VecSurfFreq.begin(), VecSurfFreq.end());
        double num1v = *num1;
        auto num2 = std::max_element(VecBotFreq.begin(), VecBotFreq.end());
        double num2v = *num2;
        auto num3 = std::max_element(VecSurrFreq.begin(), VecSurrFreq.end());
        double num3v = *num3;
        auto num4 = std::max_element(VecSumFreq.begin(), VecSumFreq.end());
        double num4v = *num4;
        double maxValue = std::max({num1v, num2v, num3v, num4v});

        auto num12 = std::max_element(VecSurfFreq.begin(), VecSurfFreq.end());
        double num1m = *num12;
        auto num22 = std::max_element(VecBotFreq.begin(), VecBotFreq.end());
        double num2m = *num22;
        auto num32 = std::max_element(VecSurrFreq.begin(), VecSurrFreq.end());
        double num3m = *num32;
        auto num42 = std::max_element(VecSumFreq.begin(), VecSumFreq.end());
        double num4m = *num42;
        double minValue = std::min({num1m, num2m, num3m, num4m});

        axisY->setMin(m_cadAMath.floorToPowerOfTen(minValue));
        axisY->setMax(m_cadAMath.ceilToPowerOfTen(maxValue));
        axisY->setLabelFormat("%.2e");
        //axisY->setMax(1);
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);


        // Привязка серий к осям
        for (QAbstractSeries *series : chart->series()) {
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        }
        // Создание виджета для отображения графика
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Добавление виджета с графиком в форму
        formLayout->addWidget(chartView);

        ui->tabWidget->addTab(newPage, "Реверберация по частоте");
    }

    if (ReverbCalc[1]) // Осуществлялся временной расчет
    {
        QWidget *newPage = new QWidget();
        QFormLayout *formLayout = new QFormLayout(newPage);
        QChart *chart = new QChart();
        chart->legend()->setAlignment(Qt::AlignBottom);
        if (ReverbChecks[0])
        {
            QLineSeries *surfSeries = new QLineSeries();
            for (int i = 0; i < VecDist.size(); i++)
            {
                surfSeries->append(VecDist[i], VecSurfDist[i]);
                surfSeries->setColor(Qt::red);
                surfSeries->setName("Поверхностная реверберация");
            }
        chart->addSeries(surfSeries);
        }

        if (ReverbChecks[1])
        {
            QLineSeries *botSeries = new QLineSeries();
            for (int i = 0; i < VecDist.size(); i++)
            {
                botSeries->append(VecDist[i], VecBotDist[i]);
                botSeries->setColor(Qt::blue);
                botSeries->setName("Донная реверберация");
            }
        chart->addSeries(botSeries);
        }

        if (ReverbChecks[2])
        {
            QLineSeries *surrSeries = new QLineSeries();
            for (int i = 0; i < VecDist.size(); i++)
            {
                surrSeries->append(VecDist[i], VecSurrDist[i]);
                surrSeries->setColor(Qt::darkGreen);
                surrSeries->setName("Объемная реверберация");
            }
        chart->addSeries(surrSeries);
        }

        if (ReverbChecks[3])
        {
            QLineSeries *sumSeries = new QLineSeries();
            for (int i = 0; i < VecDist.size(); i++)
            {
                sumSeries->append(VecDist[i], VecSumDist[i]);
                sumSeries->setColor(Qt::magenta);
                sumSeries->setName("Суммарная реверберация");
            }
        chart->addSeries(sumSeries);
        }


        // Создание осей графика
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("r, м");
        QLogValueAxis *axisY = new QLogValueAxis();
        axisX->setTickCount(11);
        auto num1 = std::max_element(VecSurfDist.begin(), VecSurfDist.end());
        double num1v = *num1;
        auto num2 = std::max_element(VecBotDist.begin(), VecBotDist.end());
        double num2v = *num2;
        auto num3 = std::max_element(VecSurrDist.begin(), VecSurrDist.end());
        double num3v = *num3;
        auto num4 = std::max_element(VecSumDist.begin(), VecSumDist.end());
        double num4v = *num4;
        double maxValue = std::max({num1v, num2v, num3v, num4v});

        auto num12 = std::max_element(VecSurfDist.begin(), VecSurfDist.end());
        double num1m = *num12;
        auto num22 = std::max_element(VecBotDist.begin(), VecBotDist.end());
        double num2m = *num22;
        auto num32 = std::max_element(VecSurrDist.begin(), VecSurrDist.end());
        double num3m = *num32;
        auto num42 = std::max_element(VecSumDist.begin(), VecSumDist.end());
        double num4m = *num42;
        double minValue = std::min({num1m, num2m, num3m, num4m});


        axisY->setMin(m_cadAMath.floorToPowerOfTen(minValue));
        axisY->setMax(m_cadAMath.ceilToPowerOfTen(maxValue));
        axisY->setLabelFormat("%.2e");
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);

        // Привязка серий к осям
        for (QAbstractSeries *series : chart->series()) {
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        }
        // Создание виджета для отображения графика
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Добавление виджета с графиком в форму
        formLayout->addWidget(chartView);

        ui->tabWidget->addTab(newPage, "Реверберация по дальности");
    }

}

void PatternCharts::drawEcho(QVector<double> VecFreqE, QVector<double> VecEchoFreq, QVector<double> VecDistE, QVector<double> VecEchoDist, std::array<bool, 2> EchoCalc)
{
    if (EchoCalc[0]) // Осуществлялся частотный расчет
    {
        QWidget *newPage = new QWidget();
        QFormLayout *formLayout = new QFormLayout(newPage);
        QChart *chart = new QChart();
        chart->legend()->setAlignment(Qt::AlignBottom);
        QLineSeries *Series = new QLineSeries();
        for (int i = 0; i < VecFreqE.size(); i++)
        {
            Series->append(VecFreqE[i], VecEchoFreq[i]);
            Series->setName("Эхо-сигнал от частоты");
        }
        chart->addSeries(Series);

        // Создание осей графика
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("f, Гц");
        QLogValueAxis *axisY = new QLogValueAxis();
        axisX->setTickCount(11);
        auto mxVal = std::max_element(VecEchoFreq.begin(), VecEchoFreq.end());
        double mxVal1 = *mxVal;
        auto mnVal = std::min_element(VecEchoFreq.begin(), VecEchoFreq.end());
        double mnVal1 = *mnVal;

        axisY->setMin(m_cadAMath.floorToPowerOfTen(mnVal1));
        axisY->setLabelFormat("%.2e");
        axisY->setMax(m_cadAMath.ceilToPowerOfTen(mxVal1));
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);

        // Привязка серий к осям
        for (QAbstractSeries *series : chart->series()) {
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        }
        // Создание виджета для отображения графика
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Добавление виджета с графиком в форму
        formLayout->addWidget(chartView);

        ui->tabWidget->addTab(newPage, "Эхо-сигнал от частоты");
    }

    if (EchoCalc[1]) // Осуществлялся временной расчет
    {
        QWidget *newPage = new QWidget();
        QFormLayout *formLayout = new QFormLayout(newPage);
        QChart *chart = new QChart();
        chart->legend()->setAlignment(Qt::AlignBottom);
        QLineSeries *Series = new QLineSeries();
        for (int i = 0; i < VecDistE.size(); i++)
        {
            Series->append(VecDistE[i], VecEchoDist[i]);
            Series->setName("Эхо-сигнал от дальности");
        }
        chart->addSeries(Series);


        // Создание осей графика
        QValueAxis *axisX = new QValueAxis();
        axisX->setTitleText("R, м");
        QLogValueAxis *axisY = new QLogValueAxis();
        auto mxVal = std::max_element(VecEchoDist.begin(), VecEchoDist.end());
        double mxVal1 = *mxVal;
        auto mnVal = std::min_element(VecEchoDist.begin(), VecEchoDist.end());
        double mnVal1 = *mnVal;
        axisX->setTickCount(11);


        axisY->setMin(m_cadAMath.floorToPowerOfTen(mnVal1));
        axisY->setLabelFormat("%.2e");
        axisY->setMax(m_cadAMath.ceilToPowerOfTen(mxVal1));
        chart->addAxis(axisX, Qt::AlignBottom);
        chart->addAxis(axisY, Qt::AlignLeft);

        // Привязка серий к осям
        for (QAbstractSeries *series : chart->series()) {
            series->attachAxis(axisX);
            series->attachAxis(axisY);
        }
        // Создание виджета для отображения графика
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Добавление виджета с графиком в форму
        formLayout->addWidget(chartView);

        ui->tabWidget->addTab(newPage, "Эхо-сигнал от дальности");
    }
}



void PatternCharts::slotMainToCharts(QVector<int> Curr_num_elem1, std::array<QVector<QVector<double>>, 17> Weight_coef1,
                                     QVector<QVector<QPair<double,double>>> Center_pos1,
                                     double k1,
                                     double size_x1, double size_z1, double dist_x1, double dist_z1,
                                     double rad_circ_scr1, double dist_hex1,
                                     int overlay_type1,
                                     QVector<double> VecSurfFreq,
                                     QVector<double> VecSurfDist,
                                     QVector<double> VecBotFreq,
                                     QVector<double> VecBotDist,
                                     QVector<double> VecSurrFreq,
                                     QVector<double> VecSurrDist,
                                     QVector<double> VecSumFreq,
                                     QVector<double> VecSumDist,
                                     std::array<bool, 4> ReverbChecks,
                                     std::array<bool, 2> ReverbCalc,
                                     QVector<double> VecFreq,
                                     QVector<double> VecDist,
                                     QVector<double> VecFreqE,
                                     QVector<double> VecEchoFreq,
                                     QVector<double> VecDistE,
                                     QVector<double> VecEchoDist,
                                     std::array<bool, 2> EchoCalc,
                                     std::array<std::array<bool, 16>, 30> TableChannel1,
                                     std::array<double,16> Arr_sensitivityGroup1,
                                     std::array<QPair<double, double>, 30> SubarrayCenter1,
                                     std::array<QVector<QVector<bool>>, 16> SelectedElem1,
                                     std::array<QPair<double, double>, 16> Centroids1,
                                     int antennaType1, int chartsChannel1
                                    )
{
    antennaType = antennaType1;
    TableChannel = TableChannel1;
    Arr_sensitivityGroup = Arr_sensitivityGroup1;
    SubarrayCenter = SubarrayCenter1;
    SelectedElem = SelectedElem1;
    Centroids = Centroids1;

    chartsChannel = chartsChannel1;

    CenterPos = Center_pos1;
    overlayType = overlay_type1;
    CurrNumElem = Curr_num_elem1;
    WeightCoef = Weight_coef1;
    k = k1;

    radCircScr = rad_circ_scr1;
    distHex = dist_hex1;

    sizeX = size_x1;
    sizeZ = size_z1;
    distX = dist_x1;
    distZ = dist_z1;

    drawChart();
    drawReverb(VecSurfFreq, VecSurfDist, VecBotFreq, VecBotDist, VecSurrFreq,
               VecSurrDist, VecSumFreq, VecSumDist, ReverbChecks, ReverbCalc, VecFreq, VecDist);
    drawEcho(VecFreqE, VecEchoFreq, VecDistE, VecEchoDist, EchoCalc);
    //drawPhaseChart();
    //drawPolarChart();
}
