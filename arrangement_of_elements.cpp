#include "arrangement_of_elements.h"
#include "select_weight.h"
#include "ui_arrangement_of_elements.h"



//#40cfff приемная
//f4a900ff RGBA

Arrangement_of_elements::Arrangement_of_elements(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arrangement_of_elements)
{
    diam_pix = 430; // число пикселей в диаметре
    channel_num = 1;
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    draw_circ();

    scene->installEventFilter(this);
}

void Arrangement_of_elements::rect_click(QObject *watched, QEvent *event)
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
                                            mouseSceneEvent->scenePos().x() <= std::get<0>(Button_pos[i][j]) + size_x_pix and
                                            mouseSceneEvent->scenePos().y() >= std::get<1>(Button_pos[i][j]) and
                                            mouseSceneEvent->scenePos().y() <= std::get<1>(Button_pos[i][j]) + size_z_pix
                                            )
                                    {
                                       qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                       qDebug() << Weight_coef << Qt::endl;
                                       Select_weight window;
                                       connect(this, &Arrangement_of_elements::signal_arrange_to_select_weight, &window, &Select_weight::slot_arrange_to_select_weigth);
                                       emit signal_arrange_to_select_weight(Weight_coef[i][j], i, j, std::get<2>(Button_pos[i][j]));
                                       connect(&window, &Select_weight::signal_select_weight_to_arrange, this, &Arrangement_of_elements::slot_select_weight_to_arrange);
                                       window.setModal(true);
                                       window.exec();
                                       i_fl = 1; //  флаги выхода из цикла
                                       j_fl = 1;
                                    }
                                }
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::LeftButton)
                                {
                                    if (mouseSceneEvent->scenePos().x() >= std::get<0>(Button_pos[i][j]) and
                                        mouseSceneEvent->scenePos().x() <= std::get<0>(Button_pos[i][j]) + size_x_pix and
                                        mouseSceneEvent->scenePos().y() >= std::get<1>(Button_pos[i][j]) and
                                        mouseSceneEvent->scenePos().y() <= std::get<1>(Button_pos[i][j]) + size_z_pix)
                                    {
                                        if (regime)
                                        {
                                            qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                            qDebug() << Selected_elem[channel_num - 1][i][j] << Qt::endl;
                                            if(!Selected_elem[channel_num - 1][i][j])
                                               Selected_elem[channel_num - 1][i][j] = true;
                                            else
                                               Selected_elem[channel_num - 1][i][j] = false;
                                            scene->clear();
                                            draw_circ();
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

bool Arrangement_of_elements::hex_check(int x, int y, int getx, int gety)
{
    /* return x <= sqrt(rad_circ_scr_pix) + getx and
           x >= -sqrt(rad_circ_scr_pix) + getx and
           y >= rad_circ_scr_pix/2*((x + sqrt(rad_circ_scr_pix))
                / sqrt(rad_circ_scr_pix) + 1) + gety and
           y >= -rad_circ_scr_pix/2 * x / sqrt(rad_circ_scr_pix)
               + rad_circ_scr_pix + gety and
           y <= rad_circ_scr_pix/2 * x / -sqrt(rad_circ_scr_pix)
               - rad_circ_scr_pix + gety and
           y <= rad_circ_scr_pix/2 * x / -sqrt(rad_circ_scr_pix)
               - rad_circ_scr_pix + gety;
               */
    return x <= sqrt(rad_circ_scr_pix) + getx and
            x >= -sqrt(rad_circ_scr_pix) + getx and
            y <= rad_circ_scr_pix + gety and
            y >= -rad_circ_scr_pix + gety;
}

void Arrangement_of_elements::hex_click(QObject *watched, QEvent *event)
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
                                            hex_check(mouseSceneEvent->scenePos().x(), mouseSceneEvent->scenePos().y(),
                                                    std::get<0>(Button_pos[i][j]), std::get<1>(Button_pos[i][j]))
                                      )
                                    {
                                       qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                       qDebug() << Weight_coef << Qt::endl;
                                       Select_weight window;
                                       connect(this, &Arrangement_of_elements::signal_arrange_to_select_weight, &window, &Select_weight::slot_arrange_to_select_weigth);
                                       emit signal_arrange_to_select_weight(Weight_coef[i][j], i, j, std::get<2>(Button_pos[i][j]));
                                       connect(&window, &Select_weight::signal_select_weight_to_arrange, this, &Arrangement_of_elements::slot_select_weight_to_arrange);
                                       window.setModal(true);
                                       window.exec();
                                       i_fl = 1; //  флаги выхода из цикла
                                       j_fl = 1;
                                    }
                                }
                                if (static_cast<QGraphicsSceneMouseEvent*>(event)->button() == Qt::LeftButton)
                                {
                                    if (
                                            hex_check(mouseSceneEvent->scenePos().x(), mouseSceneEvent->scenePos().y(),
                                                         std::get<0>(Button_pos[i][j]), std::get<1>(Button_pos[i][j]))
                                       )
                                    {
                                        if (regime)
                                        {
                                            qDebug()<< i + 1 << " " << j + 1 << " " << std::get<2>(Button_pos[i][j]) <<Qt::endl;
                                            qDebug() << Selected_elem[channel_num - 1][i][j] << Qt::endl;
                                            qDebug() << "координаты выбранного элемента" <<std::get<0>(Button_pos[i][j])<<std::get<1>(Button_pos[i][j]) << Qt::endl;
                                            qDebug() << "rad_src_pix" <<rad_circ_scr_pix << Qt::endl;
                                            if(!Selected_elem[channel_num - 1][i][j])
                                               Selected_elem[channel_num - 1][i][j] = true;
                                            else
                                               Selected_elem[channel_num - 1][i][j] = false;
                                            scene->clear();
                                            draw_circ();
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
    if (!overlay_type) // клик по прямоугольникам
        rect_click(watched, event);
    else if (overlay_type) // клик по шестиугольникам
        hex_click(watched, event);
    return QDialog::eventFilter(watched, event);
}


void Arrangement_of_elements::hide_reshape_buttons()
{
    if (num_row < 19)
    {
        ui->ButtonPlus_10->hide();
        ui->ButtonMinus_10->hide();
    }
    if (num_row < 17)
    {
        ui->ButtonPlus_9->hide();
        ui->ButtonMinus_9->hide();
    }
    if (num_row < 15)
    {
        ui->ButtonPlus_8->hide();
        ui->ButtonMinus_8->hide();
    }
    if (num_row < 13)
    {
        ui->ButtonPlus_7->hide();
        ui->ButtonMinus_7->hide();
    }
    if (num_row < 11)
    {
        ui->ButtonPlus_6->hide();
        ui->ButtonMinus_6->hide();
    }
    if (num_row < 9)
    {
        ui->ButtonPlus_5->hide();
        ui->ButtonMinus_5->hide();
    }
    if (num_row < 7)
    {
        ui->ButtonPlus_4->hide();
        ui->ButtonMinus_4->hide();
    }
    if (num_row < 5)
    {
        ui->ButtonPlus_3->hide();
        ui->ButtonMinus_3->hide();
    }
    if (num_row < 2)
    {
        ui->ButtonPlus_2->hide();
        ui->ButtonMinus_2->hide();
    }
    if (num_row < 1)
    {
        ui->ButtonPlus_1->hide();
        ui->ButtonMinus_1->hide();
    }
}

void Arrangement_of_elements::disabled_channel_button(bool b)
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

void Arrangement_of_elements::draw_circ()
{
    QPen pen;
    int width_pen = 4;
    pen.setWidth(width_pen); // Ширина круга
    scene->addEllipse(-diam_pix/2 - width_pen, -diam_pix/2 - width_pen,
                      diam_pix + width_pen * 2, diam_pix + width_pen * 2, pen);
}


void Arrangement_of_elements::draw_rect (int x, int z, int size_x_pix, int size_z_pix, int j, int i)
{
    if (regime)
    {
        if (Selected_elem[channel_num - 1][j][i])
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

void Arrangement_of_elements::draw_hex(int x, int y, int rad_circ_scr_pix, int j, int i)
{
    if (regime)
    {
        if (Selected_elem[channel_num - 1][j][i])
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
    if (!overlay_type) // прямоугольная антенна
        redrawing_rect();
    else if (overlay_type) // шестиугольная антенна
        redrawing_hex();
}

void Arrangement_of_elements::redrawing_rect()
{
    int x, z, n;
    size_x_pix = int (size_x / rad_ant * (diam_pix / 2));
    size_z_pix = int (size_z / rad_ant * (diam_pix / 2));
    dist_x_pix = int (dist_x / rad_ant * (diam_pix / 2));
    dist_z_pix = int (dist_z / rad_ant * (diam_pix / 2));
    if (num_row & 1) // нечетное число рядов
    {
    z = -size_z_pix * 3 / 2 - dist_z_pix;
    for (int j = num_row / 2 - 1; j >= 0; j--) //
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = -size_x_pix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += size_x_pix + dist_x_pix;
            }
            x = -size_x_pix / 2 - size_x_pix - dist_x_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (size_x_pix + dist_x_pix);
            }
        }
        else // для четных
        {
            x = dist_x_pix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += size_x_pix + dist_x_pix;
            }
            x = -dist_x_pix / 2 - size_x_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (size_x_pix + dist_x_pix);
            }
        }
        z -= (size_z_pix + dist_z_pix);
    }
    z = -size_z_pix / 2;
    for (int j = num_row / 2; j < num_row ; j++)
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = -size_x_pix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += size_x_pix + dist_x_pix;
            }
            x = -size_x_pix / 2 - size_x_pix - dist_x_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (size_x_pix + dist_x_pix);
            }
        }
        else // для четных
        {
            x = dist_x_pix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += size_x_pix + dist_x_pix;
            }
            x = -dist_x_pix / 2 - size_x_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (size_x_pix + dist_x_pix);
            }
        }
        z += size_z_pix + dist_z_pix;
    }
 }
    else // для четного количества рядов
    {
        z = -dist_z_pix / 2 - size_z_pix ;
        for (int j = num_row / 2 - 1; j >= 0; j--)
        {
            if (Curr_num_elem[j] & 1) // для нечетных
            {
                x = -size_x_pix / 2;
                for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
                {
                    draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                    Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                    x += size_x_pix + dist_x_pix;
                }
                x = -size_x_pix / 2 - size_x_pix - dist_x_pix;
                for (int i = 0; i < Curr_num_elem[j] / 2; i++)
                {
                    draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                    Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                    x -= (size_x_pix + dist_x_pix);
                }
            }
            else // для четных
            {
                x = dist_x_pix / 2;
                for (int i = 0; i < Curr_num_elem[j] / 2; i++)
                {
                    draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                    Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                    x += size_x_pix + dist_x_pix;
                }
                x = -dist_x_pix / 2 - size_x_pix;
                for (int i = 0; i < Curr_num_elem[j] / 2; i++)
                {
                    draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                    Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                    x -= (size_x_pix + dist_x_pix);
                }
            }
            z -= (size_z_pix + dist_z_pix);
        }
        z = dist_z_pix / 2;
    for (int j = num_row / 2; j < num_row ; j++)
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = -size_x_pix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += size_x_pix + dist_x_pix;
            }
            x = -size_x_pix / 2 - size_x_pix - dist_x_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (size_x_pix + dist_x_pix);
            }
        }
        else // для четных
        {
            x = dist_x_pix / 2;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += size_x_pix + dist_x_pix;
            }
            x = -dist_x_pix / 2 - size_x_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_rect(x, z, size_x_pix, size_z_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= (size_x_pix + dist_x_pix);
            }
        }
        z += size_z_pix + dist_z_pix;
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

void Arrangement_of_elements::redrawing_hex()
{
    int x, z, n;
    rad_circ_scr_pix = int (rad_circ_scr / rad_ant * (diam_pix / 2));
    dist_hex_pix = int (dist_hex / rad_ant * (diam_pix / 2));
    x = 0;

    // нижняя половина
    z = 0;
    for (int j = num_row / 2; j < num_row ; j++)
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = 0;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += (2 * rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix);
            }
            x = - 2*rad_circ_scr_pix * cos(M_PI/6) - dist_hex_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x -= (2 * rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix);
            }
        }
        else // для четных
        {
            x = (rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix / 2);
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += 2 * rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix;
            }
            x = -(rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix / 2);
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
                x -= 2 * rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix;
            }
        }
        z += (rad_circ_scr_pix * 3/2 + dist_hex_pix * cos(M_PI/6));
    }
 // верхняя половина
    z = -(rad_circ_scr_pix * 3/2 + dist_hex_pix * cos(M_PI/6));
    for (int j = num_row / 2 - 1; j >= 0; j--)
    {
        if (Curr_num_elem[j] & 1) // для нечетных
        {
            x = 0;
            for (int i = 0; i < Curr_num_elem[j] / 2 + 1; i++)
            {
                draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 + i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x += 2* rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix;
            }
            x = - 2 *rad_circ_scr_pix * cos(M_PI/6) - dist_hex_pix;
            for (int i = 0; i < Curr_num_elem[j] / 2; i++)
            {
                draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 - 1 - i);
                Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
                x -= 2* rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix;
            }
        }
        else // для четных
        {
           x = rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix / 2;
           for (int i = 0; i < Curr_num_elem[j] / 2; i++)
           {
               draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 + i);
               Button_pos[j][Curr_num_elem[j] / 2 + i] = std::make_tuple(x, z, 1);
               x += 2 * rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix;
           }
           x = -rad_circ_scr_pix * cos(M_PI/6) - dist_hex_pix / 2;
           for (int i = 0; i < Curr_num_elem[j] / 2; i++)
           {
               draw_hex(x, z, rad_circ_scr_pix, j, Curr_num_elem[j] / 2 - 1 - i);
               Button_pos[j][Curr_num_elem[j] / 2 - 1 - i] = std::make_tuple(x, z, 1);
               x -= 2 * rad_circ_scr_pix * cos(M_PI/6) + dist_hex_pix;
           }
        }
        z -= (rad_circ_scr_pix * 3/2 + dist_hex_pix * cos(M_PI/6));
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



void Arrangement_of_elements::slot_main_to_arrange(double size_x1, double size_z1, double dist_x1, double dist_z1,
                                                   double rad_circ_scr1, double dist1,
                                                   double rad_ant1, int num_row1, QVector<int> Max_elem1, QVector<int> Curr_num_elem1,
                                                   QVector<QVector<double>> Weight_coef1, std::array<QVector<QVector<bool>>, 16> Selected_elem1,
                                                   int overlay_type1)
{
    overlay_type = overlay_type1;
    size_x = size_x1; size_z = size_z1; dist_x = dist_x1;
    dist_z = dist_z1; rad_ant = rad_ant1; num_row = num_row1;
    rad_circ_scr = rad_circ_scr1; dist_hex = dist1;
    Selected_elem = Selected_elem1;
    Max_elem = Max_elem1;
    Weight_coef = Weight_coef1;
    Curr_num_elem = Curr_num_elem1;
    Button_pos.resize(Curr_num_elem.size());
    for (int i = 0; i < Curr_num_elem.size(); i++)
    {
        Button_pos[i].resize(Curr_num_elem[i]);
    }
    hide_reshape_buttons();
}

void Arrangement_of_elements::slot_select_weight_to_arrange(double weight1, int i, int j)
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
        disabled_channel_button(false);
    }
}


void Arrangement_of_elements::on_radioButton_2_clicked(bool checked)
{
    if (checked){
        QWidget clear;
        regime = false;
        redrawing();
        disabled_channel_button(true);
    }
}


void Arrangement_of_elements::on_ButtonPlus_1_clicked()
{
    reshape_plus(0);
}


void Arrangement_of_elements::on_ButtonMinus_1_clicked()
{
    reshape_minus(0);
}


void Arrangement_of_elements::on_ButtonPlus_2_clicked()
{
    reshape_plus(1);
}


void Arrangement_of_elements::on_ButtonMinus_2_clicked()
{
    reshape_minus(1);
}


void Arrangement_of_elements::on_ButtonPlus_3_clicked()
{
    reshape_plus(2);
}

void Arrangement_of_elements::on_ButtonMinus_3_clicked()
{
    reshape_minus(2);
}

void Arrangement_of_elements::on_ButtonPlus_4_clicked()
{
    reshape_plus(3);
}

void Arrangement_of_elements::on_ButtonMinus_4_clicked()
{
    reshape_minus(3);
}

void Arrangement_of_elements::on_ButtonPlus_5_clicked()
{
    reshape_plus(4);
}

void Arrangement_of_elements::on_ButtonMinus_5_clicked()
{
    reshape_minus(4);
}

void Arrangement_of_elements::on_ButtonPlus_6_clicked()
{
    reshape_plus(5);
}

void Arrangement_of_elements::on_ButtonMinus_6_clicked()
{
    reshape_minus(5);
}

void Arrangement_of_elements::on_ButtonPlus_7_clicked()
{
    reshape_plus(6);
}

void Arrangement_of_elements::on_ButtonMinus_7_clicked()
{
    reshape_minus(6);
}


void Arrangement_of_elements::reshape_plus(int n)
{
    if (overlay_type and ((Curr_num_elem[num_row / 2 - n] != 0
                          and Curr_num_elem[num_row / 2 + n] != 0)
                              or ((num_row / 2 - n) % 2 != 0)))
    {

        if((Curr_num_elem[num_row / 2 - n] < Max_elem[num_row / 2 - n]) and
                (Curr_num_elem[num_row / 2 + n] < Max_elem[num_row / 2 + n]))
        {
            if (n)
                Curr_num_elem[num_row / 2 - n] += 2;
            Curr_num_elem[num_row / 2 + n] += 2;
            scene->clear();
            if (n)
            {
                Button_pos[num_row / 2 + n].push_back(std::make_tuple(0, 0, 0));
                Weight_coef[num_row / 2 + n].push_back(1);
                Button_pos[num_row / 2 + n].push_back(std::make_tuple(0, 0, 0));
                Weight_coef[num_row / 2 + n].push_back(1);
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                {
                    Selected_elem[i][num_row / 2 + n].push_back(false);
                    Selected_elem[i][num_row / 2 + n].push_back(false);
                }
            }
            Button_pos[num_row / 2 - n].push_back(std::make_tuple(0, 0, 0));
            Weight_coef[num_row / 2 - n].push_back(1);
            Button_pos[num_row / 2 - n].push_back(std::make_tuple(0, 0, 0));
            Weight_coef[num_row / 2 - n].push_back(1);
            for (unsigned int i = 0; i < Selected_elem.size(); i++)
            {
                Selected_elem[i][num_row / 2 - n].push_back(false);
                Selected_elem[i][num_row / 2 - n].push_back(false);
            }
        }
        draw_circ();
        redrawing();

    }
    else
    {
        if (num_row & 1)
        {
            if((Curr_num_elem[num_row / 2 - n] < Max_elem[num_row / 2 - n]) and
                    (Curr_num_elem[num_row / 2 + n] < Max_elem[num_row / 2 + n]))
            {
                if (n)
                    Curr_num_elem[num_row / 2 - n] += 1;
                Curr_num_elem[num_row / 2 + n] += 1;
                scene->clear();
                if (n)
                {
                    Button_pos[num_row / 2 + n].push_back(std::make_tuple(0, 0, 0));
                    Weight_coef[num_row / 2 + n].push_back(1);
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][num_row / 2 + n].push_back(false);
                }
                Button_pos[num_row / 2 - n].push_back(std::make_tuple(0, 0, 0));
                Weight_coef[num_row / 2 - n].push_back(1);
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                    Selected_elem[i][num_row / 2 - n].push_back(false);
            }
            draw_circ();
            redrawing();
        }
        else
            {
                if((Curr_num_elem[num_row / 2 + n] < Max_elem[num_row / 2 + n]) and
                        (Curr_num_elem[num_row / 2 - n - 1] < Max_elem[num_row / 2 - n - 1]))
                {
                    Curr_num_elem[num_row / 2 + n] += 1;
                    Curr_num_elem[num_row / 2 - n - 1] += 1;
                    scene->clear();
                    Button_pos[num_row / 2 + n].push_back(std::make_tuple(0, 0, 0));
                    Weight_coef[num_row / 2 + n].push_back(1);
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][num_row / 2 + n].push_back(false);
                    Button_pos[num_row / 2 - n - 1].push_back(std::make_tuple(0, 0, 0));
                    Weight_coef[num_row / 2 - n - 1].push_back(1);
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][num_row / 2 - n - 1].push_back(false);
                    draw_circ();
                    redrawing();
                }
            }
    }
}

void Arrangement_of_elements::reshape_minus(int n)
{
    if (overlay_type and Curr_num_elem[num_row / 2 - n] != 1 // для шестиугольных элементов
            and Curr_num_elem[num_row / 2 + n] != 1)
    {
            if((Curr_num_elem[num_row / 2 - n] > 0) and
                    (Curr_num_elem[num_row / 2 + n] > 0))
            {
                if (n)
                    Curr_num_elem[num_row / 2 - n] -= 2;
                Curr_num_elem[num_row / 2 + n] -= 2;
                scene->clear();
                if (n)
                {
                    Button_pos[num_row / 2 + n].pop_back();
                    Button_pos[num_row / 2 + n].pop_back();
                    Weight_coef[num_row / 2 + n].pop_back();
                    Weight_coef[num_row / 2 + n].pop_back();
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                    {
                        Selected_elem[i][num_row / 2 + n].pop_back();
                        Selected_elem[i][num_row / 2 + n].pop_back();
                    }
                }
                Button_pos[num_row / 2 - n].pop_back();
                Button_pos[num_row / 2 - n].pop_back();
                Weight_coef[num_row / 2 - n].pop_back();
                Weight_coef[num_row / 2 - n].pop_back();
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                {
                    Selected_elem[i][num_row / 2 - n].pop_back();
                    Selected_elem[i][num_row / 2 - n].pop_back();
                }
                draw_circ();
                redrawing();
            }
    }
    else // для чутырехугольных элементов
    {
        if (num_row & 1)
        {
            if((Curr_num_elem[num_row / 2 - n] > 0) and
                    (Curr_num_elem[num_row / 2 + n] > 0))
            {
                if (n)
                    Curr_num_elem[num_row / 2 - n] -= 1;
                Curr_num_elem[num_row / 2 + n] -= 1;
                scene->clear();
                if (n)
                {
                    Button_pos[num_row / 2 + n].pop_back();
                    Weight_coef[num_row / 2 + n].pop_back();
                    for (unsigned int i = 0; i < Selected_elem.size(); i++)
                        Selected_elem[i][num_row / 2 + n].pop_back();
                }
                Button_pos[num_row / 2 - n].pop_back();
                Weight_coef[num_row / 2 - n].pop_back();
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                    Selected_elem[i][num_row / 2 - n].pop_back();
                draw_circ();
                redrawing();
            }
        }
        else
        {
            if((Curr_num_elem[num_row / 2 + n] > 0) and
                    (Curr_num_elem[num_row / 2 - n - 1] > 0))
            {
                Curr_num_elem[num_row / 2 + n] -= 1;
                Curr_num_elem[num_row / 2 - n - 1] -= 1;
                scene->clear();
                Button_pos[num_row / 2 + n].pop_back();
                Button_pos[num_row / 2 - n - 1].pop_back();
                for (unsigned int i = 0; i < Selected_elem.size(); i++)
                {
                    Selected_elem[i][num_row / 2 + n].pop_back();
                    Selected_elem[i][num_row / 2 - n - 1].pop_back();
                }
                draw_circ();
                redrawing();
            }
        }
    }
}


void Arrangement_of_elements::on_ChannelNumButton_1_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_1->setDisabled(true);
    channel_num = 1;
    redrawing();

}

void Arrangement_of_elements::on_ChannelNumButton_2_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_2->setDisabled(true);
    channel_num = 2;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_3_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_3->setDisabled(true);
    channel_num = 3;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_4_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_4->setDisabled(true);
    channel_num = 4;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_5_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_5->setDisabled(true);
    channel_num = 5;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_6_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_6->setDisabled(true);
    channel_num = 6;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_7_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_7->setDisabled(true);
    channel_num = 7;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_8_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_8->setDisabled(true);
    channel_num = 8;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_9_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_9->setDisabled(true);
    channel_num = 9;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_10_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_10->setDisabled(true);
    channel_num = 10;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_11_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_11->setDisabled(true);
    channel_num = 11;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_12_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_12->setDisabled(true);
    channel_num = 12;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_13_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_13->setDisabled(true);
    channel_num = 13;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_14_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_14->setDisabled(true);
    channel_num = 14;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_15_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_15->setDisabled(true);
    channel_num = 15;
    redrawing();
}

void Arrangement_of_elements::on_ChannelNumButton_16_clicked()
{
    disabled_channel_button(false);
    ui->ChannelNumButton_16->setDisabled(true);
    channel_num = 16;
    redrawing();
}


void Arrangement_of_elements::on_saveButton_clicked()
{
    emit signal_arrange_to_main(Curr_num_elem, Weight_coef, Button_pos,
                                size_x_pix, size_z_pix, dist_x_pix, dist_x_pix);
    QWidget::close();
}

