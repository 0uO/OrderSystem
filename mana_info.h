#ifndef MANA_INFO_H
#define MANA_INFO_H

#include <QDialog>
#include <string>
#include <vector>
#include <QListWidgetItem>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class Mana_Info;
}

class Mana_Info : public QDialog
{
    Q_OBJECT

public:
    explicit Mana_Info(QWidget *parent = 0);
    void add_list(std::string s);
    void Load();
    void Load_info();
    void set_type(int i);
    std::vector<std::vector<std::string> > get_info();
    std::string item_now;
    ~Mana_Info();
    Waiting wa;
    Exit ex;


private slots:
    void on_ExitBtn_clicked();

    void on_pushButton_clicked();

    void on_InfoList_itemClicked(QListWidgetItem *item);

    void on_DelBtn_clicked();

    void on_SubBtn_clicked();

private:
    Ui::Mana_Info *ui;
    int type;//1:Cooker 2:Server 3:Dish
};

#endif // MANA_INFO_H
