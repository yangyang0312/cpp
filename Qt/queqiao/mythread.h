#ifndef MYTHREAD
#define MYTHREAD

#include <QThread>
#include "sqlitethread.h"
#include "json_netthread.h"


class MyThread:public QThread
{
    Q_OBJECT
protected:
    void run();

public:

public:
    MyThread();
    ~MyThread();

signals:
    //要与主界面交互的
    void alimama_login_flag(QString m_user_name,QString m_alimama_tb_token,QList<QNetworkCookie> m_cookie_list);
    void alimama_need_login();
    void exit_queqiao();
    void pid_need_update();
    void pid_updated(QList<Pid>pid_list,QString);
    void log_changed(QString);
    void update_sql();
    void search_sql(QString);
    void search_comlete(QSqlQuery);
    void need_imagin(QString);
    void imagin_complete();
    void need_item(QString,QString,QString);
    void item_complete(Item);
    void dwz_complete(QString);
    //不和主界面交互的直接关联吧。。

};


#endif // MYTHREAD

