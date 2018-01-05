#include "manager.h"
#include "ui_manager.h"
#include "function.h"
#include "ok.h"
#include "mana_info.h"
#include "check_order.h"
#include <vector>

Manager::Manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
    QFont font  = ui->label->font();
    font.setPointSize(32);
    ui->label->setFont(font);
}

Manager::~Manager()
{
    delete ui;
}

void Manager::on_Reset_clicked()
{
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    handle.drop_tables();
    handle.create_tables();
    handle.close();

    OK Ok_page;
    Ok_page.exec();
}

void Manager::on_ExitBtn_clicked()
{
    accept();
}

void Manager::on_OBtn_clicked()
{
    Check_Order C_page;
    C_page.Load(-1);
    C_page.exec();
}

void Manager::on_CBtn_clicked()
{
    Mana_Info M_page;

    M_page.set_type(1);
    M_page.Load();
    M_page.exec();
}

void Manager::on_SBtn_clicked()
{
    Mana_Info M_page;

    M_page.set_type(2);
    M_page.Load();
    M_page.exec();
}


void Manager::on_TBtn_clicked()
{
     Mana_Info M_page;

     M_page.set_type(4);
     M_page.Load();
     M_page.exec();
}

void Manager::on_DBtn_clicked()
{
    Mana_Info M_page;

    M_page.set_type(3);
    M_page.Load();
    M_page.exec();
}
