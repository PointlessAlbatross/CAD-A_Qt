#ifndef SELECT_WEIGHT_H
#define SELECT_WEIGHT_H

#include <QDialog>


namespace Ui {
class SelectWeight;
}

class SelectWeight : public QDialog
{
    Q_OBJECT

private:
    int i, j, n;
    double weigth;


public:
    explicit SelectWeight(QWidget *parent = nullptr);
    ~SelectWeight();

signals:
    void signalSelectWeightToArrange (double weigth, int i, int j);

public slots:
   void slotArrangeToSelectWeigth (double weigth, int i, int j, int n);
private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SelectWeight *ui;
};

#endif // SELECT_WEIGHT_H
