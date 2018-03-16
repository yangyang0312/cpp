#include "sqlitethread.h"
#include <QEventLoop>


Sqlite_Thread::Sqlite_Thread()
{

}

Sqlite_Thread::~Sqlite_Thread()
{

}

void Sqlite_Thread::run()
{
    SqLite*sqlite=new SqLite();

    //连接数据库插入信号和槽
    connect(this,SIGNAL(sql_insert(QString)),sqlite,SLOT(on_sql_insert(QString)));
    //关联log信号
    connect(sqlite,SIGNAL(log_changed(QString)),this,SIGNAL(log_changed(QString)));
    //关联更新数据库的信号
    connect(this,SIGNAL(update_sql()),sqlite,SLOT(on_update_sql()));
    //关联查询信号
    connect(this,SIGNAL(search_sql(QString)),sqlite,SLOT(on_search_sql(QString)));
    //关联查询完成的返回信号
    connect(sqlite,SIGNAL(search_complete(QSqlQuery)),this,SIGNAL(search_comlete(QSqlQuery)));
    //关联活动列表信号
    connect(sqlite,SIGNAL(get_activaty_map(QMap<int,int>)),this,SIGNAL(get_activaty_map(QMap<int,int>)));


    QEventLoop*event_loop=new QEventLoop();

    QObject::connect(this,SIGNAL(exit_queqiao()),event_loop,SLOT(quit()));

    event_loop->exec();

    delete sqlite;
}
