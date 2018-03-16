#ifndef JSON_NETTHREAD
#define JSON_NETTHREAD


#include <QThread>
#include "json_net.h"

class Json_Net_Thread:public QThread
{
    Q_OBJECT
protected:
    void run();

public:
    Json_Net_Thread();
    ~Json_Net_Thread();

signals:
    //与主界面交互的
    void exit_queqiao();
    void log_changed(QString);

    void alimama_login_flag(QString m_user_name,QString m_alimama_tb_token,QList<QNetworkCookie> m_cookie_list);
    void alimama_need_login();
    void pid_need_update();
    void pid_updated(QList<Pid>pid_list,QString);
    void need_imagin(QString);
    void imagin_complete();
    void need_item(QString,QString,QString);
    void item_complete(Item);
    void dwz_complete(QString);
    //不与主界面交互的
    void sql_insert(QString);
    void get_activaty_map(QMap<int,int>);//获取已存在于数据库中的活动
};


#endif // JSON_NETTHREAD

