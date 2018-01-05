#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    Waiting wa;
    Exit ex;


private slots:

    void on_LogBtn_clicked();

    void on_regBtn_clicked();

    void on_ExitBtn_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
