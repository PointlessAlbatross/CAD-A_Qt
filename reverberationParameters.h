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
    void signal_reverberationParametersToMain1();
public slots:
    void slot_mainToReverberationParameters1(double param1, double param2, double param3, int channel1, int numDot, int typeReverb);
    void slot_mainToReverberationParameters2(double param1, double param2, double param3, int channel1, int channel2, int typeReverb);
private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonCompute_clicked();
};

#endif // REVERBERATIONPARAMETERS_H
