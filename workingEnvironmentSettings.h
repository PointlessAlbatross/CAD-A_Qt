#ifndef WORKINGENVIRONMENTSETTINGS_H
#define WORKINGENVIRONMENTSETTINGS_H

#include <QDialog>

namespace Ui {
class WorkingEnvironmentSettings;
}

class WorkingEnvironmentSettings : public QDialog
{
    Q_OBJECT

public:
    explicit WorkingEnvironmentSettings(QWidget *parent = nullptr);
    ~WorkingEnvironmentSettings();

private:
    Ui::WorkingEnvironmentSettings *ui;
};

#endif // WORKINGENVIRONMENTSETTINGS_H
