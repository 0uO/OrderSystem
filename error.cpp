#include "error.h"
#include "ui_error.h"

Error::Error(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Error)
{
    ui->setupUi(this);
}

Error::~Error()
{
    delete ui;
}

void Error::on_AfrBtn_clicked()
{
    this->close();
}
void Error::Info(std::string s){
    ui->InfoLb->setText(QString::fromStdString(s));
}
