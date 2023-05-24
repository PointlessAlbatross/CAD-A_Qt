#ifndef ECHOSIGNAL_H
#define ECHOSIGNAL_H

#include <QDialog>

namespace Ui {
class EchoSignal;
}

class EchoSignal : public QDialog
{
    Q_OBJECT

public:
    explicit EchoSignal(QWidget *parent = nullptr);
    ~EchoSignal();

private:
    Ui::EchoSignal *ui;
};

#endif // ECHOSIGNAL_H
