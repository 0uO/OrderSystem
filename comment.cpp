#include "comment.h"
#include "ui_comment.h"
#include "function.h"
#include "ok.h"
#include "error.h"
#include <string>
#include <vector>

Comment::Comment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Comment)
{
    ui->setupUi(this);
}

Comment::~Comment()
{
    delete ui;
}

void Comment::Load(int _Gno,std::string _name){
    Gno=_Gno;
    Dname=_name;
    ui->textBrowser->clear();
    std::vector<int> Gno_c;
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    QString qs;
    std::vector<std::string> s= handle.get_evalution(Dname.c_str(),Gno_c);
    for(int i=0;i<s.size();i++){
        qs.sprintf("\n\t\t\t-- By ID: %d\n",Gno_c[i]);
        ui->textBrowser->insertPlainText(QString::fromStdString(s[i]));
        ui->textBrowser->insertPlainText(qs);
    }

    handle.close();
}

void Comment::on_BackBtn_clicked()
{
    this->close();
}

void Comment::on_SubBtn_clicked()
{
    string s = ui->CmtTe->toPlainText().toStdString();
    if(s.size()>255){
        Error Ero;
        std::string s="Text too long!";
        Ero.Info(s);
        Ero.exec();
        return ;
    } else if(s==""){
        Error Ero;
        std::string s="Text NULL!";
        Ero.Info(s);
        Ero.exec();
        return ;
    }
    OrderSystem handle;
    handle. connect_to();
    if(!handle.check_link())
        ex.exec();
    handle.add_evalution(Gno,Dname.c_str(),s.c_str());
    handle.close();

    Load(Gno,Dname);
    OK Ok;
    Ok.exec();
}
