#include "function.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font  = qApp->font();
    font.setPointSize(16);
    qApp->setFont(font);
    Login L_page;

    L_page.exec();

    return a.exec();
}
