#include "info.h"
#include "ui_info.h"
#include "function.h"
#include "ok.h"
#include "check_order.h"
#include "error.h"
#include <string>

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;
}

void Info::Load(int _Gno){
    Gno=_Gno;
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    std::string s = handle.get_one("Guest","Gage","Gno",Gno);
    this->ui->AgeLe->setText(QString::fromStdString(s));
    s = handle.get_one("Guest","Gname","Gno",Gno);
    this->ui->NameLe->setText(QString::fromStdString(s));
    s = int_to_string(Gno);
    this->ui->IDLe->setText(QString::fromStdString(s));

    handle.close();
}

void Info::on_BackBtn_clicked()
{
    this->close();
}

void Info::on_LogBtn_clicked()
{
    accept();
    this->close();
}

void Info::on_HisBtn_clicked()
{
    Check_Order C_page;
    C_page.Load(Gno);
    C_page.exec();
}

void Info::on_ModBtn_clicked()
{
    OrderSystem handle;
    char pwd[32];
    std::string s=ui->PwdLe->text().toStdString();
    if(s==""){
        Error e;
        std::string ss="Please enter your password!";
        e.Info(ss);
        e.exec();
        return;
    }
    strcpy(pwd,s.c_str());
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    handle.Guest_modi(Gno,pwd);
    handle.close();

    OK Ok;
    Ok.exec();
}
