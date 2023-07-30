#ifndef SELECTION_OF_CORRECTIVE_ELEMENTS_H
#define SELECTION_OF_CORRECTIVE_ELEMENTS_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>



class SelectionOfCorrectiveElements : public QDialog
{
    Q_OBJECT

    QDoubleSpinBox *qBox;
    QDoubleSpinBox *q1Box;
    QDoubleSpinBox *freqBox;
    QDoubleSpinBox *deltaFreqBox;
    QDoubleSpinBox *capacityC0Box;
    QDoubleSpinBox *capacityCBox;
    QDoubleSpinBox *resistanceRBox;
    QDoubleSpinBox *inductanceLBox;


    double q;
    double q1;
    double freq;       // f
    double deltaFreq;  // delta_f
    double capacity_0; // C0
    double capacity;   // C
    double resistance; // R
    double inductance; // L

public:
    explicit SelectionOfCorrectiveElements(QWidget *parent = nullptr);
    ~SelectionOfCorrectiveElements();

private slots:


    void on_cancelButton_clicked();

    void on_saveButton_clicked();

    void on_calculateButton_clicked();

signals:
    void signal_selectionOfCorrectiveElementsToMain_save (double q, double q1, double f, double delta_f,
                                                        double C0, double C, double R, double L);
    void signal_selectionOfCorrectiveElementsToMain_calculate (double q, double q1, double f, double delta_f,
                                                        double C0, double C, double R, double L);

public slots:
    void slot_mainToSelectionOfCorrectiveElements (double qSlot, double q1Slot, double f, double delta_f,
                                                        double C0, double C, double R, double L);
};

#endif // SELECTION_OF_CORRECTIVE_ELEMENTS_H
