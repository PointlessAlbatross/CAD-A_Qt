#include "arrangementOfElements.h"
#include "selectWeight.h"
#include "ui_arrangementOfElements.h"



//#40cfff приемная
//f4a900ff RGBA

ArrangementOfElements::ArrangementOfElements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArrangementOfElements)
{
    textType = 1;
    diamPix = 500 * scaleKoef; // число пикселей в диаметре
    groupNum = 1;
    ui->setupUi(this);
    ui->groupNumButton_1->setDisabled(true);
    selectedChanelNum = 1;
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::white);
    drawCirc();
    scene->installEventFilter(this);
    ui->graphicsView->scale(1 / (scaleKoef), 1 / (scaleKoef)); // начальный масштаб
}

/*!
 * \brief ArrangementOfElements::rectCheck
 * Метод проверяет попадает ли указатель мыши в прямоугольник
 * \param x Координата x мыши
 * \param y Координата y мыши
 * \param vx Координата x центра прямоугольника
 * \param vy Координата y центра прямоугольника
 * \return Был ли клик на прямоугольник
 */
bool ArrangementOfElements::rectCheck(int x, int y, int vx, int vy)
{
    return x >= vx and
           x <= vx + sizeXPix and
           y >= vy and
           y <= vy + sizeZPix;
}

/*!
 * \brief ArrangementOfElements::rectClick
 * Метод позволяющий кликать на прямоугольники на сцене
 * \param watched
 * \param event
 */
void ArrangementOfElements::rectClick(QObject *watched, QEvent *event)
{
    if(watched == scene){
             QGraphicsSceneMouseEvent *mouseSceneEvent;
             //![1]
             if(event->type() == QEvent::GraphicsSceneMousePress){
                         mouseSceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
                         if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::RightButton)
                            qDebug()<< mouseSceneEvent->scenePos();
                         for (int i = 0, i_fl = 0; i < ButtonPos.size() and !i_fl; i++)
                         {
                             for (int j = 0, j_fl = 0; j < ButtonPos[i].size() and !j_fl; j++)
                             {
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::RightButton)
                                {
                                    if (
                                        rectCheck(mouseSceneEvent->scenePos().x(), mouseSceneEvent->scenePos().y(),
                                                  std::get<0>(ButtonPos[i][j]), std::get<1>(ButtonPos[i][j]))
                                       )
                                    {
                                        SelectWeight window;
                                        connect(this, &ArrangementOfElements::signalArrangeToSelectWeight, &window, &SelectWeight::slotArrangeToSelectWeigth);
                                        if (!regime)
                                            emit signalArrangeToSelectWeight(WeightCoef[16][i][j], i, j, std::get<2>(ButtonPos[i][j]));
                                        else if(!antennaType)
                                            emit signalArrangeToSelectWeight(WeightCoef[0][i][j], i, j, std::get<2>(ButtonPos[i][j]));
                                        else
                                            emit signalArrangeToSelectWeight(WeightCoef[groupNum - 1][i][j], i, j, std::get<2>(ButtonPos[i][j]));
                                        connect(&window, &SelectWeight::signalSelectWeightToArrange, this, &ArrangementOfElements::slotSelectWeightToArrange);
                                        window.setModal(true);
                                        window.exec();
                                        i_fl = 1; //  флаги выхода из цикла
                                        j_fl = 1;
                                    }
                                }
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::LeftButton)
                                {
                                    if (rectCheck(mouseSceneEvent->scenePos().x(), mouseSceneEvent->scenePos().y(),
                                        std::get<0>(ButtonPos[i][j]), std::get<1>(ButtonPos[i][j]))
                                       )
                                    {
                                        if (regime)
                                        {

                                            if(!SelectedElem[groupNum - 1][i][j])
                                               SelectedElem[groupNum - 1][i][j] = true;
                                            else
                                               SelectedElem[groupNum - 1][i][j] = false;
                                            scene->clear();
                                            drawCirc();
                                            redrawing();
                                            i_fl = 1; //  флаги выхода из цикла
                                            j_fl = 1;
                                        }
                                    }
                                }
                              }
                         }
                 }
    }
}


/*!
 * \brief ArrangementOfElements::hexCheck
 * Метод проверяет попадает ли указатель мыши в шестиугольник
 * \param cx Координата x центра шестиугольника
 * \param cy Координата y центра шестиугольника
 * \param x Координата x мыши
 * \param y Координата y мыши
 * \return Был ли клик на шестиугольник
 */
bool ArrangementOfElements::hexCheck(int cx, int cy, int x, int y)
{
    const int sides = 6;
    double angle = M_PI / 6.0; // 30 градусов в радиан
    double vertexX[sides];
    double vertexY[sides];
    for (int i = 0; i < sides; ++i)
    {
        vertexX[i] = cx + radCircScrPix * cos(angle);
        vertexY[i] = cy + radCircScrPix * sin(angle);
        angle += M_PI / 3.0; // 60 градусов в радиан
    }
    bool inside = false;
    for (int i = 0, j = sides - 1; i < sides; j = i++) {
        if (((vertexY[i] > y) != (vertexY[j] > y)) and
            (x < (vertexX[j] - vertexX[i]) * (y - vertexY[i]) / (vertexY[j] - vertexY[i]) + vertexX[i])) {
            inside = !inside;
        }
    }
    return inside;
}

/*!
 * \brief ArrangementOfElements::hexClick
 * Метод позволяющий кликать на прямоугольники на сцене
 * \param watched
 * \param event
 */
void ArrangementOfElements::hexClick(QObject *watched, QEvent *event)
{
    if(watched == scene){
             QGraphicsSceneMouseEvent *mouseSceneEvent;
             //![1]
             if(event->type() == QEvent::GraphicsSceneMousePress){
                         mouseSceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
                         if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::RightButton)
                            qDebug()<< mouseSceneEvent->scenePos();
                         for (int i = 0, i_fl = 0; i < ButtonPos.size() and !i_fl; i++)
                         {
                             for (int j = 0, j_fl = 0; j < ButtonPos[i].size() and !j_fl; j++)
                             {
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::RightButton)
                                {
                                    if(
                                            hexCheck(mouseSceneEvent->scenePos().x(), mouseSceneEvent->scenePos().y(),
                                                    std::get<0>(ButtonPos[i][j]), std::get<1>(ButtonPos[i][j]))
                                      )
                                    {
                                       qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(ButtonPos[i][j]) <<Qt::endl;
                                       qDebug() << WeightCoef[groupNum - 1] << Qt::endl;
                                       SelectWeight window;
                                       connect(this, &ArrangementOfElements::signalArrangeToSelectWeight, &window, &SelectWeight::slotArrangeToSelectWeigth);
                                       emit signalArrangeToSelectWeight(WeightCoef[groupNum - 1][i][j], i, j, std::get<2>(ButtonPos[i][j]));
                                       connect(&window, &SelectWeight::signalSelectWeightToArrange, this, &ArrangementOfElements::slotSelectWeightToArrange);
                                       window.setModal(true);
                                       window.exec();
                                       i_fl = 1; //  флаги выхода из цикла
                                       j_fl = 1;
                                    }
                                }
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::LeftButton)
                                {
                                    if (
                                            hexCheck(mouseSceneEvent->scenePos().x(), mouseSceneEvent->scenePos().y(),
                                                         std::get<0>(ButtonPos[i][j]), std::get<1>(ButtonPos[i][j]))
                                       )
                                    {
                                        if (regime)
                                        {
                                            qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(ButtonPos[i][j]) <<Qt::endl;
                                            qDebug() << SelectedElem[groupNum - 1][i][j] << Qt::endl;
                                            qDebug() << "координаты выбранного элемента" <<std::get<0>(ButtonPos[i][j])<<std::get<1>(ButtonPos[i][j]) << Qt::endl;
                                            qDebug() << "rad_src_pix" <<radCircScrPix << Qt::endl;
                                            if(!SelectedElem[groupNum - 1][i][j])
                                               SelectedElem[groupNum - 1][i][j] = true;
                                            else
                                               SelectedElem[groupNum - 1][i][j] = false;
                                            scene->clear();
                                            drawCirc();
                                            redrawing();
                                            i_fl = 1; //  флаги выхода из цикла
                                            j_fl = 1;
                                        }
                                    }
                                }
                              }
                         }
                 }
    }
}

/*!
 * \brief ArrangementOfElements::eventFilter
 * Метод позволяющий щелкать мышью по сцене
 * \param watched
 * \param event
 * \return
 */
bool ArrangementOfElements::eventFilter(QObject *watched, QEvent *event)
{
    if (!overlayType) // клик по прямоугольникам
        rectClick(watched, event);
    else if (overlayType) // клик по шестиугольникам
        hexClick(watched, event);
    return QDialog::eventFilter(watched, event);
}

/*!
 * \brief ArrangementOfElements::hideReshapeButtons
 * Скрывает кнопки "+" "-" в зависимости от количества рядов
 */
void ArrangementOfElements::hideReshapeButtons()
{
    if (numRow < 19)
    {
        ui->ButtonPlus_10->hide();
        ui->ButtonMinus_10->hide();
    }
    if (numRow < 17)
    {
        ui->ButtonPlus_9->hide();
        ui->ButtonMinus_9->hide();
    }
    if (numRow < 15)
    {
        ui->ButtonPlus_8->hide();
        ui->ButtonMinus_8->hide();
    }
    if (numRow < 13)
    {
        ui->ButtonPlus_7->hide();
        ui->ButtonMinus_7->hide();
    }
    if (numRow < 11)
    {
        ui->ButtonPlus_6->hide();
        ui->ButtonMinus_6->hide();
    }
    if (numRow < 9)
    {
        ui->ButtonPlus_5->hide();
        ui->ButtonMinus_5->hide();
    }
    if (numRow < 7)
    {
        ui->ButtonPlus_4->hide();
        ui->ButtonMinus_4->hide();
    }
    if (numRow < 5)
    {
        ui->ButtonPlus_3->hide();
        ui->ButtonMinus_3->hide();
    }
    if (numRow < 2)
    {
        ui->ButtonPlus_2->hide();
        ui->ButtonMinus_2->hide();
    }
    if (numRow < 1)
    {
        ui->ButtonPlus_1->hide();
        ui->ButtonMinus_1->hide();
    }
}

/*!
 * \brief ArrangementOfElements::disabledGroupButton
 * Метод делает кнопки групп недоступными
 * \param b
 */
void ArrangementOfElements::disabledGroupButton(bool b)
{
    ui->groupNumButton_1->setDisabled(b);
    ui->groupNumButton_2->setDisabled(b);
    ui->groupNumButton_3->setDisabled(b);
    ui->groupNumButton_4->setDisabled(b);
    ui->groupNumButton_5->setDisabled(b);
    ui->groupNumButton_6->setDisabled(b);
    ui->groupNumButton_7->setDisabled(b);
    ui->groupNumButton_8->setDisabled(b);
    ui->groupNumButton_9->setDisabled(b);
    ui->groupNumButton_10->setDisabled(b);
    ui->groupNumButton_11->setDisabled(b);
    ui->groupNumButton_12->setDisabled(b);
    ui->groupNumButton_13->setDisabled(b);
    ui->groupNumButton_14->setDisabled(b);
    ui->groupNumButton_15->setDisabled(b);
    ui->groupNumButton_16->setDisabled(b);
}

/*!
 * \brief ArrangementOfElements::wheelEvent
 * Метод позволяющий выполнять зум колесиком мыши
 * \param event
 */
void ArrangementOfElements::wheelEvent(QWheelEvent *event)
{
    // получаем указатель на элемент QGraphicsView из объекта ui
        QGraphicsView* graphicsView = ui->graphicsView;

        if (event->modifiers() & Qt::ControlModifier) {
            // зумирование при удерживании клавиши Ctrl
            QPointF scenePos = graphicsView->mapToScene(event->position().toPoint());
            int delta = event->angleDelta().y();
            qreal scaleFactor = 1.15;
            if (delta < 0) {
                scaleFactor = 1.0 / scaleFactor;
            }
            graphicsView->scale(scaleFactor, scaleFactor);
            QPointF newScenePos = graphicsView->mapToScene(event->position().toPoint());
            QPointF deltaScenePos = newScenePos - scenePos;
            graphicsView->horizontalScrollBar()->setValue(graphicsView->horizontalScrollBar()->value() + static_cast<int>(deltaScenePos.x()));
            graphicsView->verticalScrollBar()->setValue(graphicsView->verticalScrollBar()->value() + static_cast<int>(deltaScenePos.y()));
        } else {
            QDialog::wheelEvent(event);
        }
}

/*!
 * \brief ArrangementOfElements::drawCirc
 * Метод чертит окружность антенной решетки
 */
void ArrangementOfElements::drawCirc()
{
    QPen pen;
    int width_pen = 4*scaleKoef;
    pen.setWidth(width_pen); // Ширина круга
    scene->addEllipse(-diamPix/2 - width_pen, -diamPix/2 - width_pen,
                      diamPix + width_pen * 2, diamPix + width_pen * 2, pen);
}

/*!
 * \brief ArrangementOfElements::drawRect
 * Метод рисует на сцене прямоугольник
 * \param x Кооринаты x левого верхнего угла
 * \param z Кооринаты z левого верхнего угла
 * \param size_x_pix Размер прямоугольника в пикселях по x
 * \param size_z_pix Размер прямоугольника в пикселях по z
 * \param j
 * \param i
 */
void ArrangementOfElements::drawRect (int x, int z, int size_x_pix, int size_z_pix, int j, int i)
{
    if (regime)
    {
        if (SelectedElem[groupNum - 1][j][i])
        {
            QPen pen(Qt::black);
            pen.setWidth(int (scaleKoef));
            QGraphicsRectItem *received_pressed = scene->addRect(x, z, size_x_pix, size_z_pix);
            setText(x + size_x_pix / 2, z + size_z_pix / 2, j, i, Qt::white);
            received_pressed->setPen(pen);
            received_pressed->setBrush(QBrush(QColor(0, 0, 139)));
            received_pressed->show();
        }
        else
        {
            QPen pen(Qt::black);
            pen.setWidth(int (scaleKoef));
            QGraphicsRectItem *received = scene->addRect(x, z, size_x_pix, size_z_pix);
            setText(x + size_x_pix / 2, z + size_z_pix / 2, j, i, Qt::black);
            received->setPen(pen);
            received->setBrush(QBrush(QColor(64, 207, 255)));
            received->show();
        }
    }
    else
    {
        QPen pen(Qt::black);
        pen.setWidth(int (scaleKoef));
        QGraphicsRectItem *radiation = scene->addRect(x, z, size_x_pix, size_z_pix);
        setText(x + size_x_pix / 2, z + size_z_pix / 2, j, i, Qt::black);
        radiation->setPen(pen);
        radiation->setBrush(QBrush(QColor(244, 169, 0)));
        radiation->show();
    }


}

void ArrangementOfElements::setText(int cx, int cz, int j1, int i1, QColor color)
{
    if (textType == 1)
    {

    }
    else
    {
        QGraphicsTextItem *textItem;
        if(textType == 2)
            textItem = new QGraphicsTextItem(QString::number(j1 + 1) + "." + QString::number(i1 + 1));
        if(textType == 3)
        {
            int n = 1;
            for (int j = 0; j < ButtonPos.size(); j++){
                for (int i = 0; i < ButtonPos[j].size(); i++)
                {
                    std::get<2>(ButtonPos[j][i]) = n;
                    n++;
                }
            }
            textItem = new QGraphicsTextItem(QString::number(std::get<2>(ButtonPos[j1][i1])) );
        }
        if(textType == 4)
        {
            if (!antennaType) //амплитудная антенна
            {
                if(regime) // режим приема
                    textItem = new QGraphicsTextItem(QString::number(WeightCoef[0][j1][i1]));
                else
                    textItem = new QGraphicsTextItem(QString::number(WeightCoef[16][j1][i1]));

            }
            else if(!regime) // режим излучения
                textItem = new QGraphicsTextItem(QString::number(WeightCoef[16][j1][i1]));
            else
                textItem = new QGraphicsTextItem(QString::number(WeightCoef[groupNum - 1][j1][i1]));
        }
        textItem->setPos(cx, cz); // Установка позиции текста
        // Добавление элемента на сцену
        QFont font = textItem->font();
        font.setPointSizeF(font.pointSizeF() * scaleKoef);
        textItem->setFont(font);
        textItem->setDefaultTextColor(color);

        int textWidth = textItem->boundingRect().width();
        int textHeight = textItem->boundingRect().height();

        // Расчет позиции текста в середине прямоугольника
        int textX = cx - textWidth / 2;
        int textY = cz - textHeight / 2;

        // Установка позиции текста
        textItem->setPos(textX, textY);

        scene->addItem(textItem);
    }


}

void ArrangementOfElements::drawHex(int x, int y, int rad_circ_scr_pix, int j, int i)
{
    if (regime)
    {
        if (SelectedElem[groupNum - 1][j][i])
        {
            QPen pen(Qt::black);
            pen.setWidth(int (scaleKoef));
            QBrush brush;
            brush.setColor(QColor(0, 0, 139));
            brush.setStyle(Qt::SolidPattern);
            QPolygonF hex;
            hex << QPointF(x, y + rad_circ_scr_pix)
                << QPointF(x + int(rad_circ_scr_pix * cos(M_PI/6)), y + rad_circ_scr_pix / 2)
                << QPointF(x + int(rad_circ_scr_pix * cos(M_PI/6)), y - rad_circ_scr_pix / 2)
                << QPointF(x, y - rad_circ_scr_pix)
                << QPointF(x - int(rad_circ_scr_pix * cos(M_PI/6)), y - rad_circ_scr_pix / 2)
                << QPointF(x - int(rad_circ_scr_pix * cos(M_PI/6)), y + rad_circ_scr_pix / 2);
            scene->addPolygon(hex, pen, brush);
            setText(x, y, j, i, Qt::white);
        }
        else
        {
            QPen pen(Qt::black);
            pen.setWidth(int (scaleKoef));
            QBrush brush;
            brush.setColor(QColor(64, 207, 255));
            brush.setStyle(Qt::SolidPattern);
            QPolygonF hex;
            hex << QPointF(x, y + rad_circ_scr_pix)
                << QPointF(x + int(rad_circ_scr_pix * cos(M_PI/6.0)), y + rad_circ_scr_pix / 2.0)
                << QPointF(x + int(rad_circ_scr_pix * cos(M_PI/6.0)), y - rad_circ_scr_pix / 2.0)
                << QPointF(x, y - rad_circ_scr_pix)
                << QPointF(x - int(rad_circ_scr_pix * cos(M_PI/6.0)), y - rad_circ_scr_pix / 2.0)
                << QPointF(x - int(rad_circ_scr_pix * cos(M_PI/6.0)), y + rad_circ_scr_pix / 2.0);
            scene->addPolygon(hex, pen, brush);
            setText(x, y, j, i, Qt::black);
        }
    }
    else
    {
        QPen pen(Qt::black);
        pen.setWidth(int (scaleKoef));
        QBrush brush;
        brush.setColor(QColor(244, 169, 0));
        brush.setStyle(Qt::SolidPattern);
        QPolygonF hex;
        hex << QPointF(x, y + rad_circ_scr_pix)
            << QPointF(x + int(rad_circ_scr_pix * cos(M_PI/6.0)), y + rad_circ_scr_pix / 2.0)
            << QPointF(x + int(rad_circ_scr_pix * cos(M_PI/6.0)), y - rad_circ_scr_pix / 2.0)
            << QPointF(x, y - rad_circ_scr_pix)
            << QPointF(x - int(rad_circ_scr_pix * cos(M_PI/6.0)), y - rad_circ_scr_pix / 2.0)
            << QPointF(x - int(rad_circ_scr_pix * cos(M_PI/6.0)), y + rad_circ_scr_pix / 2.0);
        scene->addPolygon(hex, pen, brush);
        setText(x, y, j, i, Qt::black);
    }
}
/*
 * Перирисовка сцены
*/
void ArrangementOfElements::redrawing()
{
    if (!overlayType) // прямоугольная антенна
        redrawingRect();
    else if (overlayType) // шестиугольная антенна
        redrawingHex();
}


void ArrangementOfElements::redrawingRect()
{
    int x, z, n;
    sizeXPix = int (sizeX / radAnt * (diamPix / 2.0));
    sizeZPix = int (sizeZ / radAnt * (diamPix / 2.0));
    distXPix = int (distX / radAnt * (diamPix / 2.0));
    distZPix = int (distZ / radAnt * (diamPix / 2.0));
    if (numRow & 1) // нечетное число рядов
    {
    z = -sizeZPix * 3 / 2 - distZPix;
    for (int j = numRow / 2 - 1; j >= 0; j--) //
    {
        if (CurrNumElem[j] & 1) // для нечетных
        {
            x = -sizeXPix / 2;
            for (int i = 0; i < CurrNumElem[j] / 2 + 1; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -sizeXPix / 2 - sizeXPix - distXPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        else // для четных
        {
            x = distXPix / 2;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -distXPix / 2 - sizeXPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        z -= (sizeZPix + distZPix);
    }
    z = -sizeZPix / 2;
    for (int j = numRow / 2; j < numRow ; j++)
    {
        if (CurrNumElem[j] & 1) // для нечетных
        {
            x = -sizeXPix / 2;
            for (int i = 0; i < CurrNumElem[j] / 2 + 1; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -sizeXPix / 2 - sizeXPix - distXPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        else // для четных
        {
            x = distXPix / 2;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -distXPix / 2 - sizeXPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        z += sizeZPix + distZPix;
    }
 }
    else // для четного количества рядов
    {
        z = -distZPix / 2 - sizeZPix ;
        for (int j = numRow / 2 - 1; j >= 0; j--)
        {
            if (CurrNumElem[j] & 1) // для нечетных
            {
                x = -sizeXPix / 2;
                for (int i = 0; i < CurrNumElem[j] / 2 + 1; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                    ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                    x += sizeXPix + distXPix;
                }
                x = -sizeXPix / 2 - sizeXPix - distXPix;
                for (int i = 0; i < CurrNumElem[j] / 2; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                    ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                    x -= (sizeXPix + distXPix);
                }
            }
            else // для четных
            {
                x = distXPix / 2;
                for (int i = 0; i < CurrNumElem[j] / 2; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                    ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                    x += sizeXPix + distXPix;
                }
                x = -distXPix / 2 - sizeXPix;
                for (int i = 0; i < CurrNumElem[j] / 2; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                    ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                    x -= (sizeXPix + distXPix);
                }
            }
            z -= (sizeZPix + distZPix);
        }
        z = distZPix / 2;
    for (int j = numRow / 2; j < numRow ; j++)
    {
        if (CurrNumElem[j] & 1) // для нечетных
        {
            x = -sizeXPix / 2;
            for (int i = 0; i < CurrNumElem[j] / 2 + 1; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -sizeXPix / 2 - sizeXPix - distXPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        else // для четных
        {
            x = distXPix / 2;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -distXPix / 2 - sizeXPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        z += sizeZPix + distZPix;
    }
 }
    n = 1;
    for (int j = 0; j < ButtonPos.size(); j++){
        for (int i = 0; i < ButtonPos[j].size(); i++)
        {
            std::get<2>(ButtonPos[j][i]) = n;
            n++;
        }
    }
}


void ArrangementOfElements::redrawingHex()
{
    int x, z, n;
    radCircScrPix = int (radCircScr / radAnt * (diamPix / 2.0));
    distHexPix = int (distHex / radAnt * (diamPix / 2.0));
    x = 0;

    // нижняя половина
    z = 0;
    for (int j = numRow / 2; j < numRow ; j++)
    {
        if (CurrNumElem[j] & 1) // для нечетных
        {
            x = 0;
            for (int i = 0; i < CurrNumElem[j] / 2 + 1; i++)
            {
                drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += (2 * radCircScrPix * cos(M_PI/6) + distHexPix);
            }
            x = - 2*radCircScrPix * cos(M_PI/6) - distHexPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (2 * radCircScrPix * cos(M_PI/6) + distHexPix);
            }
        }
        else // для четных
        {
            x = (radCircScrPix * cos(M_PI/6) + distHexPix / 2);
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
            }
            x = -(radCircScrPix * cos(M_PI/6) + distHexPix / 2);
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
            }
        }
        z += (radCircScrPix * 3/2 + distHexPix * cos(M_PI/6));
    }
 // верхняя половина
    z = -(radCircScrPix * 3/2 + distHexPix * cos(M_PI/6));
    for (int j = numRow / 2 - 1; j >= 0; j--)
    {
        if (CurrNumElem[j] & 1) // для нечетных
        {
            x = 0;
            for (int i = 0; i < CurrNumElem[j] / 2 + 1; i++)
            {
                drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 + i);
                ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += 2* radCircScrPix * cos(M_PI/6) + distHexPix;
            }
            x = - 2 *radCircScrPix * cos(M_PI/6) - distHexPix;
            for (int i = 0; i < CurrNumElem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 - 1 - i);
                ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= 2* radCircScrPix * cos(M_PI/6) + distHexPix;
            }
        }
        else // для четных
        {
           x = radCircScrPix * cos(M_PI/6) + distHexPix / 2;
           for (int i = 0; i < CurrNumElem[j] / 2; i++)
           {
               drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 + i);
               ButtonPos[j][CurrNumElem[j] / 2 + i] = std::make_tuple(x, z, 1);
               x += 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
           }
           x = -radCircScrPix * cos(M_PI/6) - distHexPix / 2;
           for (int i = 0; i < CurrNumElem[j] / 2; i++)
           {
               drawHex(x, z, radCircScrPix, j, CurrNumElem[j] / 2 - 1 - i);
               ButtonPos[j][CurrNumElem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
               x -= 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
           }
        }
        z -= (radCircScrPix * 3/2 + distHexPix * cos(M_PI/6));
    }
    n = 1;
    for (int j = 0; j < ButtonPos.size(); j++){
        for (int i = 0; i < ButtonPos[j].size(); i++)
        {
            std::get<2>(ButtonPos[j][i]) = n;
            n++;
        }
    }
}
/*
  Слот
*/
void ArrangementOfElements::slotMainToArrange(double size_x1, double size_z1, double dist_x1, double dist_z1,
                                                   double rad_circ_scr1, double dist1,
                                                   double rad_ant1, int num_row1, QVector<int> Max_elem1, QVector<int> Curr_num_elem1,
                                                   std::array<QVector<QVector<double>>,17> Weight_coef1, std::array<QVector<QVector<bool>>, 16> Selected_elem1,
                                                   int antenna_type, int overlay_type)
{
    antennaType = antenna_type;
    overlayType = overlay_type;
    sizeX = size_x1; sizeZ = size_z1; distX = dist_x1;
    distZ = dist_z1; radAnt = rad_ant1; numRow = num_row1;
    radCircScr = rad_circ_scr1; distHex = dist1;
    SelectedElem = Selected_elem1;
    MaxElem = Max_elem1;
    WeightCoef = Weight_coef1;
    CurrNumElem = Curr_num_elem1;
    ButtonPos.resize(CurrNumElem.size());
    for (int i = 0; i < CurrNumElem.size(); i++)
    {
        ButtonPos[i].resize(CurrNumElem[i]);
    }
    hideReshapeButtons();
    // Изначальное отображение сцены
    regime = true;
    redrawing();
    ui->radioButtonReceive->setChecked(true);
}

void ArrangementOfElements::slotSelectWeightToArrange(double weight1, int i, int j)
{
    if(!regime) // режим излучения
        WeightCoef[16][i][j] = weight1;
    else if (antennaType == 0) // амплитудная антенна
        WeightCoef[0][i][j] = weight1;
    else
        WeightCoef[groupNum - 1][i][j] = weight1;

    redrawing();
}


ArrangementOfElements::~ArrangementOfElements()
{
    delete ui;
}

//режим приема
void ArrangementOfElements::on_radioButtonReceive_clicked(bool checked)
{
    if (checked){
        QWidget clear;
        regime = true;
        redrawing();
        disabledGroupButton(false);

        groupNum = 1;
        ui->groupNumButton_1->setDisabled(true);
    }
}

//режим передачи
void ArrangementOfElements::on_radioButtonRadiation_clicked(bool checked)
{
    if (checked){
        QWidget clear;
        regime = false;
        redrawing();
        disabledGroupButton(true);
    }
}

void ArrangementOfElements::on_ButtonPlus_1_clicked()
{
    reshapePlus(0);
}

void ArrangementOfElements::on_ButtonMinus_1_clicked()
{
    reshapeMinus(0);
}

void ArrangementOfElements::on_ButtonPlus_2_clicked()
{
    reshapePlus(1);
}

void ArrangementOfElements::on_ButtonMinus_2_clicked()
{
    reshapeMinus(1);
}

void ArrangementOfElements::on_ButtonPlus_3_clicked()
{
    reshapePlus(2);
}

void ArrangementOfElements::on_ButtonMinus_3_clicked()
{
    reshapeMinus(2);
}

void ArrangementOfElements::on_ButtonPlus_4_clicked()
{
    reshapePlus(3);
}

void ArrangementOfElements::on_ButtonMinus_4_clicked()
{
    reshapeMinus(3);
}

void ArrangementOfElements::on_ButtonPlus_5_clicked()
{
    reshapePlus(4);
}

void ArrangementOfElements::on_ButtonMinus_5_clicked()
{
    reshapeMinus(4);
}

void ArrangementOfElements::on_ButtonPlus_6_clicked()
{
    reshapePlus(5);
}

void ArrangementOfElements::on_ButtonMinus_6_clicked()
{
    reshapeMinus(5);
}

void ArrangementOfElements::on_ButtonPlus_7_clicked()
{
    reshapePlus(6);
}

void ArrangementOfElements::on_ButtonMinus_7_clicked()
{
    reshapeMinus(6);
}


void ArrangementOfElements::reshapePlus(int n)
{
    if (overlayType and (CurrNumElem[numRow / 2 - n] != 0
                          or ((numRow - n) % 2 == 0)))   // для шестиугольных элементов
    {

        if((CurrNumElem[numRow / 2 - n] < MaxElem[numRow / 2 - n]) and
                (CurrNumElem[numRow / 2 + n] < MaxElem[numRow / 2 + n]))
        {
            if (n)
                CurrNumElem[numRow / 2 - n] += 2;
            CurrNumElem[numRow / 2 + n] += 2;
            scene->clear();
            if (n)
            {
                ButtonPos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                for (int i = 0; i < 17; i++)
                    WeightCoef[i][numRow / 2 + n].push_back(1);
                ButtonPos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                for (int i = 0; i < 17; i++)
                    WeightCoef[i][numRow / 2 + n].push_back(1);
                for (unsigned int i = 0; i < SelectedElem.size(); i++)
                {
                    SelectedElem[i][numRow / 2 + n].push_back(false);
                    SelectedElem[i][numRow / 2 + n].push_back(false);
                }
            }
            ButtonPos[numRow / 2 - n].push_back(std::make_tuple(0, 0, 0));
            for (int i = 0; i < 17; i++)
                WeightCoef[i][numRow / 2 - n].push_back(1);
            ButtonPos[numRow / 2 - n].push_back(std::make_tuple(0, 0, 0));
            for (int i = 0; i < 17; i++)
                WeightCoef[i][numRow / 2 - n].push_back(1);
            for (unsigned int i = 0; i < SelectedElem.size(); i++)
            {
                SelectedElem[i][numRow / 2 - n].push_back(false);
                SelectedElem[i][numRow / 2 - n].push_back(false);
            }
        }
        drawCirc();
        redrawing();

    }
    else  // для четырехугольных элементов
    {
        if (numRow % 2 == 1) // нечетное число рядов
        {
            if((CurrNumElem[numRow / 2 - n] < MaxElem[numRow / 2 - n]) and
                    (CurrNumElem[numRow / 2 + n] < MaxElem[numRow / 2 + n]))
            {
                if (n)
                    CurrNumElem[numRow / 2 - n] += 1;
                CurrNumElem[numRow / 2 + n] += 1;
                scene->clear();
                if (n)
                {
                    ButtonPos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                    for (int i = 0; i < 17; i++)
                        WeightCoef[i][numRow / 2 + n].push_back(1);
                    for (unsigned int i = 0; i < SelectedElem.size(); i++)
                        SelectedElem[i][numRow / 2 + n].push_back(false);
                }
                ButtonPos[numRow / 2 - n].push_back(std::make_tuple(0, 0, 0));
                for (int i = 0; i < 17; i++)
                    WeightCoef[i][numRow / 2 - n].push_back(1);
                for (unsigned int i = 0; i < SelectedElem.size(); i++)
                    SelectedElem[i][numRow / 2 - n].push_back(false);
            }
            drawCirc();
            redrawing();
        }
        else  // четное число рядов
            {
                if((CurrNumElem[numRow / 2 + n] < MaxElem[numRow / 2 + n]) and
                        (CurrNumElem[numRow / 2 - n - 1] < MaxElem[numRow / 2 - n - 1]))
                {
                    CurrNumElem[numRow / 2 + n] += 1;
                    CurrNumElem[numRow / 2 - n - 1] += 1;
                    scene->clear();
                    ButtonPos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                    for (int i = 0; i < 17; i++)
                        WeightCoef[i][numRow / 2 + n].push_back(1);
                    for (unsigned int i = 0; i < SelectedElem.size(); i++)
                        SelectedElem[i][numRow / 2 + n].push_back(false);
                    ButtonPos[numRow / 2 - n - 1].push_back(std::make_tuple(0, 0, 0));
                    for (int i = 0; i < 17; i++)
                        WeightCoef[i][numRow / 2 - n - 1].push_back(1);
                    for (unsigned int i = 0; i < SelectedElem.size(); i++)
                        SelectedElem[i][numRow / 2 - n - 1].push_back(false);
                    drawCirc();
                    redrawing();
                }
            }
    }
}

void ArrangementOfElements::reshapeMinus(int n)
{
    if (overlayType and CurrNumElem[numRow / 2 - n] != 1 // для шестиугольных элементов
            and CurrNumElem[numRow / 2 + n] != 1)
    {
            if((CurrNumElem[numRow / 2 - n] > 0) and
                    (CurrNumElem[numRow / 2 + n] > 0))
            {
                if (n)
                    CurrNumElem[numRow / 2 - n] -= 2;
                CurrNumElem[numRow / 2 + n] -= 2;
                scene->clear();
                if (n)
                {
                    ButtonPos[numRow / 2 + n].pop_back();
                    ButtonPos[numRow / 2 + n].pop_back();
                    for (int i = 0; i < 17; i++)
                    {
                        WeightCoef[i][numRow / 2 + n].pop_back();
                        WeightCoef[i][numRow / 2 + n].pop_back();
                    }
                    for (unsigned int i = 0; i < SelectedElem.size(); i++)
                    {
                        SelectedElem[i][numRow / 2 + n].pop_back();
                        SelectedElem[i][numRow / 2 + n].pop_back();
                    }
                }
                ButtonPos[numRow / 2 - n].pop_back();
                ButtonPos[numRow / 2 - n].pop_back();
                for (int i = 0; i < 17; i++)
                {
                    WeightCoef[i][numRow / 2 - n].pop_back();
                    WeightCoef[i][numRow / 2 - n].pop_back();
                }
                for (unsigned int i = 0; i < SelectedElem.size(); i++)
                {
                    SelectedElem[i][numRow / 2 - n].pop_back();
                    SelectedElem[i][numRow / 2 - n].pop_back();
                }
                drawCirc();
                redrawing();
            }
    }
    else // для чутырехугольных элементов
    {
        if (numRow % 2 == 1) // нечетное число рядов
        {
            if((CurrNumElem[numRow / 2 - n] > 0) and
                    (CurrNumElem[numRow / 2 + n] > 0))
            {
                if (n)
                    CurrNumElem[numRow / 2 - n] -= 1;
                CurrNumElem[numRow / 2 + n] -= 1;
                scene->clear();
                if (n)
                {
                    ButtonPos[numRow / 2 + n].pop_back();
                    for (int i = 0; i < 17; i++)
                        WeightCoef[i][numRow / 2 + n].pop_back();
                    for (unsigned int i = 0; i < SelectedElem.size(); i++)
                        SelectedElem[i][numRow / 2 + n].pop_back();
                }
                ButtonPos[numRow / 2 - n].pop_back();
                for (int i = 0; i < 17; i++)
                    WeightCoef[i][numRow / 2 - n].pop_back();
                for (unsigned int i = 0; i < SelectedElem.size(); i++)
                    SelectedElem[i][numRow / 2 - n].pop_back();
                drawCirc();
                redrawing();
            }
        }
        else // четное число рядов
        {
            if((CurrNumElem[numRow / 2 + n] > 0) and
                    (CurrNumElem[numRow / 2 - n - 1] > 0))
            {
                CurrNumElem[numRow / 2 + n] -= 1;
                CurrNumElem[numRow / 2 - n - 1] -= 1;
                scene->clear();
                ButtonPos[numRow / 2 + n].pop_back();
                ButtonPos[numRow / 2 - n - 1].pop_back();
                for (int i = 0; i < 17; i++)
                {
                    WeightCoef[i][numRow / 2 + n].pop_back();
                    WeightCoef[i][numRow / 2 - n - 1].pop_back();
                }
                for (unsigned int i = 0; i < SelectedElem.size(); i++)
                {
                    SelectedElem[i][numRow / 2 + n].pop_back();
                    SelectedElem[i][numRow / 2 - n - 1].pop_back();
                }
                drawCirc();
                redrawing();
            }
        }
    }
}


void ArrangementOfElements::on_groupNumButton_1_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_1->setDisabled(true);
    groupNum = 1;
    redrawing();

}

void ArrangementOfElements::on_groupNumButton_2_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_2->setDisabled(true);
    groupNum = 2;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_3_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_3->setDisabled(true);
    groupNum = 3;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_4_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_4->setDisabled(true);
    groupNum = 4;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_5_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_5->setDisabled(true);
    groupNum = 5;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_6_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_6->setDisabled(true);
    groupNum = 6;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_7_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_7->setDisabled(true);
    groupNum = 7;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_8_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_8->setDisabled(true);
    groupNum = 8;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_9_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_9->setDisabled(true);
    groupNum = 9;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_10_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_10->setDisabled(true);
    groupNum = 10;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_11_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_11->setDisabled(true);
    groupNum = 11;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_12_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_12->setDisabled(true);
    groupNum = 12;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_13_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_13->setDisabled(true);
    groupNum = 13;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_14_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_14->setDisabled(true);
    groupNum = 14;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_15_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_15->setDisabled(true);
    groupNum = 15;
    redrawing();
}

void ArrangementOfElements::on_groupNumButton_16_clicked()
{
    disabledGroupButton(false);
    ui->groupNumButton_16->setDisabled(true);
    groupNum = 16;
    redrawing();
}

void ArrangementOfElements::on_saveButton_clicked()
{
    double scaleKoef1;
    if (overlayType == 0)
        scaleKoef1 = sizeX / sizeXPix ;
    else
        scaleKoef1 = radCircScr / radCircScrPix ;

    if (overlayType != 0)
    {
        CenterPos.resize(ButtonPos.size());
        for (int i = 0; i < ButtonPos.size(); i++)
        {
            CenterPos[i].resize(ButtonPos[i].size());
            for (int j = 0; j < ButtonPos[i].size(); j++)
            {
                CenterPos[i][j].first = std::get<0>(ButtonPos[i][j]) ;
                CenterPos[i][j].second = -(std::get<1>(ButtonPos[i][j]));
                CenterPos[i][j].first = round(CenterPos[i][j].first * scaleKoef1 * 100)/100;
                CenterPos[i][j].second = round(CenterPos[i][j].second * scaleKoef1 * 100)/100;
            }
        }
    }
    if (overlayType == 0)
    {
        CenterPos.resize(ButtonPos.size());
        for (int i = 0; i < ButtonPos.size(); i++)
        {
            CenterPos[i].resize(ButtonPos[i].size());
            for (int j = 0; j < ButtonPos[i].size(); j++)
            {
                CenterPos[i][j].first = (std::get<0>(ButtonPos[i][j]) + double(sizeXPix) / 2.0) * scaleKoef1;
                CenterPos[i][j].second = -(std::get<1>(ButtonPos[i][j]) + double(sizeZPix) / 2.0) * scaleKoef1;
                CenterPos[i][j].first = round(CenterPos[i][j].first * 100)/100;
                CenterPos[i][j].second = round(CenterPos[i][j].second * 100)/100;
            }
        }

    }

    if(antennaType == 1) // фазовая антенна
    {
        for (int grp = 0; grp < 16; grp++)
        {
            double YclNum = 0, Den = 0, ZclNum = 0;
            for (int i = 0; i < CenterPos.size(); i++)
            {
                for (int j = 0; j < CenterPos[i].size(); j++)
                {
                    if(!SelectedElem[grp][i][j])
                        continue;
                    YclNum += WeightCoef[grp][i][j] * CenterPos[i][j].first;
                    ZclNum += WeightCoef[grp][i][j] * CenterPos[i][j].second;
                    Den += WeightCoef[grp][i][j];
                }
            }
        if (Den)
        {
            Centroids[grp].second = ZclNum / Den;
            Centroids[grp].first = YclNum / Den;
            Arr_Denum[grp] = Den;
        }
        qDebug() << Centroids[grp];
        }
        qDebug() << CenterPos;
    }

    int numElem = std::get<2>(ButtonPos[ButtonPos.size() - 1][ButtonPos[ButtonPos.size() - 1].size() - 1]);
    emit signalArrangeToMain(CurrNumElem, WeightCoef, CenterPos, Centroids,
                             Arr_Denum, SelectedElem, numElem);
    QWidget::close();
}


void ArrangementOfElements::on_clcButton_clicked()
{
    if(textType != 1)
    {
        textType = 1;
        redrawing();
    }
}


void ArrangementOfElements::on_colRowButton_clicked()
{
    if(textType != 2)
    {
        textType = 2;
        redrawing();
    }
}


void ArrangementOfElements::on_numButton_clicked()
{
    if(textType != 3)
    {
        textType = 3;
        redrawing();
    }
}


void ArrangementOfElements::on_weightButton_clicked()
{
    if(textType != 4)
    {
        textType = 4;
        redrawing();
    }
}
