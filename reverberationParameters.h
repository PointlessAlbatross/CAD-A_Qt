#ifndef REVERBERATIONPARAMETERS_H
#define REVERBERATIONPARAMETERS_H

#include <QDialog>

namespace Ui {
class ReverberationParameters;
}

class ReverberationParameters : public QDialog
{
    Q_OBJECT

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

private:
    Ui::ReverberationParameters *ui;
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
