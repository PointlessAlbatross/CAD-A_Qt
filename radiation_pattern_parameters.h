#ifndef RADIATION_PATTERN_PARAMETERS_H
#define RADIATION_PATTERN_PARAMETERS_H

#include <QDialog>

namespace Ui {
class Radiation_pattern_parameters;
}

class Radiation_pattern_parameters : public QDialog
{
    Q_OBJECT

public:
    explicit Radiation_pattern_parameters(QWidget *parent = nullptr);
    ~Radiation_pattern_parameters();

private:
    Ui::Radiation_pattern_parameters *ui;
};

#endif // RADIATION_PATTERN_PARAMETERS_H
