#ifndef SELECT_WEIGHT_H
#define SELECT_WEIGHT_H

#include <QDialog>


namespace Ui {
class Select_weight;
}

class Select_weight : public QDialog
{
    Q_OBJECT

private:
    int i, j, n;
    double weigth;


public:
    explicit Select_weight(QWidget *parent = nullptr);
    ~Select_weight();

signals:
    void signalSelectWeightToArrange (double weigth, int i, int j);

public slots:
   void slotArrangeToSelectWeigth (double weigth, int i, int j, int n);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Select_weight *ui;
};

#endif // SELECT_WEIGHT_H
