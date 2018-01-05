#include "new_server.h"
#include "ui_new_server.h"
#include "ok.h"
#include "function.h"

New_Server::New_Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_Server)
{
    ui->setupUi(this);
}

New_Server::~New_Server()
{
    delete ui;
}

void New_Server::on_BackBtn_clicked()
{
    close();
}

void New_Server::on_AfrBtn_clicked()
{
     int age=string_to_int(ui->AgeLe->text().toStdString());
     char name[32];
     strcpy(name,ui->NameLe->text().toStdString().c_str());
     OrderSystem handle;
     handle.connect_to();
     if(!handle.check_link())
         ex.exec();
     handle.add_server(name,age);
     handle.close();

     OK Ok;
     Ok.exec();
     close();

}
