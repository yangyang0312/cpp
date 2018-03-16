#ifndef JSON_NET
#define JSON_NET

#include <QNetworkCookie>
#include <json/json.h>
#include "sqlite.h"
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QEventLoop>
#include <QFile>
#include <QList>
#include "queqiaostruct.h"
#include <QMap>
#include "autoclose.h"
#include <QSettings>

class Json_Net:public QObject//获取内容，解析成queqiaostruct
{
    Q_OBJECT

public:
    Json_Net();
    ~Json_Net();

private:
    QString m_user_name;
    QString m_user_num_id;
    QString m_alimama_tb_token;
    QList<QNetworkCookie>m_cookie_list;
    QNetworkAccessManager*alimama_network_manager;
    QByteArray response;
    QString default_pid;
    QList<Pid>pid_list;
    bool login_flag;
    QString insert_s;

public:
    void inline get_default_pid();
    bool http_post(const QString &url,const QByteArray &posy_data,QByteArray&response);
    bool http_get(const QString &url,QByteArray&response);

    bool json_ok(Json::Value &root,const QByteArray &data);//读json,返回root,判断json是否正常

    bool activaty_get(const int &page,QList<Activaty>&activaty_list,const int &page_size,bool&has_next_page,int &total_page);//获取一个页活动，解析到一个Activaty的list中
    bool json_to_activaty(Json::Value&root,QList<Activaty>&activaty_list,bool &has_next_page,int &total_page);
    bool insert_activaty(const QList<Activaty>&activaty_list);

    bool item_get(const int &eventId,const QString&pid,QList<Item>&item_list,const int &page=1,const int&page_size=1000);
    bool item_get_insert(const int &eventId,const QString&pid,const int &page=1,const int&page_size=1000);
    bool json_to_item(const int&eventId,Json::Value &root, QList<Item>&item_list,bool&has_next_page);
    bool json_to_item_insert(const int&eventId,Json::Value &root,bool&has_next_page);
    bool insert_item(const QList<Activaty> &activaty_list);

    bool pid_get(QList<Pid>&pid_list);
    bool json_to_pid(Json::Value&root,QList<Pid>&pid_list);
    bool get_pid_list();

    int date_to_int(QString date);
    bool activaty_contain(QMap<int,int>&activaty_map,QList<Activaty>&activaty_list);

    bool get_dwz(QString);

private slots:
    void on_alimama_login_flag(QString m_user_name,QString m_alimama_tb_token,QList<QNetworkCookie> m_cookie_list);
    void on_pid_need_update();
    void on_update(QMap<int,int>);
    void on_need_imagin(QString);
    void on_need_item(QString,QString,QString);

signals:
    void pid_need_update();
    void sql_insert(QString);
    void alimama_need_login();
    void pid_updated(QList<Pid>pid_list,QString);
    void log_changed(QString);
    void imagin_complete();
    void item_complete(Item);
    void dwz_complete(QString);
};


#endif // JSON_NET
