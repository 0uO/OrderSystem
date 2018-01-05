#ifndef NEW_SERVER_H
#define NEW_SERVER_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class New_Server;
}

class New_Server : public QDialog
{
    Q_OBJECT

public:
    explicit New_Server(QWidget *parent = 0);
    ~New_Server();
    Waiting wa;
    Exit ex;


private slots:
    void on_BackBtn_clicked();

    void on_AfrBtn_clicked();

private:
    Ui::New_Server *ui;
};

#endif // NEW_SERVER_H
