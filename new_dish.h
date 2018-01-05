#ifndef NEW_DISH_H
#define NEW_DISH_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class New_Dish;
}

class New_Dish : public QDialog
{
    Q_OBJECT

public:
    explicit New_Dish(QWidget *parent = 0);
    ~New_Dish();
    Waiting wa;
    Exit ex;


private slots:
    void on_AfrBtn_clicked();

    void on_BackBtn_clicked();

private:
    Ui::New_Dish *ui;
};

#endif // NEW_DISH_H
