#ifndef ARRANGEMENT_OF_ELEMENTS_H
#define ARRANGEMENT_OF_ELEMENTS_H

#include <QDialog>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QScrollBar>

namespace Ui {
class ArrangementOfElements;
}
class ArrangementOfElements : public QDialog
{
    Q_OBJECT

public:
    explicit ArrangementOfElements(QWidget *parent = nullptr);
    ~ArrangementOfElements();

private:
    Ui::ArrangementOfElements *ui;
    QGraphicsScene *scene;

    double scaleKoef = 20.0; // масштаб уменьшения

    int antennaType;
    int overlayType;
    bool regime;
    int textType;

    int diamPix;
    int cnt;
    double sizeX;
    double sizeZ;
    double distX;
    double distZ;
    double radAnt;

    double radCircScr;
    double distHex;

    int sizeXPix;
    int sizeZPix;
    int distXPix;
    int distZPix;

    int radCircScrPix;
    int distHexPix;

    int numRow;
    int groupNum;

    std::array<double,16> Arr_ZclNum;
    std::array<double,16> Arr_YclNum;
    std::array<double,16> Arr_Denum;

    QVector<int> MaxElem;
    QVector<int> CurrNumElem;
    std::array<QVector<QVector<double>>, 17> WeightCoef;
    QVector <QVector<std::tuple<int, int, int>>> ButtonPos; // x,y,n
    std::array<QVector<QVector<bool>>, 16> SelectedElem;
    QVector<QVector<QPair<double,double>>> CenterPos;
    std::array<QPair<double, double>, 16> Centroids;

    int selectedChanelNum;

    void redrawing();
    void redrawingRect();
    void redrawingHex();
    void drawCirc();
    void drawRect (int x, int z, int size_x_pix, int size_z_pix, int j1, int i1);
    void setText (int cx, int cz, int j1, int i1, QColor color);
    void drawHex (int x, int z, int rad_circ_scr_pix, int j1, int i1);
    int i1, j1, n1;
    double weight;


    void reshapePlus(int n);
    void reshapeMinus(int n);
    void hideReshapeButtons();
    void disabledGroupButton(bool b);
    bool eventFilter(QObject *watched, QEvent *event);
    void rectClick(QObject *watched, QEvent *event);
    bool rectCheck(int x, int y, int getx, int gety);
    void hexClick(QObject *watched, QEvent *event);
    bool hexCheck(int x, int y, int getx, int gety);   
    void wheelEvent(QWheelEvent* event);
signals:
    void signalArrangeToSelectWeight (double, int, int, int);
    void signalArrangeToMain(QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17> Weight_coef, QVector<QVector<QPair<double,double>>> Center_pos,
                             std::array<QPair<double, double>, 16> Centroids, std::array<double,16> Arr_Denum, std::array<QVector<QVector<bool>>, 16> Selected_elem,
                             int numElem);


public slots:
    void slotMainToArrange(double size_x, double size_z, double dist_x, double dist_z,
                              double rad_circ_scr, double dist_hex,
                              double rad_ant, int num_row, QVector<int> Max_elem, QVector<int> Curr_num_elem, std::array<QVector<QVector<double>>, 17> Weight_coef,
                              std::array<QVector<QVector<bool>>, 16> Selected_elem,
                              int antenna_type, int overlay_type);
    void slotSelectWeightToArrange(double weight, int i1, int j1);

private slots:
    void on_radioButtonReceive_clicked(bool checked);
    void on_radioButtonRadiation_clicked(bool checked);
    void on_ButtonPlus_1_clicked();
    void on_ButtonMinus_1_clicked();
    void on_ButtonPlus_2_clicked();
    void on_ButtonMinus_2_clicked();
    void on_ButtonPlus_3_clicked();
    void on_ButtonMinus_3_clicked();
    void on_ButtonPlus_4_clicked();
    void on_ButtonMinus_4_clicked();
    void on_ButtonPlus_5_clicked();
    void on_ButtonMinus_5_clicked();
    void on_ButtonPlus_6_clicked();
    void on_ButtonMinus_6_clicked();
    void on_ButtonPlus_7_clicked();
    void on_ButtonMinus_7_clicked();


    void on_groupNumButton_1_clicked();
    void on_groupNumButton_2_clicked();
    void on_groupNumButton_3_clicked();
    void on_groupNumButton_4_clicked();
    void on_groupNumButton_5_clicked();
    void on_groupNumButton_6_clicked();
    void on_groupNumButton_7_clicked();
    void on_groupNumButton_8_clicked();
    void on_groupNumButton_9_clicked();
    void on_groupNumButton_10_clicked();
    void on_groupNumButton_11_clicked();
    void on_groupNumButton_12_clicked();
    void on_groupNumButton_13_clicked();
    void on_groupNumButton_14_clicked();
    void on_groupNumButton_15_clicked();
    void on_groupNumButton_16_clicked();
    void on_saveButton_clicked();
    void on_clcButton_clicked();
    void on_colRowButton_clicked();
    void on_numButton_clicked();
    void on_weightButton_clicked();
};

#endif // ARRANGEMENT_OF_ELEMENTS_H
