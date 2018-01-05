#ifndef ERROR_H
#define ERROR_H

#include <QDialog>

namespace Ui {
class Error;
}

class Error : public QDialog
{
    Q_OBJECT

public:
    explicit Error(QWidget *parent = 0);
    void Info(std::string s);
    ~Error();

private slots:
    void on_AfrBtn_clicked();

private:
    Ui::Error *ui;
};

#endif // ERROR_H
