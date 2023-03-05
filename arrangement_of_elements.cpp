#include "arrangement_of_elements.h"
#include "select_weight.h"
#include "ui_arrangement_of_elements.h"



//#40cfff приемная
//f4a900ff RGBA

Arrangement_of_elements::Arrangement_of_elements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arrangement_of_elements)
{
    diamPix = 450; // число пикселей в диаметре
    channelNum = 1;
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::white);
    drawCirc();
    scene->installEventFilter(this);
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
                         for (int i = 0, i_fl = 0; i < Button_pos.size() and !i_fl; i++)
                         {
                             for (int j = 0, j_fl = 0; j < Button_pos[i].size() and !j_fl; j++)
                             {
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::RightButton)
                                {
                                    if      (
                                            mouseSceneEvent->scenePos().x() >= std::get<0>(Button_pos[i][j]) and
                                            mouseSceneEvent->scenePos().x() <= std::get<0>(Button_pos[i][j]) + sizeXPix and
                                            mouseSceneEvent->scenePos().y() >= std::get<1>(Button_pos[i][j]) and
                                            mouseSceneEvent->scenePos().y() <= std::get<1>(Button_pos[i][j]) + sizeZPix
                                            )
                                    {
                                       qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                       qDebug() << Weight_coef << Qt::endl;
                                       Select_weight window;
                                       connect(this, &Arrangement_of_elements::signalArrangeToSelectWeight, &window, &Select_weight::slot_arrange_to_select_weigth);
                                       emit signalArrangeToSelectWeight(Weight_coef[i][j], i, j, std::get<2>(Button_pos[i][j]));
                                       connect(&window, &Select_weight::signal_select_weight_to_arrange, this, &Arrangement_of_elements::slotSelectWeightToArrange);
                                       window.setModal(true);
                                       window.exec();
                                       i_fl = 1; //  флаги выхода из цикла
                                       j_fl = 1;
                                    }
                                }
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::LeftButton)
                                {
                                    if (mouseSceneEvent->scenePos().x() >= std::get<0>(Button_pos[i][j]) and
                                        mouseSceneEvent->scenePos().x() <= std::get<0>(Button_pos[i][j]) + sizeXPix and
                                        mouseSceneEvent->scenePos().y() >= std::get<1>(Button_pos[i][j]) and
                                        mouseSceneEvent->scenePos().y() <= std::get<1>(Button_pos[i][j]) + sizeZPix)
                                    {
                                        if (regime)
                                        {
                                            qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                            qDebug() << Selected_elem[channelNum - 1][i][j] << Qt::endl;
                                            if(!Selected_elem[channelNum - 1][i][j])
                                               Selected_elem[channelNum - 1][i][j] = true;
                                            else
                                               Selected_elem[channelNum - 1][i][j] = false;
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

/*
          //(1)
          mouseSceneEvent->scenePos().y() >= rad_circ_scr_pix/2*((mouseSceneEvent->scenePos().x() + sqrt(rad_circ_scr_pix))
            / sqrt(rad_circ_scr_pix) + 1) + std::get<1>(Button_pos[i][j]) and
          //(2)
          mouseSceneEvent->scenePos().y() >= -rad_circ_scr_pix/2 * mouseSceneEvent->scenePos().x() / sqrt(rad_circ_scr_pix)
             + rad_circ_scr_pix + std::get<1>(Button_pos[i][j]) and
          //(3)
          mouseSceneEvent->scenePos().x() >= sqrt(rad_circ_scr_pix) + std::get<0>(Button_pos[i][j]) and
          //(4)
          mouseSceneEvent->scenePos().y() <= -rad_circ_scr_pix/2*((mouseSceneEvent->scenePos().x() - sqrt(rad_circ_scr_pix))
             / -sqrt(rad_circ_scr_pix) - 1) + std::get<1>(Button_pos[i][j]) and
          //(5)
          mouseSceneEvent->scenePos().y() <= rad_circ_scr_pix/2 * mouseSceneEvent->scenePos().x() / -sqrt(rad_circ_scr_pix)
             - rad_circ_scr_pix + std::get<1>(Button_pos[i][j]) and
          //(6)
          mouseSceneEvent->scenePos().x() <= -sqrt(rad_circ_scr_pix) + std::get<0>(Button_pos[i][j])

*/

bool Arrangement_of_elements::hexCheck(int x, int y, int getx, int gety)
{
     return x <= sqrt(3)/2*radCircScrPix + getx and
            x >= -sqrt(3)/2*radCircScrPix + getx and
            y <= radCircScrPix/2 + gety and
            y >= -radCircScrPix/2 + gety;
/*
    return x <= sqrt(3)/2*rad_circ_scr_pix + getx and
            x >= -sqrt(3)/2*rad_circ_scr_pix + getx and
            y >= rad_circ_scr_pix/2*((x + sqrt(rad_circ_scr_pix))
                / sqrt(rad_circ_scr_pix) + 1) + gety and
            y >= -rad_circ_scr_pix/2 * x / sqrt(rad_circ_scr_pix)
               + rad_circ_scr_pix + gety and
            y <= -rad_circ_scr_pix/2*((x - sqrt(rad_circ_scr_pix))
               / -sqrt(rad_circ_scr_pix) - 1) + gety and
            y <= rad_circ_scr_pix/2 * x / -sqrt(rad_circ_scr_pix)
               - rad_circ_scr_pix + gety;
*/
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
                         for (int i = 0, i_fl = 0; i < Button_pos.size() and !i_fl; i++)
                         {
                             for (int j = 0, j_fl = 0; j < Button_pos[i].size() and !j_fl; j++)
                             {
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::RightButton)
                                {
                                    if(
                                            hexCheck(mouseSceneEvent->scenePos().x(), mouseSceneEvent->scenePos().y(),
                                                    std::get<0>(Button_pos[i][j]), std::get<1>(Button_pos[i][j]))
                                      )
                                    {
                                       qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                       qDebug() << Weight_coef << Qt::endl;
                                       Select_weight window;
                                       connect(this, &Arrangement_of_elements::signalArrangeToSelectWeight, &window, &Select_weight::slot_arrange_to_select_weigth);
                                       emit signalArrangeToSelectWeight(Weight_coef[i][j], i, j, std::get<2>(Button_pos[i][j]));
                                       connect(&window, &Select_weight::signal_select_weight_to_arrange, this, &Arrangement_of_elements::slotSelectWeightToArrange);
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
                                                         std::get<0>(Button_pos[i][j]), std::get<1>(Button_pos[i][j]))
                                       )
                                    {
                                        if (regime)
                                        {
                                            qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                            qDebug() << Selected_elem[channelNum - 1][i][j] << Qt::endl;
                                            qDebug() << "координаты выбранного элемента" <<std::get<0>(Button_pos[i][j])<<std::get<1>(Button_pos[i][j]) << Qt::endl;
                                            qDebug() << "rad_src_pix" <<radCircScrPix << Qt::endl;
                                            if(!Selected_elem[channelNum - 1][i][j])
                                               Selected_elem[channelNum - 1][i][j] = true;
                                            else
                                               Selected_elem[channelNum - 1][i][j] = false;
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

void Arrangement_of_elements::drawCirc()
{
    QPen pen;
    int width_pen = 4;
    pen.setWidth(width_pen); // Ширина круга
    scene->addEllipse(-diamPix/2 - width_pen, -diamPix/2 - width_pen,
                      diamPix + width_pen * 2, diamPix + width_pen * 2, pen);
}


void Arrangement_of_elements::drawRect (int x, int z, int size_x_pix, int size_z_pix, int j, int i)
{
    if (regime)
    {
        if (Selected_elem[channelNum - 1][j][i])
        {
            QGraphicsRectItem *received_pressed = scene->addRect(x, z, size_x_pix, size_z_pix);
            received_pressed->setPen(QPen(Qt::black));
            received_pressed->setBrush(QBrush(QColor(0, 0, 139)));
            received_pressed->show();
        }
        else
        {
            QGraphicsRectItem *received = scene->addRect(x, z, size_x_pix, size_z_pix);
            received->setPen(QPen(Qt::black));
            received->setBrush(QBrush(QColor(64, 207, 255)));
            received->show();
        }
    }
    else
    {
        QGraphicsRectItem *radiation = scene->addRect(x, z, size_x_pix, size_z_pix);
        radiation->setPen(QPen(Qt::black));
        radiation->setBrush(QBrush(QColor(244, 169, 0)));
        radiation->show();
    }


}

void Arrangement_of_elements::drawHex(int x, int y, int rad_circ_scr_pix, int j, int i)
{
    if (regime)
    {
        if (Selected_elem[channelNum - 1][j][i])
        {
            QPen pen(Qt::black);
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
            QBrush brush;
            brush.setColor(QColor(64, 207, 255));
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
    }
    else
    {
        QPen pen(Qt::black);
        QBrush brush;
        brush.setColor(QColor(244, 169, 0));
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
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = -sizeXPix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -sizeXPix / 2 - sizeXPix - distXPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        else // для четных
        {
            x = distXPix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -distXPix / 2 - sizeXPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        z -= (sizeZPix + distZPix);
    }
    z = -sizeZPix / 2;
    for (int j = numRow / 2; j < numRow ; j++)
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = -sizeXPix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -sizeXPix / 2 - sizeXPix - distXPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        else // для четных
        {
            x = distXPix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -distXPix / 2 - sizeXPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
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
            if (Curr_num_elem[j] & 1) // для нечетных
            {
                x = -sizeXPix / 2;
                for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                    Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                    x += sizeXPix + distXPix;
                }
                x = -sizeXPix / 2 - sizeXPix - distXPix;
                for (int i = 0; i < Curr_num_elem[j] / 2; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                    Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                    x -= (sizeXPix + distXPix);
                }
            }
            else // для четных
            {
                x = distXPix / 2;
                for (int i = 0; i < Curr_num_elem[j] / 2; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                    Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                    x += sizeXPix + distXPix;
                }
                x = -distXPix / 2 - sizeXPix;
                for (int i = 0; i < Curr_num_elem[j] / 2; i++)
                {
                    drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                    Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                    x -= (sizeXPix + distXPix);
                }
            }
            z -= (sizeZPix + distZPix);
        }
        z = distZPix / 2;
    for (int j = numRow / 2; j < numRow ; j++)
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = -sizeXPix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -sizeXPix / 2 - sizeXPix - distXPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        else // для четных
        {
            x = distXPix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += sizeXPix + distXPix;
            }
            x = -distXPix / 2 - sizeXPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawRect(x, z, sizeXPix, sizeZPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (sizeXPix + distXPix);
            }
        }
        z += sizeZPix + distZPix;
    }
 }
    n = 1;
    for (int j = 0; j < Button_pos.size(); j++){
        for (int i = 0; i < Button_pos[j].size(); i++)
        {
            std::get<2>(Button_pos[j][i]) = n;
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
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = 0;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += (2 * radCircScrPix * cos(M_PI/6) + distHexPix);
            }
            x = - 2*radCircScrPix * cos(M_PI/6) - distHexPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (2 * radCircScrPix * cos(M_PI/6) + distHexPix);
            }
        }
        else // для четных
        {
            x = (radCircScrPix * cos(M_PI/6) + distHexPix / 2);
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
            }
            x = -(radCircScrPix * cos(M_PI/6) + distHexPix / 2);
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
            }
        }
        z += (radCircScrPix * 3/2 + distHexPix * cos(M_PI/6));
    }
 // верхняя половина
    z = -(radCircScrPix * 3/2 + distHexPix * cos(M_PI/6));
    for (int j = numRow / 2 - 1; j >= 0; j--)
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = 0;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += 2* radCircScrPix * cos(M_PI/6) + distHexPix;
            }
            x = - 2 *radCircScrPix * cos(M_PI/6) - distHexPix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= 2* radCircScrPix * cos(M_PI/6) + distHexPix;
            }
        }
        else // для четных
        {
           x = radCircScrPix * cos(M_PI/6) + distHexPix / 2;
           for (int i = 0; i < Curr_num_elem[j] / 2; i++)
           {
               drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 + i);
               Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
               x += 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
           }
           x = -radCircScrPix * cos(M_PI/6) - distHexPix / 2;
           for (int i = 0; i < Curr_num_elem[j] / 2; i++)
           {
               drawHex(x, z, radCircScrPix, j, Curr_num_elem[j] / 2 - 1 - i);
               Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
               x -= 2 * radCircScrPix * cos(M_PI/6) + distHexPix;
           }
        }
        z -= (radCircScrPix * 3/2 + distHexPix * cos(M_PI/6));
    }
    n = 1;
    for (int j = 0; j < Button_pos.size(); j++){
        for (int i = 0; i < Button_pos[j].size(); i++)
        {
            std::get<2>(Button_pos[j][i]) = n;
            n++;
        }
    }

    qDebug() << "Button_pos" <<Qt::endl;
    for (int i = 0; i < Button_pos.size(); i++)
    {
        for (int j = 0; j < Button_pos[i].size(); j++)
        {
            qDebug() << std::get<0>(Button_pos[i][j]) << std::get<1>(Button_pos[i][j]) << " ";
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
                                                   QVector<QVector<double>> Weight_coef1, std::array<QVector<QVector<bool>>, 16> Selected_elem1,
                                                   int overlay_type1)
{
    overlayType = overlay_type1;
    sizeX = size_x1; sizeZ = size_z1; distX = dist_x1;
    distZ = dist_z1; radAnt = rad_ant1; numRow = num_row1;
    radCircScr = rad_circ_scr1; distHex = dist1;
    Selected_elem = Selected_elem1;
    Max_elem = Max_elem1;
    Weight_coef = Weight_coef1;
    Curr_num_elem = Curr_num_elem1;
    Button_pos.resize(Curr_num_elem.size());
    for (int i = 0; i < Curr_num_elem.size(); i++)
    {
        Button_pos[i].resize(Curr_num_elem[i]);
    }
    hideReshapeButtons();
}

void Arrangement_of_elements::slotSelectWeightToArrange(double weight1, int i, int j)
{
    Weight_coef[i][j] = weight1;
}


Arrangement_of_elements::~Arrangement_of_elements()
{
    delete ui;
}

void Arrangement_of_elements::on_radioButton_clicked(bool checked)
{
    if (checked){
        QWidget clear;
        regime = true;
        redrawing();
        disabledChannelButton(false);
    }
}


void Arrangement_of_elements::on_radioButton_2_clicked(bool checked)
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
    if (overlayType and (Curr_num_elem[numRow / 2 - n] != 0
                          or ((numRow - n) % 2 == 0)))
    {

        if((Curr_num_elem[numRow / 2 - n] < Max_elem[numRow / 2 - n]) and
                (Curr_num_elem[numRow / 2 + n] < Max_elem[numRow / 2 + n]))
        {
            if (n)
                Curr_num_elem[numRow / 2 - n] += 2;
            Curr_num_elem[numRow / 2 + n] += 2;
            scene->clear();
            if (n)
            {
                Button_pos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                Weight_coef[numRow / 2 + n].push_back(1);
                Button_pos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                Weight_coef[numRow / 2 + n].push_back(1);
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                {
                    Selected_elem[i][numRow / 2 + n].push_back(false);
                    Selected_elem[i][numRow / 2 + n].push_back(false);
                }
            }
            Button_pos[numRow / 2 - n].push_back(std::make_tuple(0, 0, 0));
            Weight_coef[numRow / 2 - n].push_back(1);
            Button_pos[numRow / 2 - n].push_back(std::make_tuple(0, 0, 0));
            Weight_coef[numRow / 2 - n].push_back(1);
            for (unsigned int i = 0; i < Selected_elem.size(); i++)
            {
                Selected_elem[i][numRow / 2 - n].push_back(false);
                Selected_elem[i][numRow / 2 - n].push_back(false);
            }
        }
        drawCirc();
        redrawing();

    }
    else
    {
        if (numRow & 1)
        {
            if((Curr_num_elem[numRow / 2 - n] < Max_elem[numRow / 2 - n]) and
                    (Curr_num_elem[numRow / 2 + n] < Max_elem[numRow / 2 + n]))
            {
                if (n)
                    Curr_num_elem[numRow / 2 - n] += 1;
                Curr_num_elem[numRow / 2 + n] += 1;
                scene->clear();
                if (n)
                {
                    Button_pos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                    Weight_coef[numRow / 2 + n].push_back(1);
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][numRow / 2 + n].push_back(false);
                }
                Button_pos[numRow / 2 - n].push_back(std::make_tuple(0, 0, 0));
                Weight_coef[numRow / 2 - n].push_back(1);
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                    Selected_elem[i][numRow / 2 - n].push_back(false);
            }
            drawCirc();
            redrawing();
        }
        else
            {
                if((Curr_num_elem[numRow / 2 + n] < Max_elem[numRow / 2 + n]) and
                        (Curr_num_elem[numRow / 2 - n - 1] < Max_elem[numRow / 2 - n - 1]))
                {
                    Curr_num_elem[numRow / 2 + n] += 1;
                    Curr_num_elem[numRow / 2 - n - 1] += 1;
                    scene->clear();
                    Button_pos[numRow / 2 + n].push_back(std::make_tuple(0, 0, 0));
                    Weight_coef[numRow / 2 + n].push_back(1);
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][numRow / 2 + n].push_back(false);
                    Button_pos[numRow / 2 - n - 1].push_back(std::make_tuple(0, 0, 0));
                    Weight_coef[numRow / 2 - n - 1].push_back(1);
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][numRow / 2 - n - 1].push_back(false);
                    drawCirc();
                    redrawing();
                }
            }
    }
}

void Arrangement_of_elements::reshapeMinus(int n)
{
    if (overlayType and Curr_num_elem[numRow / 2 - n] != 1 // для шестиугольных элементов
            and Curr_num_elem[numRow / 2 + n] != 1)
    {
            if((Curr_num_elem[numRow / 2 - n] > 0) and
                    (Curr_num_elem[numRow / 2 + n] > 0))
            {
                if (n)
                    Curr_num_elem[numRow / 2 - n] -= 2;
                Curr_num_elem[numRow / 2 + n] -= 2;
                scene->clear();
                if (n)
                {
                    Button_pos[numRow / 2 + n].pop_back();
                    Button_pos[numRow / 2 + n].pop_back();
                    Weight_coef[numRow / 2 + n].pop_back();
                    Weight_coef[numRow / 2 + n].pop_back();
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                    {
                        Selected_elem[i][numRow / 2 + n].pop_back();
                        Selected_elem[i][numRow / 2 + n].pop_back();
                    }
                }
                Button_pos[numRow / 2 - n].pop_back();
                Button_pos[numRow / 2 - n].pop_back();
                Weight_coef[numRow / 2 - n].pop_back();
                Weight_coef[numRow / 2 - n].pop_back();
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                {
                    Selected_elem[i][numRow / 2 - n].pop_back();
                    Selected_elem[i][numRow / 2 - n].pop_back();
                }
                drawCirc();
                redrawing();
            }
    }
    else // для чутырехугольных элементов
    {
        if (numRow & 1)
        {
            if((Curr_num_elem[numRow / 2 - n] > 0) and
                    (Curr_num_elem[numRow / 2 + n] > 0))
            {
                if (n)
                    Curr_num_elem[numRow / 2 - n] -= 1;
                Curr_num_elem[numRow / 2 + n] -= 1;
                scene->clear();
                if (n)
                {
                    Button_pos[numRow / 2 + n].pop_back();
                    Weight_coef[numRow / 2 + n].pop_back();
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][numRow / 2 + n].pop_back();
                }
                Button_pos[numRow / 2 - n].pop_back();
                Weight_coef[numRow / 2 - n].pop_back();
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                    Selected_elem[i][numRow / 2 - n].pop_back();
                drawCirc();
                redrawing();
            }
        }
        else
        {
            if((Curr_num_elem[numRow / 2 + n] > 0) and
                    (Curr_num_elem[numRow / 2 - n - 1] > 0))
            {
                Curr_num_elem[numRow / 2 + n] -= 1;
                Curr_num_elem[numRow / 2 - n - 1] -= 1;
                scene->clear();
                Button_pos[numRow / 2 + n].pop_back();
                Button_pos[numRow / 2 - n - 1].pop_back();
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                {
                    Selected_elem[i][numRow / 2 + n].pop_back();
                    Selected_elem[i][numRow / 2 - n - 1].pop_back();
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
    emit signalArrangeToMain(Curr_num_elem, Weight_coef, Button_pos,
                                sizeXPix, sizeZPix, distXPix, distXPix,
                                radCircScrPix, distHexPix);
    QWidget::close();
}

