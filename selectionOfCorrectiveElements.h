#ifndef SELECTION_OF_CORRECTIVE_ELEMENTS_H
#define SELECTION_OF_CORRECTIVE_ELEMENTS_H

#include <QDialog>

namespace Ui {
class selectionOfCorrectiveElements;
}

class selectionOfCorrectiveElements : public QDialog
{
    Q_OBJECT

public:
    explicit selectionOfCorrectiveElements(QWidget *parent = nullptr);
    ~selectionOfCorrectiveElements();

private:
    Ui::selectionOfCorrectiveElements *ui;
};

#endif // SELECTION_OF_CORRECTIVE_ELEMENTS_H
