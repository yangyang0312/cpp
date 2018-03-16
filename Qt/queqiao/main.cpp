#include "mainwindow.h"
#include <QApplication>
#include "alimamalogin.h"
#include "mythread.h"
#include <QSqlQuery>
#include "itemdetail.h"
#include <aniulogin.h>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+"plugins");
    a.addLibraryPath(strLibPath);


    qRegisterMetaType<QList<Pid> >("QList<Pid>");
    qRegisterMetaType<QSqlQuery>("QSqlQuery");
    qRegisterMetaType<Item>("Item");
    qRegisterMetaType<QMap<int,int> >("QMap<int,int>");
    MainWindow main_window;
    AlimamaLogin alimama_login;
    MyThread thread;
    itemdetail detail;

    //登录信号连接到主窗口槽
    QObject::connect(&alimama_login,SIGNAL(alimama_login_flag(QString,QString,QList<QNetworkCookie>)),&main_window,SLOT(on_alimama_login_flag(QString,QString,QList<QNetworkCookie>)));
    //登录信号连接到线程登录信号
    QObject::connect(&alimama_login,SIGNAL(alimama_login_flag(QString,QString,QList<QNetworkCookie>)),&thread,SIGNAL(alimama_login_flag(QString,QString,QList<QNetworkCookie>)));
    //主窗口需要登录的信号连接到登录槽
    QObject::connect(&main_window,SIGNAL(alimama_need_login()),&alimama_login,SLOT(on_alimama_need_login()));
    //线程需要登录的信号连接到主窗口需要登录的信号
    QObject::connect(&thread,SIGNAL(alimama_need_login()),&main_window,SIGNAL(alimama_need_login()));
    //连接主窗口的关闭信号到线程，通知退出
    QObject::connect(&main_window,SIGNAL(exit_queqiao()),&thread,SIGNAL(exit_queqiao()));
    //关联主窗口pid需要更新信号到线程信号
    QObject::connect(&main_window,SIGNAL(pid_need_update()),&thread,SIGNAL(pid_need_update()));
    //关联主窗口pid已经更新的槽和线程相关信号
    QObject::connect(&thread,SIGNAL(pid_updated(QList<Pid>,QString)),&main_window,SLOT(pid_updated(QList<Pid>,QString)));
    QObject::connect(&detail,SIGNAL(pid_need_update()),&main_window,SLOT(on_pid_update_clicked()));
    QObject::connect(&thread,SIGNAL(pid_updated(QList<Pid>,QString)),&detail,SLOT(on_pid_updated(QList<Pid>,QString)));
    //关联log信息
    QObject::connect(&alimama_login,SIGNAL(log_changed(QString)),&main_window,SLOT(on_log_changed(QString)));
    QObject::connect(&main_window,SIGNAL(log_changed(QString)),&main_window,SLOT(on_log_changed(QString)));
    QObject::connect(&thread,SIGNAL(log_changed(QString)),&main_window,SLOT(on_log_changed(QString)));
    QObject::connect(&detail,SIGNAL(log_changed(QString)),&main_window,SLOT(on_log_changed(QString)));
    //关联主窗口更新数据库信号到线程数据库更新槽
    QObject::connect(&main_window,SIGNAL(update_sql()),&thread,SIGNAL(update_sql()));
    //关联搜索信号
    QObject::connect(&main_window,SIGNAL(search_sql(QString)),&thread,SIGNAL(search_sql(QString)));
    QObject::connect(&thread,SIGNAL(search_comlete(QSqlQuery)),&main_window,SLOT(on_search_complete(QSqlQuery)));
    //关联查看详情信号
    QObject::connect(&main_window,SIGNAL(need_detail(Table)),&detail,SLOT(on_need_detail(Table)));
    //关联图片信号
    QObject::connect(&main_window,SIGNAL(need_imagin(QString)),&thread,SIGNAL(need_imagin(QString)));
    QObject::connect(&thread,SIGNAL(imagin_complete()),&detail,SLOT(on_imagin_complete()));
    //关联更新item信号
    QObject::connect(&detail,SIGNAL(need_item(QString,QString,QString)),&thread,SIGNAL(need_item(QString,QString,QString)));
    QObject::connect(&thread,SIGNAL(item_complete(Item)),&detail,SLOT(on_item_complete(Item)));
    QObject::connect(&thread,SIGNAL(dwz_complete(QString)),&detail,SLOT(on_dwz_complete(QString)));

    thread.start();
    return a.exec();
}
