#include "check_order_detail.h"
#include "ui_check_order_detail.h"
#include "function.h"
#include "ok.h"
#include "error.h"
#include <string>
#include <vector>

check_order_detail::check_order_detail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::check_order_detail)
{
    ui->setupUi(this);

    QStringList header;
    header<<"Dish"<<"Cooker"<<"Number"<<"Status";
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//kuan du zi shi ying
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setRowCount(0);
}

check_order_detail::~check_order_detail()
{
    delete ui;
}


void check_order_detail::Load(int _Ono){
    Ono=_Ono;
    OrderSystem handle;
    int x;
    std::string s;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    std::vector<std::vector<std::string> > v= handle.get_all_orders_di(Ono,x);
    ui->tableWidget->setRowCount(v.size());
    for(int i = 0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            if(j==1)
                s="ID: ";
            else s="";
            s+=v[i][j];
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(s.c_str()));
        }
        if(i<x)ui->tableWidget->setItem(i,3,new QTableWidgetItem("Unfinished"));
        else ui->tableWidget->setItem(i,3,new QTableWidgetItem("Finished"));
    }
    handle.close();
    ui->tableWidget->selectRow(0);
    ui->tableWidget->resizeColumnsToContents();
}

void check_order_detail::on_BackBtn_clicked()
{
    close();
}

void check_order_detail::on_pushButton_2_clicked()
{
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();

    std::string Dname=(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().toStdString());
    if(handle.complete_a_dish(Ono,Dname.c_str())==2){
        OK Ok;
        std::string s="This Order has been finished!ありがとうございます!";
        Ok.Info(s);
        Ok.exec();
        accept();
    }
    std::string s="Finished";
    ui->tableWidget->item(ui->tableWidget->currentRow(),3)->setText(QString::fromStdString(s));

    handle.close();
}
