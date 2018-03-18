#include "login.h"
#include "ui_login.h"

#include <QtCore/QUrl>
#include <QtWebKitWidgets/qwebview.h>
#include <QWebFrame>
#include <QWebElement>
#include <QMessageBox>
#include <QNetworkCookieJar>
#include "networkcookie.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->WebView->load(QUrl("https://login.taobao.com/member/login.jhtml?style=minisimple&disableQuickLogin=true"));
}

Login::~Login()
{
    delete ui;
}

void Login::on_WebView_loadFinished(bool arg1)
{
    QString url=ui->WebView->url().toString();
    if(url=="https://www.taobao.com/"||url == "https://www.taobao.com")
    {
        ui->WebView->load(QUrl("https://login.taobao.com/member/login.jhtml?style=minisimple&disableQuickLogin=true"));
    }
    else if(-1!=url.indexOf("https://i.taobao.com/my_taobao.htm"))
    {
        ui->WebView->load(QUrl("https://mai.taobao.com/seller_admin.htm"));
    }
    else if(url=="https://mai.taobao.com/seller_admin.htm")
    {
        this->hide();
        QString name=ui->WebView->page()->mainFrame()->findFirstElement("#seller-nav").evaluateJavaScript("this.innerText").toString();
        int name_start = name.indexOf("卖家手机端");
        int name_end = name.indexOf("退出");
        if(name_start==-1||name_end==-1)
        {
            QMessageBox(QMessageBox::NoIcon,"","获取用户名失败！");
        }
        else
        {
            name=name.mid(name_start+6,name_end-name_start-8);
        }
        //获取cookie到一个QString里边去
        NetworkCookie*cookieJar;
        cookieJar=(NetworkCookie*)ui->WebView->page()->networkAccessManager()->cookieJar();
        QList<QNetworkCookie>cooklist=cookieJar->getCookies();
        //QString cookieStr;
        QString seller_num_id;//卖家数字id
        QString tb_token;//标示登录的东西
        QString cookie;
        for(auto i:cooklist)
        {
            cookie+=i.name()+"="+i.value()+";";
            //cookieStr+=i.name()+"="+i.value()+";";
            if(i.name()=="_tb_token_")
            {
                tb_token=i.value();
                //QMessageBox(QMessageBox::NoIcon,"",i.value()).exec();
            }
            else if(i.name()=="unb")
            {
                seller_num_id=i.value();
                //QMessageBox(QMessageBox::NoIcon,"",i.value()).exec();
            }
        }
        emit login_flag(name,tb_token,seller_num_id,cooklist);
        //QMessageBox(QMessageBox::NoIcon,"",name).exec();
    }
}
