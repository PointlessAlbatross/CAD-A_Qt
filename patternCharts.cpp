#include "patternCharts.h"
#include "ui_patternCharts.h"
#include <QDebug>

Pattern_charts::Pattern_charts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pattern_charts)
{
    ui->setupUi(this);
}

Pattern_charts::~Pattern_charts()
{
    delete ui;
}

double Pattern_charts::D(double theta, double phi)
{
    if (overlayType == 0) // Четырехугольник
    {
        double a;
        if (phi != 0)
           a = sin( k * (sizeX+distX) / 2 * sin(theta) * sin (phi) )/ (k*(sizeX+distX) / 2 * (sin(theta) * sin (phi)));
        else
           a = 1;
        double b = sin ( k * (sizeZ+distZ) / 2 * cos (theta)) / (k * (sizeZ+distZ) / 2 * cos (theta));
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
//проблеммы с каналами
std::complex<double> Pattern_charts::Dt(double theta, double phi)
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); // Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0;
    for (int a = 0; a < CenterPos.size(); a++)
    {
        for(int b = 0; b < CenterPos[a].size(); b++)
        {
                //[1] Числитель
                D_numerator += (WeightCoef[0][a][b] * exp( (1.0*i) * k * (CenterPos[a][b].first * ( sin(theta)*sin(phi) - sin(theta_t)*sin(phi_t) )
                                                   + CenterPos[a][b].second * (cos (theta) - cos(theta_t))) ) *
                         D(theta_t, phi_t) * ( 1.0 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0 );
                //[2] Знаменатель
                D_denumerator += WeightCoef[0][a][b] * D(theta_t, phi_t) * ( 1 + abs( sin( atan2(theta_t, phi_t) ))) / 2;
        }
    }
    return D_numerator / D_denumerator;
}

void Pattern_charts::drawChart()
{
    for(int reg_chart = 1; reg_chart <= 2; reg_chart++)
    {
        QLineSeries *series = new QLineSeries();
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

void Pattern_charts::drawPolarChart()
{
    const qreal angularMin = 0;
    const qreal angularMax = 360;

    QSplineSeries *series = new QSplineSeries();
    switch (regChart) {
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
    chart->setTitle("Simple line chart example");

    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setRange(angularMin, angularMax);
    angularAxis->setTickCount(13); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%d");
    angularAxis->setLabelsVisible(true);
    angularAxis->setReverse(true);
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

    ui->formLayout_1->addWidget(chartView);
}




void Pattern_charts::slotMainToCharts(QVector<int> Curr_num_elem1, std::array<QVector<QVector<double>>, 17> Weight_coef1,
                         QVector<QVector<std::tuple<int, int, int> > > Button_pos1,
                         double k1,
                         double size_x1, double size_z1, double dist_x1, double dist_z1,
                         int size_x_pix1, int size_z_pix1, double rad_circ_scr1, double dist_hex1, int rad_circ_scr_pix1, int dist_hex_pix1,
                         int overlay_type1)
{

    overlayType = overlay_type1;
    double scale_koef;
    if (overlay_type1 == 0)
        scale_koef = size_x1 / size_x_pix1 ;
    else
        scale_koef = rad_circ_scr1 / rad_circ_scr_pix1 ;
    radCircScr = rad_circ_scr1;
    distHex = dist_hex1;
    CurrNumElem = Curr_num_elem1;
    WeightCoef = Weight_coef1;
    k = k1;

    if (overlay_type1 != 0)
    {
        ButtonPos = Button_pos1;
        qDebug() << "Button_pos" <<Qt::endl;
        CenterPos.resize(Button_pos1.size());
        for (int i = 0; i < Button_pos1.size(); i++)
        {
            CenterPos[i].resize(Button_pos1[i].size());
            for (int j = 0; j < Button_pos1[i].size(); j++)
            {
                CenterPos[i][j].first = std::get<0>(Button_pos1[i][j]) ;
                CenterPos[i][j].second = -(std::get<1>(Button_pos1[i][j]));
                CenterPos[i][j].first = round(CenterPos[i][j].first * scale_koef * 100)/100;
                CenterPos[i][j].second = round(CenterPos[i][j].second * scale_koef * 100)/100;
            }
        }
    }

    sizeX = size_x1;
    sizeZ = size_z1;
    distX = dist_x1;
    distZ = dist_z1;
    radCircScrPix = rad_circ_scr_pix1;
    distHexPix = dist_hex_pix1;
    if (overlay_type1 == 0)
    {
        CenterPos.resize(Button_pos1.size());
        for (int i = 0; i < Button_pos1.size(); i++)
        {
            CenterPos[i].resize(Button_pos1[i].size());
            for (int j = 0; j < Button_pos1[i].size(); j++)
            {
                CenterPos[i][j].first = (std::get<0>(Button_pos1[i][j]) + double(size_x_pix1) / 2) * scale_koef;
                CenterPos[i][j].second = -(std::get<1>(Button_pos1[i][j]) + double(size_z_pix1) / 2) * scale_koef;
                CenterPos[i][j].first = round(CenterPos[i][j].first * 100)/100;
                CenterPos[i][j].second = round(CenterPos[i][j].second * 100)/100;
            }
        }
        qDebug() << "Center_pos" <<Qt::endl;
        qDebug() << CenterPos <<Qt::endl;
    }

    drawChart();
    //drawPolarChart();
}
