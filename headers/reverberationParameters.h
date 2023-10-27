#ifndef REVERBERATIONPARAMETERS_H
#define REVERBERATIONPARAMETERS_H

#include <QDialog>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>


class ReverberationParameters : public QDialog
{
    Q_OBJECT

    QCheckBox *surfCheckBox;
    QCheckBox *surroundCheckBox;
    QCheckBox *botCheckBox;
    QCheckBox *sumCheckBox;

    QDoubleSpinBox *param1Box;
    QDoubleSpinBox *param2Box;
    QDoubleSpinBox *param3Box;
    QSpinBox *channel1Box;
    QSpinBox *channel2Box;
    QSpinBox *numDotBox;

    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;



    double reverbDist1;
    double reverbDist2;
    double reverbDist3;
    double reverbFreq1;
    double reverbFreq2;
    double reverbFreq3;
    int reverbChannel1;
    int reverbChannel2;
    std::array<bool, 4> ReverbChecks;
    int REVERB_TYPE;
    int numDot;

public:
    explicit ReverberationParameters(QWidget *parent = nullptr);
    ~ReverberationParameters();

signals:
    void signal_reverberationParametersToMain1(double param1, double param2, double param3, int channel1, int numDot, std::array<bool, 4> ReverbChecks, int typeReverb, bool isCalculate);
    void signal_reverberationParametersToMain2(double param1, double param2, double param3, int channel1, int channel2, std::array<bool, 4> ReverbChecks, int typeReverb, bool isCalculate);
public slots:
    void slot_mainToReverberationParameters1(double param1, double param2, double param3, int channel1, int numDot, std::array<bool, 4> ReverbChecks, int typeReverb);
    void slot_mainToReverberationParameters2(double param1, double param2, double param3, int channel1, int channel2, std::array<bool, 4> ReverbChecks, int typeReverb);
private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonCompute_clicked();
    void on_surfCheckBox_stateChanged(int arg1);
    void on_surroundCheckBox_stateChanged(int arg1);
    void on_botCheckBox_stateChanged(int arg1);
    void on_sumCheckBox_stateChanged(int arg1);
};

#endif // REVERBERATIONPARAMETERS_H
