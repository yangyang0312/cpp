#include "json_netthread.h"
#include <QEventLoop>


Json_Net_Thread::Json_Net_Thread()
{

}

Json_Net_Thread::~Json_Net_Thread()
{

}

void Json_Net_Thread::run()
{
    Json_Net*json_net=new Json_Net();
    //连接登录和需要登录的信号
    connect(this,SIGNAL(alimama_login_flag(QString,QString,QList<QNetworkCookie>)),json_net,SLOT(on_alimama_login_flag(QString,QString,QList<QNetworkCookie>)));
    connect(json_net,SIGNAL(alimama_need_login()),this,SIGNAL(alimama_need_login()));
    //连接插入数据库的信号
    connect(json_net,SIGNAL(sql_insert(QString)),this,SIGNAL(sql_insert(QString)));
    //连接pid需要更新的信号和pid更新完成的信号
    connect(this,SIGNAL(pid_need_update()),json_net,SLOT(on_pid_need_update()));
    connect(json_net,SIGNAL(pid_updated(QList<Pid>,QString)),this,SIGNAL(pid_updated(QList<Pid>,QString)));
    //关联log信号
    connect(json_net,SIGNAL(log_changed(QString)),this,SIGNAL(log_changed(QString)));
    //关联数据库获取到的数据库已存在的活动的信号到更新槽，以便控制更新
    connect(this,SIGNAL(get_activaty_map(QMap<int,int>)),json_net,SLOT(on_update(QMap<int,int>)));
    //关联图片信号
    connect(this,SIGNAL(need_imagin(QString)),json_net,SLOT(on_need_imagin(QString)));
    connect(json_net,SIGNAL(imagin_complete()),this,SIGNAL(imagin_complete()));
    //关联item信号
    connect(this,SIGNAL(need_item(QString,QString,QString)),json_net,SLOT(on_need_item(QString,QString,QString)));
    connect(json_net,SIGNAL(item_complete(Item)),this,SIGNAL(item_complete(Item)));
    //关联dwz信号
    connect(json_net,SIGNAL(dwz_complete(QString)),this,SIGNAL(dwz_complete(QString)));


    QEventLoop*event_loop=new QEventLoop();

    QObject::connect(this,SIGNAL(exit_queqiao()),event_loop,SLOT(quit()));

    event_loop->exec();

    delete json_net;
}
