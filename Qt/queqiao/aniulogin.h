#ifndef ANIULOGIN_H
#define ANIULOGIN_H

#include <QMainWindow>

namespace Ui {
class AniuLogin;
}

class AniuLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit AniuLogin(QWidget *parent = 0);
    ~AniuLogin();

private slots:
    void on_webView_loadFinished(bool arg1);
    void closeEvent(QCloseEvent*event);

private:
    Ui::AniuLogin *ui;
    QString getMcode();
    QString getWMIHWInfo(int type);
public:
    bool is_aniu_;
    void need_aniu();
signals:
    void is_aniu(bool);
};

#endif // ANIULOGIN_H
