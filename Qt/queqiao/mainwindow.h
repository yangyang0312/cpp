#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkCookie>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <json/json.h>
#include "queqiaostruct.h"
#include "sqlite.h"
#include <QCalendarWidget>
#include <QRect>
#include <QDate>
#include <QSqlQuery>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "aniulogin.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void alimama_need_login();
    void update_activaty();
    void exit_queqiao();
    void pid_need_update();
    void log_changed(QString);
    //这个是检查到更新的时候更新数据库
    void update_sql();
    void search_sql(QString);
    void need_detail(Table);
    void need_imagin(QString);

private slots:
    void on_alimama_login_flag(QString m_user_name,QString m_alimama_tb_token,QList<QNetworkCookie> m_cookie_list);
    void closeEvent(QCloseEvent*event);
    void pid_updated(QList<Pid>pid_list,QString);
    void on_pid_update_clicked();
    void on_begin_time_select_clicked();
    void on_begin_time_changed(QDate);
    void on_sort_clicked();
    void on_repeat_clicked();
    void on_login_clicked();
    void on_start_clicked();
    void on_log_changed(QString s);
    void on_update_clicked();
    void on_search_complete(QSqlQuery);
    void table_changed();
    void on_table_clicked(const QModelIndex &index);
    void on_table_doubleClicked(const QModelIndex &index);
    void resizeEvent(QResizeEvent *);
    //是阿牛的人允许，不然不允许，退出
    void is_aniu(bool);
    //自动更新
    bool checkUpdate();
    QByteArray http_get(const QString &url);

private:
    QString m_user_name;
    QString m_alimama_tb_token;
    QList<QNetworkCookie>m_cookie_list;
    QNetworkAccessManager*alimama_network_manager;
    QList<Pid>pid_list;
    QCalendarWidget*calendar;
    bool is_login;
    QString log;
    QList<Table>table_list;
    int get_days(const int& start);
    bool is_number(QString);
    AniuLogin aniu_login;
    QString version;//版本号

public:


};

#endif // MAINWINDOW_H
