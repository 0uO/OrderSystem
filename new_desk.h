#ifndef NEW_DESK_H
#define NEW_DESK_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class New_Desk;
}

class New_Desk : public QDialog
{
    Q_OBJECT

public:
    explicit New_Desk(QWidget *parent = 0);
    ~New_Desk();
    Waiting wa;
    Exit ex;


private slots:
    void on_AfrBtn_clicked();
    void on_BackBtn_clicked();

private:
    Ui::New_Desk *ui;
};

#endif // NEW_DESK_H
