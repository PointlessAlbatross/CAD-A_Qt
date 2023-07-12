#include "plot3d.h"

Plot3D::Plot3D(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("3D Plot");
    resize(800, 600);
}

Plot3D::~Plot3D()
{
    delete graph;
    delete container;
}

/*!
 * \brief Plot3D::D
 * Метод для вычисления характеристики направленности отдельного элемента
 * \param theta Вертикальный угол
 * \param phi Горизонтальный угол
 * \return Направленность антенны при заданном угле
 */
double Plot3D::D(double theta, double phi)
{
    if (overlayType == 0) // Четырехугольник
    {
        double a;
        if (phi != 0)
           a = sin( k * (sizeX+distX) / 2.0 * sin(theta) * sin (phi) )/ (k*(sizeX+distX) / 2.0 * (sin(theta) * sin (phi)));
        else
           a = 1;
        double b = sin ( k * (sizeZ+distZ) / 2.0 * cos (theta)) / (k * (sizeZ+distZ) / 2.0 * cos (theta));
        return a * b;
    }
    else if (overlayType != 0)  // Шестиугольник
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
 * \brief Plot3D::Dt
 * Метод для вычисления характеристики направленности для амплитудной антенны
 * \param theta Вертикальный угол
 * \param phi Горизонтальный угол
 * \return Направленность антенны при заданном угле
 */
std::complex<double> Plot3D::Dt(double theta, double phi)
{
    double theta_t = M_PI_2, phi_t = 0;
    std::complex<double> i (0, 1); // Мнимая единица
    std::complex<double> D_numerator = 0, D_denumerator = 0; // Числитель и знаменатель
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
 * \brief Plot3D::plot3D
 * Метод для построения трехмерного графика
 */
void Plot3D::plot3D()
{
    // Создание экземпляра трехмерного графика
        graph = new Q3DSurface();
        container = QWidget::createWindowContainer(graph);

        // Создание данных для графика
        QSurfaceDataProxy *dataProxy = new QSurfaceDataProxy();
        QSurface3DSeries *series = new QSurface3DSeries(dataProxy);
        series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);

        double step = 2;
        int numPointsX = 180 / step + 1; // Количество точек по оси X
        int numPointsZ = 2 * 180 / step + 1; // Количество точек по оси Y

        QSurfaceDataArray *dataArray = new QSurfaceDataArray;
        dataArray->reserve(numPointsX);

        for (double theta = 0.0; theta <= 360; theta += step) {
            QSurfaceDataRow *dataRow = new QSurfaceDataRow(numPointsZ);
            float x = theta;

            for (double phi = -90, j = 0; phi <= 90; phi += step, j++) {
                float z = phi;
                float y = double(abs(Dt(x / 180.0 * M_PI, phi / 180.0 * M_PI)));
                (*dataRow)[j].setPosition(QVector3D(x, y, z));
            }

            *dataArray << dataRow;
        }

        dataProxy->resetArray(dataArray);

        // Настройка параметров графика
        graph->axisX()->setRange(0.0, 180.0);
        graph->axisZ()->setRange(-90.0, 90.0);
        graph->addSeries(series);
        graph->axisX()->setTitle("X");
        graph->axisY()->setTitle("Y");
        graph->axisZ()->setTitle("Z");

        // Установка виджета с графиком в элемент формы
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(container);
        setLayout(layout);

        // Включение возможности вращения графика
        graph->setFlags(graph->flags() ^ Qt::FramelessWindowHint);

        // Отображение графика
        show();
}


/*!
 * \brief Plot3D::slot_MainToPlot3D
 * Слот для приема данных из главного меню
 * \param Curr_num_elem1 Текущее число элементов
 * \param Weight_coef1 Чувствительности элементов
 * \param Center_pos1 Центры тяжести групп
 * \param k1 Волновое число
 * \param size_x1 Размер прямоугольного элемента по x
 * \param size_z1 Размер прямоугольного элемента по z
 * \param dist_x1 Зазор прямоугольного элемента по x
 * \param dist_z1 Зазор прямоугольного элемента по z
 * \param rad_circ_scr1 Диаметр описанной окружности шестиугольного элемента
 * \param dist_hex1 Зазор шестиугольного элемента
 * \param overlay_type1 Тип накладки 0: 4-х угольная, 1: 6-и угольная
 * ***дописать коменты***
 * \param TableChannel1
 * \param Arr_sensitivityGroup1
 * \param SubarrayCenter1
 * \param SelectedElem1
 * \param Centroids1
 * \param antennaType1
 * \param chartsChannel1
 */
void Plot3D::slot_MainToPlot3D(QVector<int> Curr_num_elem1,
                               std::array<QVector<QVector<double> >, 17> Weight_coef1,
                               QVector<QVector<QPair<double, double> > > Center_pos1,
                               double k1, double size_x1, double size_z1,
                               double dist_x1, double dist_z1, double rad_circ_scr1,
                               double dist_hex1, int overlay_type1,
                               std::array<std::array<bool, 16>, 30> TableChannel1,
                               std::array<double, 16> Arr_sensitivityGroup1,
                               std::array<QPair<double, double>, 30> SubarrayCenter1,
                               std::array<QVector<QVector<bool> >, 16> SelectedElem1,
                               std::array<QPair<double, double>, 16> Centroids1,
                               int antennaType1, int chartsChannel1)
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

    plot3D();
}
