#ifndef SQLITE
#define SQLITE

#include <QSql>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <QDate>

class SqLite:public QObject
{
    Q_OBJECT

public:
    SqLite();//初始化，然后检查数据库是否存在，表是否完整，不存在的话要创建
    ~SqLite();//

    bool sql_insert(const QString&);
    bool sql_delete(const QString&);
    bool sql_search(const QString&);
    bool sql_update(const QString&);
    bool sql_error();
    QSqlQuery query;

private:
    QSqlDatabase db;

    QString link_name;//数据库连接名字
    QString db_name;//数据库名字
    QString db_host;//数据库主机名
    QString db_user_name;
    QString db_password;//数据库密码
    int retry_time;//重试次数

    bool create_activaty_table();
    bool create_item_table();
    bool db_exist();//数据库是不是存在
    bool db_perfact();//判断数据库完整性
    bool activaty_table_exist();
    bool item_table_exist();
    int table_number();//返回数据库的表数量
    bool db_build();
    bool delete_out_date_activaty();
    bool delete_out_date_item();


private slots:
    void on_sql_insert(QString);
    void on_update_sql();
    void on_search_sql(QString);

signals:
    void log_changed(QString);
    void get_activaty_map(QMap<int,int>);
    void search_complete(QSqlQuery);
};

#endif // SQLITE

