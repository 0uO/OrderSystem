#include "exit.h"
#include "ui_exit.h"

Exit::Exit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exit)
{
    ui->setupUi(this);
}

Exit::~Exit()
{
    delete ui;
}

void Exit::on_pushButton_clicked()
{
    exit(1);
}
