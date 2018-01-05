#ifndef COMMENT_H
#define COMMENT_H

#include <QDialog>
#include <string>
#include "waiting.h"
#include "exit.h"

namespace Ui {
class Comment;
}

class Comment : public QDialog
{
    Q_OBJECT

public:
    explicit Comment(QWidget *parent = 0);
    void Load(int _Gno,std::string name);
    int Gno;
    std::string Dname;
    ~Comment();
    Waiting wa;
    Exit ex;


private slots:
    void on_BackBtn_clicked();

    void on_SubBtn_clicked();

private:
    Ui::Comment *ui;
};

#endif // COMMENT_H
