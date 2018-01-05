#include "count.h"
#include "ui_count.h"
#include "function.h"
#include "ok.h"
#include <vector>
#include <string>

Count::Count(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Count)
{
    ui->setupUi(this);
    QStringList header;
    header.clear();
    header<<"Item"<<"Num";
    ui->OrderList ->setHorizontalHeaderLabels(header);
    ui->OrderList ->horizontalHeader()->setStretchLastSection(true);
    ui->OrderList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->OrderList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Count::~Count()
{
    delete ui;
}

void Count::on_BackBtn_clicked()
{
    this->close();
}
void Count::Load(int _Gno,int _Deskno,std::vector<std::string>_Di,std::vector<int>_Di_num){
    Gno=_Gno;
    Deskno=_Deskno;
    Di.assign(_Di.begin(), _Di.end());
    Di_Num.assign(_Di_num.begin(), _Di_num.end());
    int r=0;
    for(int i=0;i<Di.size();i++){
        if(Di_Num[i]==0) r++;
        ui->OrderList ->setItem(i-r,0,new QTableWidgetItem(Di[i].c_str()));
        ui->OrderList ->setItem(i-r,1,new QTableWidgetItem(int_to_string(Di_Num[i]).c_str()));
    }
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    std::vector<std::string> room = handle.get_all_room();
    for(int i=0;i<room.size();i++){
        ui->DCB->addItem(QString::fromStdString(room[i]));
    }

    ui->TotalLe->setText(QString::fromStdString(double_to_string(handle.count_order(Di,Di_Num))));
    handle.close();
}

void Count::on_AfrBtn_clicked()
{
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    Deskno=handle.get_a_desk(ui->DCB->currentText().toStdString());
    handle.put_orders(Deskno,Di,Di_Num,Gno);
    handle.close();

    OK Ok;
    string s="Enjoy.";
    Ok.Info(s);
    Ok.exec();
    close();
}
