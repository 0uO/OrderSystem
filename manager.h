#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class Manager;
}

class Manager : public QDialog
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    ~Manager();
    Waiting wa;
    Exit ex;


private slots:
    void on_Reset_clicked();

    void on_ExitBtn_clicked();

    void on_CBtn_clicked();

    void on_OBtn_clicked();

    void on_SBtn_clicked();

    void on_TBtn_clicked();

    void on_DBtn_clicked();

private:
    Ui::Manager *ui;
};

#endif // MANAGER_H
