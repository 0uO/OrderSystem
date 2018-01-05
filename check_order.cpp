#include "check_order.h"
#include "ui_check_order.h"
#include "ok.h"
#include "error.h"
#include "function.h"
#include "check_order_detail.h"
#include <string>
#include <vector>

Check_Order::Check_Order(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Check_Order)
{
    ui->setupUi(this);

    QStringList header;
    header<<"Ono"<<"Desk"<<"Order By"<<"Time"<<"Status"<<"Total";
    ui->Orders->setHorizontalHeaderLabels(header);
    ui->Orders->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Orders->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Orders->horizontalHeader()->setStretchLastSection(true);//kuan du zi shi ying
    ui->Orders->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->Orders->setRowCount(0);

    Ono=0;
}

Check_Order::~Check_Order()
{
    delete ui;
}

void Check_Order::Load(int _Gno){
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    Gno=_Gno;
    std::vector<std::vector<std::string> > v = handle.get_all_orders(Gno);
    ui->Orders->setRowCount(v.size());
    for(int i = ui->Orders->rowCount();i > 0;i--){
        for(int j=0;j<6;j++)
            ui->Orders->setItem(i,j,new QTableWidgetItem("1"));
    }
    std::string s="ID: ";
    for(int i = 0;i<v.size();i++){
        for(int j=0;j<6;j++){
            if(j==2)v[i][j]=s+v[i][j];
            if(j==4){
                if(v[i][j]=="0")
                    v[i][j]="Unfinished";
                else v[i][j]="Finished";
            }
            ui->Orders->setItem(i,j,new QTableWidgetItem(v[i][j].c_str()));
        }
    }
    ui->Orders->selectRow(0);
    ui->Orders->resizeColumnsToContents();
    handle.close();
}

void Check_Order::on_BackBtn_clicked()
{
    close();
}

void Check_Order::on_DtlBtn_clicked()
{
    if(ui->Orders->rowCount()==0)return ;
    check_order_detail C_page;
    int Ono=string_to_int(ui->Orders->item(ui->Orders->currentRow(),0)->text().toStdString());
    C_page.Load(Ono);
    if(C_page.exec()==QDialog::Accepted){
        std::string s="Finished";
        ui->Orders->item(ui->Orders->currentRow(),4)->setText(QString::fromStdString(s));
    }
}
