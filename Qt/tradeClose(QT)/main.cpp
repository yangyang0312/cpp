#include "mainwindow.h"
#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Login login;

    QObject::connect(&login,SIGNAL(login_flag(QString,QString,QString,QList<QNetworkCookie>)),&w,SLOT(on_login_flag(QString,QString,QString,QList<QNetworkCookie>)));

    login.show();
    return a.exec();
}
