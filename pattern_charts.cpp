#include "pattern_charts.h"
#include "ui_pattern_charts.h"
#include <QDebug>

Pattern_charts::Pattern_charts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pattern_charts)
{
    ui->setupUi(this);
    qDebug() << "bessel" <<j1(2);
}

Pattern_charts::~Pattern_charts()
{
    delete ui;
}

double Pattern_charts::D(double theta, double phi)
{
    if (overlay_type == 0)
    {
        double a;
        if (phi)
           a = sin( k * (size_x+dist_x) / 2 * sin(theta) * sin (phi) )/ (k*(size_x+dist_x) / 2 * (sin(theta) * sin (phi)));
        else
           a = 1;
        double b = sin ( k * (size_z+dist_z) / 2 * cos (theta)) / (k * (size_z+dist_z) / 2 * cos (theta));
        return a * b;
    }
    else if (overlay_type != 0)
    {
        double a;
        if (phi != 0)
            a = j1(theta) *(k * (sqrt(3)*rad_circ_scr_pix+dist_hex_pix)/2 * sqrt(pow(sin(theta)*sin(phi),2)+pow(cos(theta),2)))/
                            (k*(sqrt(3)*rad_circ_scr_pix+dist_hex_pix)/2 * sqrt(pow(sin(theta)*sin(phi),2)+pow(cos(theta),2)));
        return a;
    }
    return 1;
}

std::complex<double> Pattern_charts::Dt(double theta, double phi)
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); // Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0;
    if (overlay_type == 0)
    {
        for (int a = 0; a < Center_pos.size(); a++)
        {
            for(int b = 0; b < Center_pos[a].size(); b++)
            {
                    //[1] Числитель
                    D_numerator += (Weight_coef[a][b] * exp( (1.0*i) * k * (Center_pos[a][b].first * ( sin(theta)*sin(phi) - sin(theta_t)*sin(phi_t) )
                                                       + Center_pos[a][b].second * (cos (theta) - cos(theta_t))) ) *
                             D(theta_t, phi_t) * ( 1.0 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0 );
                    //[2] Знаменатель
                    D_denumerator += Weight_coef[a][b] * D(theta_t, phi_t) * ( 1 + abs( sin( atan2(theta_t, phi_t) ))) / 2;
            }
        }
    }

    else if (overlay_type != 0) // Шестиугольник
    {


        for (int a = 0; a < Button_pos.size(); a++)
        {
            for(int b = 0; b < Button_pos[a].size(); b++)
            {
                //[1] Числитель
                D_numerator += (Weight_coef[a][b] * exp( (1.0*i) * k * (std::get<0>(Button_pos[a][b]) * ( sin(theta)*sin(phi) - sin(theta_t)*sin(phi_t) )
                                                   + std::get<1>(Button_pos[a][b]) * (cos (theta) - cos(theta_t))) ) *
                         D(theta_t, phi_t) * ( 1.0 + abs( sin( atan2(theta_t, phi_t) ))) / 2.0 );
                //[2] Знаменатель
                D_denumerator += Weight_coef[a][b] * D(theta_t, phi_t) * ( 1 + abs( sin( atan2(theta_t, phi_t) ))) / 2;
            }
        }
    }

    return D_numerator / D_denumerator;
}

void Pattern_charts::drow_chart()
{
    for(int reg_chart = 1; reg_chart < 3; reg_chart++)
    {
        QLineSeries *series = new QLineSeries();
        switch (reg_chart) {
        case 1:
            phi = 0;
            for (double deg = 0; deg <= 181; deg += 0.1)
                series->append(deg, abs(Dt(double(deg)/180 * M_PI, phi)));
            break;
        case 2:
            theta = M_PI_2;
                for (double deg = -90; deg <= 91; deg += 0.1)
                    series->append(deg, abs(Dt(theta, double(deg)/180 * M_PI)));
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

void Pattern_charts::drow_polar_chart()
{
    const qreal angularMin = 0;
    const qreal angularMax = 360;

    QSplineSeries *series = new QSplineSeries();
    switch (reg_chart) {
    case 1:
        phi = 0;
        for (double deg = angularMin; deg <= angularMax; deg += 0.1)
            series->append(deg, abs(Dt(double(deg)/180 * M_PI, phi)));
        break;
    case 2:
        theta = M_PI_2;
            for (double deg = angularMin; deg <= angularMax; deg += 0.1)
                series->append(deg, abs(Dt(theta, double(deg)/180 * M_PI)));
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




void Pattern_charts::slot_main_to_charts(QVector<int> Curr_num_elem1, QVector<QVector<double> > Weight_coef1,
                         QVector<QVector<std::tuple<int, int, int> > > Button_pos1,
                         double k1,
                         double size_x1, double size_z1, double dist_x1, double dist_z1,
                         int size_x_pix1, int size_z_pix1, int rad_circ_scr_pix1, int dist_hex_pix1,
                         int overlay_type1)
{

    overlay_type = overlay_type1;
    double scale_koef = size_x1 / size_x_pix1 ;
    Curr_num_elem = Curr_num_elem1;
    Weight_coef = Weight_coef1;
    k = k1;

    if (overlay_type1 != 0)
    {
        Button_pos = Button_pos1;
        qDebug() << "Button_pos" <<Qt::endl;
        for (int i = 0; i < Button_pos1.size(); i++)
        {
            for (int j = 0; j < Button_pos1[i].size(); j++)
            {
                qDebug() << std::get<0>(Button_pos1[i][j]) << std::get<1>(Button_pos1[i][j]) << " ";
            }
        }
    }

    size_x = size_x1;
    size_z = size_z1;
    dist_x = dist_x1;
    dist_z = dist_z1;
    rad_circ_scr_pix = rad_circ_scr_pix1;
    dist_hex_pix = dist_hex_pix1;
    if (overlay_type1 == 0)
    {
        Center_pos.resize(Button_pos1.size());
        for (int i = 0; i < Button_pos1.size(); i++)
        {
            Center_pos[i].resize(Button_pos1[i].size());
            for (int j = 0; j < Button_pos1[i].size(); j++)
            {
                Center_pos[i][j].first = (std::get<0>(Button_pos1[i][j]) + double(size_x_pix1) / 2) * scale_koef;
                Center_pos[i][j].second = -(std::get<1>(Button_pos1[i][j]) + double(size_z_pix1) / 2) * scale_koef;
                Center_pos[i][j].first = round(Center_pos[i][j].first * 100)/100;
                Center_pos[i][j].second = round(Center_pos[i][j].second * 100)/100;
            }
        }
        qDebug() << "Center_pos" <<Qt::endl;
        qDebug() << Center_pos <<Qt::endl;
    }

    drow_chart();
    //drow_polar_chart();
}
