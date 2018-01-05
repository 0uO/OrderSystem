#include "register.h"
#include "ui_register.h"
#include "function.h"
#include "ok.h"
#include "error.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    QFont font  = ui->Name->font();
    font.setPointSize(32);
    ui->Name->setFont(font);
}

Register::~Register()
{
    delete ui;
}

void Register::on_BackBtn_clicked()
{
    this->close();
}

void Register::on_RegBtn_clicked()
{
    string name = ui->NamLe->text().toStdString();
    int age = string_to_int(ui->AgeLe->text().toStdString());
    string Pwd=ui->PwdLe->text().toStdString();
    string Pwd_2=ui->AfrLe->text().toStdString();

    if(!(Pwd==Pwd_2)||name==""||age==0||Pwd==""){
        Error Ero_page;
        Ero_page.exec();
    } else {
        OrderSystem handle;
        wa.show();
        handle.connect_to();
        wa.close();
        if(!handle.check_link())
            ex.exec();
        int ID = handle.Guest_reg(Pwd.c_str(),name.c_str(),age);

        OK Ok_page;
        string s = "Your ID: ";
        s+=int_to_string(ID);
        Ok_page.Info(s);
        Ok_page.exec();
        close();
    }
}
