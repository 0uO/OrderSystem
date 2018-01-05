#ifndef NEW_COOKER_H
#define NEW_COOKER_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class New_Cooker;
}

class New_Cooker : public QDialog
{
    Q_OBJECT

public:
    explicit New_Cooker(QWidget *parent = 0);
    ~New_Cooker();
    Waiting wa;
    Exit ex;


private slots:
    void on_BackBtn_clicked();

    void on_AfrBtn_clicked();

private:
    Ui::New_Cooker *ui;
};

#endif // NEW_COOKER_H
