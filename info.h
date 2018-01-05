#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = 0);
    void Load(int _Gno);
    int Gno;
    ~Info();
    Waiting wa;
    Exit ex;


private slots:
    void on_BackBtn_clicked();

    void on_LogBtn_clicked();

    void on_HisBtn_clicked();

    void on_ModBtn_clicked();

private:
    Ui::Info *ui;
};

#endif // INFO_H
