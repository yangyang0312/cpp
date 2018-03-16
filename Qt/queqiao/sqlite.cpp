#include "sqlite.h"
#include <QSqlError>

SqLite::SqLite():
    db(),
    link_name("db_link"),
    db_name("data.db"),
    db_host("localhost"),
    db_user_name("root"),
    db_password("yangyang"),
    retry_time(3)
{
    //qDebug()<<link_name<<db_name<<db_host<<db_user_name<<db_password;
///////////初始化db///////////////////////////////////////////////////////////////////////////////////
    if(QSqlDatabase::contains(link_name))
        db=QSqlDatabase::database(link_name);
    else
        db=QSqlDatabase::addDatabase("QSQLITE",link_name);
    db.setHostName(db_host);
    db.setPassword(db_password);
    db.setUserName(db_user_name);
    db.setDatabaseName(db_name);

    QSqlQuery q(db);
    query=q;

    if(db.open())
    {
        //qDebug()<<"数据库打开";
////////////判断数据库文件是不是存在，存在的话判断表的完整性，不存在或者不完整，重新建表///////////////////
        if(db_exist())
        {
            emit log_changed("数据库存在\r\n");
            if(db_perfact())
            {
                emit log_changed("数据库完整\r\n");
            }
            else
            {
                int count=0;
                while(++count)
                {
                    if(db_build())
                        break;
                    if(count>retry_time)
                    {
                        emit log_changed("重试建表失败\r\n");
                        break;
                    }
                }
            }
        }
        else
        {
            emit log_changed("数据库不存在\r\n");
            int count=0;
            while(++count)
            {
                if(db_build())
                {
                    emit log_changed("重建数据库成功\r\n");
                    break;
                }
                if(count>retry_time)
                {
                    emit log_changed("重试建表失败\r\n");
                    break;
                }
            }
        }
    }
    else
    {
        emit log_changed("数据库未能打开\r\n");
    }
}

SqLite::~SqLite()
{
    db.close();
}

bool SqLite::sql_delete(const QString &s)
{
    qDebug()<<s;
    if(query.exec(s))
        return true;
    else
    {
        sql_error();
        qDebug()<<s;
    }
    return false;
}

bool SqLite::sql_insert(const QString &s)
{
    qDebug()<<"正在插入";
    if(query.exec(s))
    {
        return true;
    }
    else
    {
        sql_error();
        QFile file("error.txt");
        file.open(QIODevice::Append);
        file.write(s.toLocal8Bit());
        file.close();
    }
    return false;
}

bool SqLite::sql_search(const QString &s)
{
    qDebug()<<"正在查询"<<s;
    if(query.exec(s))
        return true;
    else
        sql_error();
    return false;
}

bool SqLite::sql_update(const QString &s)
{
    if(query.exec(s))
        return true;
    else
        sql_error();
    return false;
}

bool SqLite::create_activaty_table()
{
    if(query.exec("create table activaty ("
               "eventId int primary key not null,"
               "previewUrl varchar(100) not null,"
               "startTime int not null,"
               "endTime int not null,"
               "shareRate double not null,"
               "eventStatus int not null,"
               "eventStatusStr varchar(20) not null,"
               "alipayNum int,"
               "cvr double,"
               "avgCommission double,"
               "tkLevel int,"
               "eventTitle varchar(1000),"
               "comments varchar(1000),"
               "platformType int,"
               "platformTypeStr varchar(10),"
               "promotionType int,"
               "promotionTypeStr varchar(100),"
               "auditEndTime varchar(30),"
               "createFinish int,"
               "canOperate int,"
               "canEditFloor int,"
               "highQualityType int"
               ")"))
    {
        emit log_changed("活动表建立完成");
        return true;
    }
    else
        sql_error();
    return false;
}

bool SqLite::create_item_table()
{
    if(query.exec("create table item ("
                  "itemId varchar(12) not null,"
                  "eventId int not null,"
                  "sellerId varchar(12),"
                  "itemTitle varchar(512),"
                  "picUrl varchar(100),"
                  "tag int,"
                  "commissionRate int,"
                  "isSoldOut int,"
                  "discountPrice double,"
                  "auctionPrice double,"
                  "discountRate double,"
                  "soldQuantity int,"
                  "mall int,"
                  "primary key (itemId,eventId)"//活动id加上商品id作为主键
                  ")"))
    {
        emit log_changed("item表创建完成");
        return true;
    }
    else
        sql_error();
    return false;
}

bool SqLite::db_exist()
{
    if(QFile::exists(db_name))
    {
        return true;
    }
    return false;
}

bool SqLite::db_perfact()
{
    int table_num=table_number();
    if(table_num<=0)
    {
        emit log_changed("数据库表数量为0");
        return false;
    }
    else
    {
        emit log_changed(QString("存在的表的数量")+QString::number(table_num)+"个");
        if(item_table_exist()&&activaty_table_exist())
        {
            emit log_changed("表属性完整");
            return true;
        }
        else
        {
            emit log_changed("表格属性不完整");
            return false;
        }
    }
}

bool SqLite::item_table_exist()
{
    QVector<QString>item_;
    item_.push_back("itemId");
    item_.push_back("eventId");
    item_.push_back("sellerId");
    item_.push_back("itemTitle");
    item_.push_back("picUrl");
    item_.push_back("tag");
    item_.push_back("commissionRate");
    item_.push_back("isSoldOut");
    item_.push_back("discountPrice");
    item_.push_back("auctionPrice");
    item_.push_back("discountRate");
    item_.push_back("soldQuantity");
    item_.push_back("mall");

    QVector<QString>temp;
    if(query.exec("PRAGMA table_info (item)"))
    {
        while(1)
        {
            if(query.next())
            {
                //qDebug()<<query.value(1).toString();
                temp.push_back(query.value(1).toString());
            }
            else
            {
                emit log_changed("表属性查询结束");
                break;
            }
        }
    }
    else
    {
        emit log_changed("PRAGMA执行失败");
        sql_error();
        return false;
    }
    if(temp==item_)
    {
        emit log_changed("item表属性完整");
        return true;
    }
    return false;
}

int SqLite::table_number()
{
    int count=0;
    if(query.exec(QString("select name from sqlite_master where type='table'")))
    {

        while(query.next())
        {
            //qDebug()<<query.value(0).toString();
            ++count;
        }
    }
    else
    {
        emit log_changed("查询表数量失败");
        sql_error();
    }
    return count;
}

bool SqLite::activaty_table_exist()
{
    QVector<QString> ac_;
    ac_.push_back("eventId");
    ac_.push_back("previewUrl");
    ac_.push_back("startTime");
    ac_.push_back("endTime");
    ac_.push_back("shareRate");
    ac_.push_back("eventStatus");
    ac_.push_back("eventStatusStr");
    ac_.push_back("alipayNum");
    ac_.push_back("cvr");
    ac_.push_back("avgCommission");
    ac_.push_back("tkLevel");
    ac_.push_back("eventTitle");
    ac_.push_back("comments");
    ac_.push_back("platformType");
    ac_.push_back("platformTypeStr");
    ac_.push_back("promotionType");
    ac_.push_back("promotionTypeStr");
    ac_.push_back("auditEndTime");
    ac_.push_back("createFinish");
    ac_.push_back("canOperate");
    ac_.push_back("canEditFloor");
    ac_.push_back("highQualityType");

    QVector<QString>temp;
    if(query.exec("PRAGMA table_info (activaty)"))
    {
        while(1)
        {
            if(query.next())
            {
                //qDebug()<<query.value(1).toString();
                temp.push_back(query.value(1).toString());
            }
            else
            {
                emit log_changed("表属性查询结束");
                break;
            }
        }
    }
    else
    {
        emit log_changed("activaty PRAGMA执行失败");
        sql_error();
        return false;
    }
    if(temp==ac_)
    {
        emit log_changed("activaty表格属性完整");
        return true;
    }
    return false;
}

bool SqLite::db_build()
{
    if(create_activaty_table()&&create_item_table())
        emit log_changed("数据库建立完成");
    if(db_perfact())
    {
        emit log_changed("数据库完整");
        return true;
    }
    else
    {
        emit log_changed("数据库不完整");
        return false;
    }

}

void SqLite::on_sql_insert(QString s)
{
    sql_insert(s);
}

void SqLite::on_update_sql()
{
    QDate date=QDate::currentDate();
    emit log_changed(QString("获取系统时间成功")+date.toString("yyyy-MM-dd")+"\r\n");
    int time=date.toString("yyyyMMdd").toInt();
    emit log_changed("正在删除过期活动...\r\n请稍候...\r\n");
    QString s1("delete from item where eventId not in (select eventId from activaty)");
    QString s2("delete from activaty where eventId not in(select eventId from item group by eventId)");
    QString s3=QString("delete from item where eventId in (select eventId from activaty where endTime<")+QString::number(time)+")";
    QString s4=QString("delete from activaty where endTime<")+QString::number(time);
    if(sql_delete(s1)&&sql_delete(s2))
    {
        if(sql_delete(s3))
            if(sql_delete(s4))
                emit log_changed(QString("已删除活动结束时间小于 ")+date.toString("yyyy-MM-dd")+"的活动\r\n");
            else
                emit log_changed(QString("删除活动结束时间小于 ")+date.toString("yyyy-MM-dd")+" 的活动失败\r\n");
        else
            emit log_changed(QString("删除活动结束时间小于 ")+date.toString("yyyy-MM-dd")+" 的活动失败\r\n");
    }
    else
        emit log_changed(QString("删除活动结束时间小于 ")+date.toString("yyyy-MM-dd")+" 的活动失败\r\n");
    if(sql_search("select eventId from activaty"))
    {
        QMap<int,int>activaty_map;
        while(query.next())
        {
            activaty_map.insert(query.value(0).toInt(),query.value(0).toInt());
        }
        emit log_changed("数据库中获取活动成功！\r\n正在更新数据库...\r\n");
        emit get_activaty_map(activaty_map);
    }
    else
    {
        emit log_changed("数据库中获取活动失败！无法更新数据,请重试...\r\n");
    }
}

bool SqLite::sql_error()
{
    QSqlError error=query.lastError();
    emit log_changed(QString("error:")+error.driverText()+("\r\nerror type:")+QString::number(error.type())+"\r\n");
    return true;
}

void SqLite::on_search_sql(QString s)
{
    if(sql_search(s))
    {
        qDebug()<<"查询成功sqlite";
        emit search_complete(query);
    }
    else
    {
        emit log_changed(QString("查询")+s+("失败,正在重试\r\n"));
        if(sql_search(s))
        {
            emit search_complete(query);
            emit log_changed("重试查询成功\r\n");
        }
        else
        {
            emit log_changed(QString("查询")+s+("失败,跳过,请手动重试\r\n"));
        }
    }
}
