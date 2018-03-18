#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include "networkcookie.h"

typedef struct
{
    QString m_name;
    QString m_time;
    QString m_number;
    QString m_url;
}order_info;

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

private slots:
    void on_login_flag(QString name,QString tb_token,QString seller_num_id,QList<QNetworkCookie> cookielist);
    void on_start_clicked();
    void on_stop_clicked();
    void on_pushButton_clicked();
    void auto_scroll();
    void on_order_changed();

private:
    QString m_name;
    QString m_tb_token;
    QString m_seller_num_id;
    QString m_search_name;
    QString m_close_reason;
    QString detail;//详情，同步到ui->detail
    QString order;//全部订单，同步到ui->order
    QVector <order_info>order_list;
    QMap <QString,QString>order_map;
    QMap <QString,QString>detail_map;
    QString post_url;
    bool stop_flag;
    QNetworkAccessManager*network_manager;
    QList<QNetworkCookie> cookie;


    int translate_html_to_order(QString html);
    //void http_post(QByteArray post_data);
    void get_order_list();
    void trade_close();
signals:
    void order_changed();
    void post_complete(QString html);
    void detail_changed();
};

#endif // MAINWINDOW_H
