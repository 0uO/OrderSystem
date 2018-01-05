#ifndef COUNT_H
#define COUNT_H

#include <QDialog>
#include <string>
#include <vector>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class Count;
}

class Count : public QDialog
{
    Q_OBJECT

public:
    explicit Count(QWidget *parent = 0);
    void Load(int _Gno,int _Deskno,std::vector<std::string>_Di,std::vector<int>_Di_num);
    int Gno;
    int Deskno;
    double Total;
    std::string Dname;
    std::vector<std::string> Di;
    std::vector<int> Di_Num;
    ~Count();
    Waiting wa;
    Exit ex;


private slots:
    void on_BackBtn_clicked();

    void on_AfrBtn_clicked();

private:
    Ui::Count *ui;
};

#endif // COUNT_H
