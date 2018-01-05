#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    Waiting wa;
    Exit ex;


private slots:
    void on_BackBtn_clicked();

    void on_RegBtn_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
