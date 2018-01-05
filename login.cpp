#include "login.h"
#include "ui_login.h"
#include "error.h"
#include "function.h"
#include "register.h"
#include "mw.h"
#include "manager.h"
#include <string>
#include <iostream>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QFont font  = ui->Name->font();
    font.setPointSize(32);
    ui->Name->setFont(font);
}

Login::~Login()
{
    delete ui;
}

void Login::on_LogBtn_clicked()
{
    int ID = string_to_int(ui->IDLe->text().toStdString());
    string Pwd =ui->PWdLe->text().toStdString();
    OrderSystem handle;
    wa.show();
    handle.connect_to();
    wa.close();
    if(!handle.check_link())
        ex.exec();
    if(handle.check_login(ID,Pwd.c_str())){
        if(ID==0){
            Manager M_page;
            this->hide();
            if (M_page.exec()==QDialog::Accepted)
                this->show();
        } else {
            string s = "Hello, ";
            s+=handle.get_one("Guest","Gname","Gno",ID);

            MW M_page;
            M_page.Gno=ID;
            M_page.setInfo(s);
            M_page.load_list1();
            this->hide();
            if (M_page.exec()==QDialog::Accepted)
                this->show();
        }
    } else {
        Error Ero_page;
        std::string s="Unmatch!";
        Ero_page.Info(s);
        Ero_page.exec();
    }
    handle.close();
}

void Login::on_regBtn_clicked()
{
    Register reg_page;
    reg_page.exec();
}

void Login::on_ExitBtn_clicked()
{
    exit(0);
}
