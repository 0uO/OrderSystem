#include "ok.h"
#include "ui_ok.h"
#include <string>

OK::OK(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OK)
{
    ui->setupUi(this);
}

OK::~OK()
{
    delete ui;
}

void OK::on_AfrBtn_clicked()
{
    this->close();
}

void OK::Info(std::string s){
    ui->InfoLb->setText(QString::fromStdString(s));
}
