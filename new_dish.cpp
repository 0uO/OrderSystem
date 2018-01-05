#include "new_dish.h"
#include "ui_new_dish.h"
#include "function.h"
#include "ok.h"
#include "error.h"

New_Dish::New_Dish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_Dish)
{
    ui->setupUi(this);
}

New_Dish::~New_Dish()
{
    delete ui;
}

void New_Dish::on_AfrBtn_clicked()
{
    double Price=string_to_double(ui->PLe->text().toStdString());
    char name[32];
    strcpy(name,ui->NameLe->text().toStdString().c_str());
    char group[16];
    strcpy(group,ui->TLe->text().toStdString().c_str());
    OrderSystem handle;
    handle.connect_to();
    if(!handle.check_link())
        ex.exec();
    if(!handle.add_dish(name, Price,group)){
        Error Ero;
        string s="The Dish already exists or No Cooker could cook it!";
        Ero.Info(s);
        Ero.exec();
        return ;
    }
    handle.close();

    OK Ok;
    Ok.exec();
    close();
}

void New_Dish::on_BackBtn_clicked()
{
    close();
}
