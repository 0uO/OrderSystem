#ifndef CHECK_ORDER_DETAIL_H
#define CHECK_ORDER_DETAIL_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class check_order_detail;
}

class check_order_detail : public QDialog
{
    Q_OBJECT

public:
    explicit check_order_detail(QWidget *parent = 0);
    void Load(int _Ono);
    int Ono;
    ~check_order_detail();

    Waiting wa;
    Exit ex;

private slots:
    void on_BackBtn_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::check_order_detail *ui;
};

#endif // CHECK_ORDER_DETAIL_H
