#include "arrangementOfElements.h"
#include "selectWeight.h"
#include "ui_arrangementOfElements.h"



//#40cfff приемная
//f4a900ff RGBA

Arrangement_of_elements::Arrangement_of_elements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arrangement_of_elements)
{
    diamPix = 500 * scaleKoef; // число пикселей в диаметре
    channelNum = 1;
    ui->setupUi(this);
    ui->ChannelNumButton_1->setDisabled(true);
    selectedChanelNum = 1;
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::white);
    drawCirc();
    scene->installEventFilter(this);
    ui->graphicsView->scale(1 / (scaleKoef), 1 / (scaleKoef)); // начальный масштаб
}


bool Arrangement_of_elements::rectCheck(int x, int y, int vx, int vy)
{
    return x >= vx and
           x <= vx + sizeXPix and
           y >= vy and
           y <= vy + sizeZPix;
}

void Arrangement_of_elements::rectClick(QObject *watched, QEvent *event)
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
                                        Select_weight window;
                                        connect(this, &Arrangement_of_elements::signalArrangeToSelectWeight, &window, &Select_weight::slotArrangeToSelectWeigth);
                                        if (!regime)
                                            emit signalArrangeToSelectWeight(WeightCoef[16][i][j], i, j, std::get<2>(ButtonPos[i][j]));
                                        else if(regime)
                                            emit signalArrangeToSelectWeight(WeightCoef[channelNum - 1][i][j], i, j, std::get<2>(ButtonPos[i][j]));
                                        connect(&window, &Select_weight::signalSelectWeightToArrange, this, &Arrangement_of_elements::slotSelectWeightToArrange);
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

                                            if(!SelectedElem[channelNum - 1][i][j])
                                               SelectedElem[channelNum - 1][i][j] = true;
                                            else
                                               SelectedElem[channelNum - 1][i][j] = false;
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



bool Arrangement_of_elements::hexCheck(int cx, int cy, int x, int y)
{
    const int sides = 6;
    double angle = M_PI / 6.0; // 30 градусов в радиан
    double vertexX[sides];
    double vertexY[sides];
    for (int i = 0; i < sides; ++i) {
        vertexX[i] = cx + radCircScrPix * cos(angle);
        vertexY[i] = cy + radCircScrPix * sin(angle);
        angle += M_PI / 3.0; // 60 градусов в радиан
    }

    // Проверяет принадлежит ли точка шестиугольнику
    bool inside = false;
    for (int i = 0, j = sides - 1; i < sides; j = i++) {
        if (((vertexY[i] > y) != (vertexY[j] > y)) and
            (x < (vertexX[j] - vertexX[i]) * (y - vertexY[i]) / (vertexY[j] - vertexY[i]) + vertexX[i])) {
            inside = !inside;
        }
    }
    return inside;
}

void Arrangement_of_elements::hexClick(QObject *watched, QEvent *event)
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
                                       qDebug() << WeightCoef[channelNum - 1] << Qt::endl;
                                       Select_weight window;
                                       connect(this, &Arrangement_of_elements::signalArrangeToSelectWeight, &window, &Select_weight::slotArrangeToSelectWeigth);
                                       emit signalArrangeToSelectWeight(WeightCoef[channelNum - 1][i][j], i, j, std::get<2>(ButtonPos[i][j]));
                                       connect(&window, &Select_weight::signalSelectWeightToArrange, this, &Arrangement_of_elements::slotSelectWeightToArrange);
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
                                            qDebug() << SelectedElem[channelNum - 1][i][j] << Qt::endl;
                                            qDebug() << "координаты выбранного элемента" <<std::get<0>(ButtonPos[i][j])<<std::get<1>(ButtonPos[i][j]) << Qt::endl;
                                            qDebug() << "rad_src_pix" <<radCircScrPix << Qt::endl;
                                            if(!SelectedElem[channelNum - 1][i][j])
                                               SelectedElem[channelNum - 1][i][j] = true;
                                            else
                                               SelectedElem[channelNum - 1][i][j] = false;
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


bool Arrangement_of_elements::eventFilter(QObject *watched, QEvent *event)
{
    if (!overlayType) // клик по прямоугольникам
        rectClick(watched, event);
    else if (overlayType) // клик по шестиугольникам
        hexClick(watched, event);
    return QDialog::eventFilter(watched, event);
}


void Arrangement_of_elements::hideReshapeButtons()
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

void Arrangement_of_elements::disabledChannelButton(bool b)
{
    ui->ChannelNumButton_1->setDisabled(b);
    ui->ChannelNumButton_2->setDisabled(b);
    ui->ChannelNumButton_3->setDisabled(b);
    ui->ChannelNumButton_4->setDisabled(b);
    ui->ChannelNumButton_5->setDisabled(b);
    ui->ChannelNumButton_6->setDisabled(b);
    ui->ChannelNumButton_7->setDisabled(b);
    ui->ChannelNumButton_8->setDisabled(b);
    ui->ChannelNumButton_9->setDisabled(b);
    ui->ChannelNumButton_10->setDisabled(b);
    ui->ChannelNumButton_11->setDisabled(b);
    ui->ChannelNumButton_12->setDisabled(b);
    ui->ChannelNumButton_13->setDisabled(b);
    ui->ChannelNumButton_14->setDisabled(b);
    ui->ChannelNumButton_15->setDisabled(b);
    ui->ChannelNumButton_16->setDisabled(b);
}

void Arrangement_of_elements::wheelEvent(QWheelEvent *event)
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

void Arrangement_of_elements::drawCirc()
{
    QPen pen;
    int width_pen = 4*scaleKoef;
    pen.setWidth(width_pen); // Ширина круга
    scene->addEllipse(-diamPix/2 - width_pen, -diamPix/2 - width_pen,
                      diamPix + width_pen * 2, diamPix + width_pen * 2, pen);
}


void Arrangement_of_elements::drawRect (int x, int z, int size_x_pix, int size_z_pix, int j, int i)
{
    if (regime)
    {
        if (SelectedElem[channelNum - 1][j][i])
        {
            QPen pen(Qt::black);
            pen.setWidth(int (scaleKoef));
            QGraphicsRectItem *received_pressed = scene->addRect(x, z, size_x_pix, size_z_pix);
            received_pressed->setPen(pen);
            received_pressed->setBrush(QBrush(QColor(0, 0, 139)));
            received_pressed->show();
        }
        else
        {
            QPen pen(Qt::black);
            pen.setWidth(int (scaleKoef));
            QGraphicsRectItem *received = scene->addRect(x, z, size_x_pix, size_z_pix);
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
        radiation->setPen(pen);
        radiation->setBrush(QBrush(QColor(244, 169, 0)));
        radiation->show();
    }


}

void Arrangement_of_elements::drawHex(int x, int y, int rad_circ_scr_pix, int j, int i)
{
    if (regime)
    {
        if (SelectedElem[channelNum - 1][j][i])
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
    }
}
/*
 * Перирисовка сцены
*/
void Arrangement_of_elements::redrawing()
{
    if (!overlayType) // прямоугольная антенна
        redrawingRect();
    else if (overlayType) // шестиугольная антенна
        redrawingHex();
}


void Arrangement_of_elements::redrawingRect()
{
    int x, z, n;
    sizeXPix = int (sizeX / radAnt * (diamPix / 2));
    sizeZPix = int (sizeZ / radAnt * (diamPix / 2));
    distXPix = int (distX / radAnt * (diamPix / 2));
    distZPix = int (distZ / radAnt * (diamPix / 2));
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


void Arrangement_of_elements::redrawingHex()
{
    int x, z, n;
    radCircScrPix = int (radCircScr / radAnt * (diamPix / 2));
    distHexPix = int (distHex / radAnt * (diamPix / 2));
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

    qDebug() << "Button_pos" <<Qt::endl;
    for (int i = 0; i < ButtonPos.size(); i++)
    {
        for (int j = 0; j < ButtonPos[i].size(); j++)
        {
            qDebug() << std::get<0>(ButtonPos[i][j]) << std::get<1>(ButtonPos[i][j]) << " ";
        }
        qDebug() <<Qt::endl;
    }
}
/*
  Слот
*/
void Arrangement_of_elements::slotMainToArrange(double size_x1, double size_z1, double dist_x1, double dist_z1,
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

void Arrangement_of_elements::slotSelectWeightToArrange(double weight1, int i, int j)
{
    if(!regime)
        WeightCoef[16][i][j] = weight1;
    else if (regime)
        WeightCoef[channelNum - 1][i][j] = weight1;
}


Arrangement_of_elements::~Arrangement_of_elements()
{
    delete ui;
}

//режим приема
void Arrangement_of_elements::on_radioButtonReceive_clicked(bool checked)
{
    if (checked){
        QWidget clear;
        regime = true;
        redrawing();
        disabledChannelButton(false);

        channelNum = 1;
        ui->ChannelNumButton_1->setDisabled(true);
    }
}

//режим передачи
void Arrangement_of_elements::on_radioButtonRadiation_clicked(bool checked)
{
    if (checked){
        QWidget clear;
        regime = false;
        redrawing();
        disabledChannelButton(true);
    }
}

void Arrangement_of_elements::on_ButtonPlus_1_clicked()
{
    reshapePlus(0);
}

void Arrangement_of_elements::on_ButtonMinus_1_clicked()
{
    reshapeMinus(0);
}

void Arrangement_of_elements::on_ButtonPlus_2_clicked()
{
    reshapePlus(1);
}

void Arrangement_of_elements::on_ButtonMinus_2_clicked()
{
    reshapeMinus(1);
}

void Arrangement_of_elements::on_ButtonPlus_3_clicked()
{
    reshapePlus(2);
}

void Arrangement_of_elements::on_ButtonMinus_3_clicked()
{
    reshapeMinus(2);
}

void Arrangement_of_elements::on_ButtonPlus_4_clicked()
{
    reshapePlus(3);
}

void Arrangement_of_elements::on_ButtonMinus_4_clicked()
{
    reshapeMinus(3);
}

void Arrangement_of_elements::on_ButtonPlus_5_clicked()
{
    reshapePlus(4);
}

void Arrangement_of_elements::on_ButtonMinus_5_clicked()
{
    reshapeMinus(4);
}

void Arrangement_of_elements::on_ButtonPlus_6_clicked()
{
    reshapePlus(5);
}

void Arrangement_of_elements::on_ButtonMinus_6_clicked()
{
    reshapeMinus(5);
}

void Arrangement_of_elements::on_ButtonPlus_7_clicked()
{
    reshapePlus(6);
}

void Arrangement_of_elements::on_ButtonMinus_7_clicked()
{
    reshapeMinus(6);
}


void Arrangement_of_elements::reshapePlus(int n)
{
    if (overlayType and (CurrNumElem[numRow / 2 - n] != 0
                          or ((numRow - n) % 2 == 0)))
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
    else
    {
        if (numRow & 1)
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
        else
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

void Arrangement_of_elements::reshapeMinus(int n)
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
                    WeightCoef[numRow / 2 + n].pop_back();
                    WeightCoef[numRow / 2 + n].pop_back();
                    for (unsigned int i = 0; i < SelectedElem.size(); i++)
                    {
                        SelectedElem[i][numRow / 2 + n].pop_back();
                        SelectedElem[i][numRow / 2 + n].pop_back();
                    }
                }
                ButtonPos[numRow / 2 - n].pop_back();
                ButtonPos[numRow / 2 - n].pop_back();
                WeightCoef[numRow / 2 - n].pop_back();
                WeightCoef[numRow / 2 - n].pop_back();
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
        if (numRow & 1)
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
                    WeightCoef[numRow / 2 + n].pop_back();
                    for (unsigned int i = 0; i < SelectedElem.size(); i++)
                        SelectedElem[i][numRow / 2 + n].pop_back();
                }
                ButtonPos[numRow / 2 - n].pop_back();
                WeightCoef[numRow / 2 - n].pop_back();
                for (unsigned int i = 0; i < SelectedElem.size(); i++)
                    SelectedElem[i][numRow / 2 - n].pop_back();
                drawCirc();
                redrawing();
            }
        }
        else
        {
            if((CurrNumElem[numRow / 2 + n] > 0) and
                    (CurrNumElem[numRow / 2 - n - 1] > 0))
            {
                CurrNumElem[numRow / 2 + n] -= 1;
                CurrNumElem[numRow / 2 - n - 1] -= 1;
                scene->clear();
                ButtonPos[numRow / 2 + n].pop_back();
                ButtonPos[numRow / 2 - n - 1].pop_back();
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


void Arrangement_of_elements::on_ChannelNumButton_1_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_1->setDisabled(true);
    channelNum = 1;
    redrawing();

}

void Arrangement_of_elements::on_ChannelNumButton_2_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_2->setDisabled(true);
    channelNum = 2;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_3_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_3->setDisabled(true);
    channelNum = 3;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_4_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_4->setDisabled(true);
    channelNum = 4;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_5_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_5->setDisabled(true);
    channelNum = 5;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_6_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_6->setDisabled(true);
    channelNum = 6;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_7_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_7->setDisabled(true);
    channelNum = 7;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_8_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_8->setDisabled(true);
    channelNum = 8;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_9_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_9->setDisabled(true);
    channelNum = 9;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_10_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_10->setDisabled(true);
    channelNum = 10;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_11_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_11->setDisabled(true);
    channelNum = 11;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_12_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_12->setDisabled(true);
    channelNum = 12;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_13_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_13->setDisabled(true);
    channelNum = 13;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_14_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_14->setDisabled(true);
    channelNum = 14;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_15_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_15->setDisabled(true);
    channelNum = 15;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_16_clicked()
{
    disabledChannelButton(false);
    ui->ChannelNumButton_16->setDisabled(true);
    channelNum = 16;
    redrawing();
}

void Arrangement_of_elements::on_saveButton_clicked()
{
    emit signalArrangeToMain(CurrNumElem, WeightCoef, ButtonPos,
                                sizeXPix, sizeZPix, distXPix, distXPix,
                                radCircScrPix, distHexPix);
    QWidget::close();
}

