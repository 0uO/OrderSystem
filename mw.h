#ifndef MW_H
#define MW_H

#include <QDialog>
#include <QListWidgetItem>
#include <QTableWidgetItem>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class MW;
}

class MW : public QDialog
{
    Q_OBJECT

public:
    explicit MW(QWidget *parent = 0);
    void setInfo(std::string s);
    void add_list1(std::string s);
    void add_list2(std::string s);
    void load_list1();
    void load_list2(std::string s);
    void update_cart();
    int Gno;
    int Deskno;
    double Dprice;
    std::string Dname;
    std::vector<std::string> Di;
    std::vector<int> Di_Num;
    ~MW();
    Waiting wa;
    Exit ex;


private slots:
    void on_CmtBtn_clicked();

    void on_InfoBtn_clicked();

    void on_AfrBtn_clicked();

    void on_SortList_itemClicked(QListWidgetItem *item);

    void on_SortList2_itemClicked(QTableWidgetItem *item);

    void on_pushButton_clicked();


private:
    Ui::MW *ui;
};

#endif // MW_H
