#include "new_desk.h"
#include "ui_new_desk.h"
#include "function.h"
#include "ok.h"

New_Desk::New_Desk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_Desk)
{
    ui->setupUi(this);
}

New_Desk::~New_Desk()
{
    delete ui;
}

void New_Desk::on_AfrBtn_clicked()
{
    int cap=string_to_double(ui->CLe->text().toStdString());
    char room[32];
    strcpy(room,ui->RLe->text().toStdString().c_str());
    OrderSystem handle;
    handle.connect_to();
    if(!handle.check_link())
        ex.exec();
    handle.add_desk(cap,room) ;
    handle.close();

    OK Ok;
    Ok.exec();
    close();
}

void New_Desk::on_BackBtn_clicked()
{
    close();
}
