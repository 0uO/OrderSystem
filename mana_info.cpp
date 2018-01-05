#include "mana_info.h"
#include "ui_mana_info.h"
#include "new_cooker.h"
#include "new_dish.h"
#include "new_server.h"
#include "new_desk.h"
#include "check_order.h"
#include "function.h"
#include "ok.h"
#include "error.h"
#include <string>
#include <vector>

Mana_Info::Mana_Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Mana_Info)
{
    ui->setupUi(this);
    ui->InfoList->setViewMode(QListView::ListMode);
    item_now="";
}

Mana_Info::~Mana_Info()
{
    delete ui;
}

void Mana_Info::set_type(int i){
    type=i;
}

void Mana_Info::add_list(std::string s){
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(s.c_str());                     //设置列表项的文本
    this->ui->InfoList->addItem(item);
}

void Mana_Info::on_ExitBtn_clicked()
{
    accept();
}

void Mana_Info::Load(){
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    std::vector<std::string> s;
    ui->InfoList->clear();
    if(type==1)
        s= handle.get_all_group();
    else if(type==2)
        s = handle.get_all_waiters();
    else if(type==3)
        s = handle.get_all_type();
    else if(type==4)
        s = handle.get_all_room();
    for(int i=0;i<s.size();i++){
        add_list(s[i]);
    }
}

std::vector<std::vector<std::string> > Mana_Info::get_info(){
    std::vector<std::vector<std::string> > v;
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    if(type==1){
        v=handle.get_part_cookers(item_now);
    } else if(type==2){
        v=handle.get_part_servers(item_now);
    } else if(type==3){
        v=handle.get_part_dishes2(item_now);
    } else if(type==4){
        v=handle.get_part_desks(item_now);
    }
    handle.close();
    return v;
}

void Mana_Info::Load_info(){
    QStringList header;
    ui->InfoTab->clear();
    if(type==1){//Cooker
        ui->InfoTab->setColumnCount(4);
        header<<"No."<<"Name"<<"Age"<<"Group";
        ui->InfoTab->setHorizontalHeaderLabels(header);
        ui->InfoTab->horizontalHeader()->setStretchLastSection(true);
        ui->InfoTab->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->InfoTab->setRowCount(0);
    } else if (type==2){//Server
        ui->InfoTab->setColumnCount(3);
        header<<"No."<<"Name"<<"Age";
        ui->InfoTab->setHorizontalHeaderLabels(header);
        ui->InfoTab->horizontalHeader()->setStretchLastSection(true);
        ui->InfoTab->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->InfoTab->setRowCount(0);
    } else if (type==3){//Dish
        ui->InfoTab->setColumnCount(4);
        header<<"No."<<"Name"<<"Type"<<"Price";
        ui->InfoTab->setHorizontalHeaderLabels(header);
        ui->InfoTab->horizontalHeader()->setStretchLastSection(true);
        ui->InfoTab->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->InfoTab->setRowCount(0);
    } else if (type==4){//Desk
        ui->InfoTab->setColumnCount(3);
        header<<"No."<<"Room"<<"Capacity";
        ui->InfoTab->setHorizontalHeaderLabels(header);
        ui->InfoTab->horizontalHeader()->setStretchLastSection(true);
        ui->InfoTab->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->InfoTab->setRowCount(0);
    }
    if(item_now=="")return;
    std::vector<std::vector<std::string> > v= get_info();
    ui->InfoTab->setRowCount(v.size());
    for(int i = 0;i<v.size();i++){
        for(int j=0;j<v[i].size();j++){
            ui->InfoTab->setItem(i,j,new QTableWidgetItem(v[i][j].c_str()));
            QTableWidgetItem *item = ui->InfoTab->item(i, 0);
            if(item) {
                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
            } else {
                item = new QTableWidgetItem;
                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                ui->InfoTab->setItem(i, 0, item);
            }
        }
    }
    ui->InfoTab->selectRow(0);
}

void Mana_Info::on_pushButton_clicked()
{
    if(type==1){
        New_Cooker N_page;
        N_page.exec();
    } else if(type==2) {
        New_Server N_page;
        N_page.exec();
    } else if(type==3) {
        New_Dish N_page;
        N_page.exec();
    } else if(type==4){///not add new
        New_Desk N_page;
        N_page.exec();
    }
    this->ui->InfoList->clear();
    Load();
    //ui->InfoList->setCurrentRow(0);
    //item_now=ui->InfoList->currentItem()->text().toStdString();
    Load_info();
}

void Mana_Info::on_InfoList_itemClicked(QListWidgetItem *item)
{
    item_now=ui->InfoList->currentItem()->text().toStdString();
    Load_info();
}

void Mana_Info::on_DelBtn_clicked()
{
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    if(item_now=="") return;
    if(!(ui->InfoTab->isItemSelected(ui->InfoTab->currentItem()))) return ;
    int s=string_to_int(ui->InfoTab->item(ui->InfoTab->currentRow(),0)->text().toStdString());
    if(s<1) return;
    handle.delete_one(type,s);
    Load();
    Load_info();
    handle.close();
}

void Mana_Info::on_SubBtn_clicked()
{
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    int r=ui->InfoTab->rowCount();
    int c=ui->InfoTab->columnCount();
    //cout<<"r: "<<r<<endl<<"c: "<<c<<endl;
    std::vector<std::string> s;
    std::string ss;

    bool f=1;

    for(int i=0;i<r;i++){
        s.clear();
        for(int j=0;j<c;j++){
            ss=ui->InfoTab->item(i,j)->text().toStdString();
            s.push_back(ss);
        }
        if(!handle.update_one(s,type)){
            Error Ero;
            ss="The Dish already exists or No Cooker could cook it!";
            Ero.Info(ss);
            Ero.exec();
            f=0;
        };
    }

    handle.close();
    if(f){
        OK Ok;
        Ok.exec();
    }
    Load();
    Load_info();
}
