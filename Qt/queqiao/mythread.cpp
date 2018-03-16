#include "mythread.h"
#include <QEventLoop>


MyThread::MyThread()
{

}

MyThread::~MyThread()
{

}

void MyThread::run()
{
    Sqlite_Thread *sqlite_th=new Sqlite_Thread();
    Json_Net_Thread *json_net_th=new Json_Net_Thread();

    //关联退出信号
    connect(this,SIGNAL(exit_queqiao()),sqlite_th,SIGNAL(exit_queqiao()));
    connect(this,SIGNAL(exit_queqiao()),json_net_th,SIGNAL(exit_queqiao()));
    //关联log信号
    connect(json_net_th,SIGNAL(log_changed(QString)),this,SIGNAL(log_changed(QString)));
    connect(sqlite_th,SIGNAL(log_changed(QString)),this,SIGNAL(log_changed(QString)));
    //关联登录信号
    connect(this,SIGNAL(alimama_login_flag(QString,QString,QList<QNetworkCookie>)),json_net_th,SIGNAL(alimama_login_flag(QString,QString,QList<QNetworkCookie>)));
    //关联需要登录的信号
    connect(json_net_th,SIGNAL(alimama_need_login()),this,SIGNAL(alimama_need_login()));
    //从json线程发过来的信号插入到sql线程
    connect(json_net_th,SIGNAL(sql_insert(QString)),sqlite_th,SIGNAL(sql_insert(QString)));
    //关联pid需要更新的信号和更新完成的信号
    connect(this,SIGNAL(pid_need_update()),json_net_th,SIGNAL(pid_need_update()));
    connect(json_net_th,SIGNAL(pid_updated(QList<Pid>,QString)),this,SIGNAL(pid_updated(QList<Pid>,QString)));
    //关联数据库中获取到的已存在的活动
    connect(sqlite_th,SIGNAL(get_activaty_map(QMap<int,int>)),json_net_th,SIGNAL(get_activaty_map(QMap<int,int>)));
    //关联更新数据可的信号到数据库，删除过期活动之后获取存在的活动，发送出去json线程控制更新
    connect(this,SIGNAL(update_sql()),sqlite_th,SIGNAL(update_sql()));
    //关联查询信号和查询完成后发回来的信号
    connect(this,SIGNAL(search_sql(QString)),sqlite_th,SIGNAL(search_sql(QString)));
    connect(sqlite_th,SIGNAL(search_comlete(QSqlQuery)),this,SIGNAL(search_comlete(QSqlQuery)));
    //关联图片信号
    connect(this,SIGNAL(need_imagin(QString)),json_net_th,SIGNAL(need_imagin(QString)));
    connect(json_net_th,SIGNAL(imagin_complete()),this,SIGNAL(imagin_complete()));
    //关联item信号
    connect(this,SIGNAL(need_item(QString,QString,QString)),json_net_th,SIGNAL(need_item(QString,QString,QString)));
    connect(json_net_th,SIGNAL(item_complete(Item)),this,SIGNAL(item_complete(Item)));
    //关联短网址完成信号
    connect(json_net_th,SIGNAL(dwz_complete(QString)),this,SIGNAL(dwz_complete(QString)));

    sqlite_th->start();
    json_net_th->start();
    QEventLoop*event_loop=new QEventLoop();

    QObject::connect(this,SIGNAL(exit_queqiao()),event_loop,SLOT(quit()));

    event_loop->exec();

    delete json_net_th;
    delete sqlite_th;
}
