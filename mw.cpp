#include "mw.h"
#include "ui_mw.h"
#include "info.h"
#include "comment.h"
#include "count.h"
#include "function.h"
#include "ok.h"
#include "error.h"
#include <string>

MW::MW(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MW)
{
    ui->setupUi(this);
    QFont font  = ui->HelloLb->font();
    font.setPointSize(32);
    ui->HelloLb->setFont(font);
    ui->SortList->setViewMode(QListView::ListMode);

    QStringList header;
    header<<"Name"<<"Price";
    ui->SortList2->setHorizontalHeaderLabels(header);
    ui->SortList2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SortList2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->SortList2->horizontalHeader()->setStretchLastSection(true);//kuan du zi shi ying
    ui->SortList2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->SortList2->setRowCount(0);

    header.clear();
    header<<"Item"<<"Num";
    ui->InfoTab->setHorizontalHeaderLabels(header);
    ui->InfoTab->horizontalHeader()->setStretchLastSection(true);
    ui->InfoTab->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->InfoTab->setRowCount(0);

    Dname="";
    Deskno=1;
}

MW::~MW()
{
    delete ui;
}

void MW::setInfo(std::string s){
    this->ui->HelloLb->setText(QString::fromStdString(s));
}

void MW::add_list1(std::string s){
    QListWidgetItem *item = new QListWidgetItem;
    item->setText(s.c_str());                     //设置列表项的文本
    this->ui->SortList->addItem(item);
}

void MW::load_list1(){
    OrderSystem handle;
    handle.connect_to();
    if(!handle.check_link())
        ex.exec();
    std::vector<std::string> s=handle.get_all_type();
    for(int i=0;i<s.size();i++){
        add_list1(s[i]);
    }
    handle.close();
}
void MW::load_list2(string s){
    OrderSystem handle;
    handle.connect_to();
    if(!handle.check_link())
        ex.exec();
    std::vector<std::vector<std::string> > ss=handle.get_part_dishes(s);
    ui->SortList2->setRowCount(ss.size());
    for(int i = ui->SortList2->rowCount();i > 0;i--){
        ui->SortList2->setItem(i,0,new QTableWidgetItem(" "));
        ui->SortList2->setItem(i,1,new QTableWidgetItem(" "));
    }
    for(int i=0;i<ss.size();i++){
        ui->SortList2->setItem(i,0,new QTableWidgetItem(ss[i][0].c_str()));
        ui->SortList2->setItem(i,1,new QTableWidgetItem(ss[i][1].c_str()));
    }
    handle.close();
}

void MW::update_cart(){
    ui->InfoTab->setRowCount(Di.size());
    for(int i = ui->InfoTab->rowCount();i > 0;i--){
        ui->InfoTab->setItem(i,0,new QTableWidgetItem(" "));
        ui->InfoTab->setItem(i,1,new QTableWidgetItem(" "));
    }
    for(int i=0;i<Di.size();i++){
        ui->InfoTab->setItem(i,0,new QTableWidgetItem(Di[i].c_str()));
        ui->InfoTab->setItem(i,1,new QTableWidgetItem(int_to_string(Di_Num[i]).c_str()));
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

void MW::on_CmtBtn_clicked()
{
    if(Dname=="")return ;
    Comment C_page;
    C_page.Load(Gno,Dname);
    C_page.exec();
}

void MW::on_InfoBtn_clicked()
{
    Info Info_page;
    Info_page.Load(Gno);
    if(Info_page.exec()==QDialog::Accepted)
        accept();
}

void MW::on_AfrBtn_clicked()
{
    if(Di.size()==0) return ;
    int sum=0;
    for(int i=0;i<Di.size();i++){
        Di_Num[i]=string_to_int(ui->InfoTab->item(i,1)->text().toStdString());
        if(Di_Num[i]<0){
            Error Ero;
            std::string s="What do you want to do???";
            Ero.Info(s);
            Ero.exec();
            return ;
        }
        sum+=Di_Num[i];
    }
    if (sum==0) return;
    Count C_page;
    C_page.Load(Gno,Deskno,Di,Di_Num);
    C_page.exec();
}

void MW::on_SortList_itemClicked(QListWidgetItem *item)
{
    std::string s=item->text().toStdString();
    load_list2(s);
    ui->SortList2->selectRow(0);
    on_SortList2_itemClicked(ui->SortList2->currentItem());
}


void MW::on_pushButton_clicked()
{
    int num= string_to_int(ui->NumBox->text().toStdString());
    if(num==0)return ;
    if(Dname=="")return;
    for(int i=0;i<Di.size();i++){
        if(Di[i]==Dname){
            Di_Num[i]=string_to_int(ui->InfoTab->item(i,1)->text().toStdString())+num;
            if(Di_Num[i]<0)Di_Num[i]=0;
            update_cart();
            return ;
        }
    }
    Di.push_back(Dname);
    Di_Num.push_back(num);
    update_cart();
}

void MW::on_SortList2_itemClicked(QTableWidgetItem *item)
{
    Dname=ui->SortList2->item(item->row(),0)->text().toStdString();
    Dprice=string_to_int(ui->SortList2->item(item->row(),1)->text().toStdString());
}
