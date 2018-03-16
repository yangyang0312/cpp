#ifndef SQLITETHREAD
#define SQLITETHREAD


#include <QThread>
#include "sqlite.h"

class Sqlite_Thread:public QThread
{
    Q_OBJECT
protected:
    void run();

public:
    Sqlite_Thread();
    ~Sqlite_Thread();

signals:
    //这些是要和主界面交互的信号
    void exit_queqiao();
    void log_changed(QString);

    void update_sql();
    void search_sql(QString);
    void search_comlete(QSqlQuery);
    //内部json_net和sqlite交互的信号，不需要和外面的主界面交互
    void sql_insert(QString);
    void get_activaty_map(QMap<int,int>);
};


#endif // SQLITETHREAD

