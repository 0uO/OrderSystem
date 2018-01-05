#include "new_cooker.h"
#include "ui_new_cooker.h"
#include "function.h"
#include "ok.h"

New_Cooker::New_Cooker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_Cooker)
{
    ui->setupUi(this);
}

New_Cooker::~New_Cooker()
{
    delete ui;
}

void New_Cooker::on_BackBtn_clicked()
{
    close();
}

void New_Cooker::on_AfrBtn_clicked()
{
    int age=string_to_int(ui->AgeLe->text().toStdString());
    char name[32];
    strcpy(name,ui->NameLe->text().toStdString().c_str());
    char group[16];
    strcpy(group,ui->GroupLe->text().toStdString().c_str());
    OrderSystem handle;
    handle.connect_to();
    if(!handle.check_link())
        ex.exec();
    handle.add_cooker(name,age,group);
    handle.close();

    OK Ok;
    Ok.exec();
    close();
}
