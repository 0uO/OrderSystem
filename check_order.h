#ifndef CHECK_ORDER_H
#define CHECK_ORDER_H

#include <QDialog>
#include <QTableWidgetItem>
#include "waiting.h"
#include "exit.h"


namespace Ui {
class Check_Order;
}

class Check_Order : public QDialog
{
    Q_OBJECT

public:
    explicit Check_Order(QWidget *parent = 0);
    void Load(int _Gno);
    int Gno;
    int Ono;
    Waiting wa;
    Exit ex;
    ~Check_Order();

private slots:

    void on_BackBtn_clicked();
    void on_DtlBtn_clicked();

private:
    Ui::Check_Order *ui;
};

#endif // CHECK_ORDER_H
