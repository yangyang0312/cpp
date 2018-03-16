#ifndef ALIMAMALOGIN_H
#define ALIMAMALOGIN_H
#include <QNetworkCookie>
#include <QMainWindow>
#include <QVariant>

namespace Ui {
class AlimamaLogin;
}

class AlimamaLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlimamaLogin(QWidget *parent = 0);
    ~AlimamaLogin();

private:
    Ui::AlimamaLogin *ui;

signals:
    //这个信号发出，表明已经登录成功了
    void alimama_login_flag(QString name,QString alimama_tb_token,QList<QNetworkCookie> cookielist);
    void log_changed(QString);

private slots:
    void on_webView_loadFinished(bool arg1);
    void on_alimama_need_login();
    void on_login_clicked();
    void on_refresh_clicked();
    void on_select_currentIndexChanged(const QString &arg1);

private:
    QString m_name;
    QString m_alimama_tb_token;
    QList<QNetworkCookie> cookielist;
    QMap<QString,QString>user_map;
};

#endif // ALIMAMALOGIN_H
