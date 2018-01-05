#ifndef OK_H
#define OK_H
#include <QDialog>
#include <string>

namespace Ui {
class OK;
}

class OK : public QDialog
{
    Q_OBJECT

public:
    explicit OK(QWidget *parent = 0);
    void Info(std::string s);
    ~OK();

private slots:
    void on_AfrBtn_clicked();
private:
    Ui::OK *ui;
};

#endif // OK_H
