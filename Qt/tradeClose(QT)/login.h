#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QNetworkCookie>
#include "networkcookie.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;

signals:
    //这个信号发出，表明已经登录成功了
    void login_flag(QString name,QString tb_token,QString seller_num_id,QList<QNetworkCookie> cookielist);
private slots:
    void on_WebView_loadFinished(bool arg1);
};

#endif // LOGIN_H
