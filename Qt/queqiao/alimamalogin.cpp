#include "alimamalogin.h"
#include "ui_alimamalogin.h"
#include "networkcookie.h"
#include <QUrl>
#include <QSettings>
#include <QWebFrame>
#include <QWebElement>
#include <QMessageBox>
#include <QNetworkCookie>
#include <QList>
#include <QNetworkCookieJar>
#include <autoclose.h>

AlimamaLogin::AlimamaLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlimamaLogin),
    m_name(),
    m_alimama_tb_token(),
    cookielist(),
    user_map()
{
    ui->setupUi(this);
    QSettings settings("user.ini",QSettings::IniFormat);
    QMap<QString,QVariant>map=settings.value("user").toMap();
    for(auto i=map.cbegin();i!=map.cend();++i)
    {
        if(i.key().size()>1)
        {
            user_map.insert(i.key(),i.value().toString());
            ui->select->addItem(i.key());
        }
    }
    ui->name->setText(ui->select->currentText());
    ui->pwd->setText(user_map[ui->select->currentText()]);
    ui->login->setFocus();
    ui->login->setDefault(true);
    ui->login->setShortcut(Qt::Key_Enter);
    ui->login->setShortcut(Qt::Key_Return);
    ui->login->setToolTip("点击登录");
    ui->select->setToolTip("选择账户");
    ui->select_s->setToolTip("选择账户");
    ui->pwd->setToolTip("密码");
    ui->pwd_s->setToolTip("密码");
    ui->name->setToolTip("用户名");
    ui->name_s->setToolTip("用户名");
    ui->refresh->setToolTip("点击刷新页面");
}

AlimamaLogin::~AlimamaLogin()
{
    QSettings settings("user.ini",QSettings::IniFormat);
    QMap<QString,QVariant>m;
    if(ui->pwd->text().size()>5)
        user_map.insert(ui->name->text(),ui->pwd->text());
    for(auto i=user_map.cbegin();i!=user_map.cend();++i)
    {
        if(i.key().size()>5)
            m.insert(i.key(),i.value());
    }
    settings.setValue("user",m);
    delete ui;
}

void AlimamaLogin::on_webView_loadFinished(bool arg1)
{
    QString url=ui->webView->url().toString();
    if((url.indexOf("http://www.alimama.com/index.htm"))!=-1)
    {//登录成功
        m_name=ui->webView->page()->mainFrame()->findFirstElement(".menu-username").evaluateJavaScript("this.innerText").toString();

        qDebug()<<m_name;
        if((m_name.indexOf("你好，"))!=-1)
        {
            m_name=m_name.right(m_name.size()-3);
            if(m_name[m_name.size()-1]=='\n')
            {
                m_name=m_name.left(m_name.size()-1);
            }
            qDebug()<<m_name;
        }

        NetworkCookie*cookieJar;
        cookieJar=(NetworkCookie*)ui->webView->page()->networkAccessManager()->cookieJar();
        cookielist=cookieJar->getCookies("http://www.alimama.com/index.htm");
        QString cookie;
        for(auto i:cookielist)
        {
            cookie+=i.name()+"="+i.value()+";";
            if(i.name()=="_tb_token_")//这个网站的_tb_token_有两个，要第二个
            {
                m_alimama_tb_token=i.value();
            }
        }

        //qDebug()<<"获取信息成功";
        //qDebug()<<"cookie"<<cookie;
        //qDebug()<<"alimama_tb_token"<<m_alimama_tb_token;
        //qDebug()<<"taobao_tb_token"<<m_taobao_tb_token;
        //qDebug()<<"num_id"<<m_user_num_id;

        ui->webView->load(QUrl("http://pub.alimama.com/myunion.htm#!/promo/act/activity?toPage=1&eventStatus=5"));
    }
    else if(url=="http://pub.alimama.com/myunion.htm#!/promo/act/activity?toPage=1&eventStatus=5")
    {//获取cookie
        qDebug()<<"name:"<<m_name;
        //qDebug()<<"alimama_tb_token"<<m_alimama_tb_token;
        //qDebug()<<"num_id"<<m_user_num_id;
        qDebug()<<m_name.size()<<cookielist.size()<<m_alimama_tb_token.size();
        if(m_name.size()>0&&cookielist.size()>0&&m_alimama_tb_token.size()>0)
        {
            this->hide();
            emit alimama_login_flag(m_name,m_alimama_tb_token,cookielist);
        }
        else
        {
            QMessageBox(QMessageBox::NoIcon,"错误","未获取到相应信息，登录失败!").exec();
            qDebug()<<"获取登录信息失败！";
        }
    }
    else if(url=="http://www.alimama.com/about.htm")
    {
        ui->webView->load(QUrl("https://login.taobao.com/member/login.jhtml?style=minisimple&from=alimama&redirectURL=http%3A%2F%2Flogin.taobao.com%2Fmember%2Ftaobaoke%2Flogin.htm%3Fis_login%3d1&full_redirect=true&disableQuickLogin=true"));
        //this->show();
    }
}

void AlimamaLogin::on_alimama_need_login()
{
    this->show();
    ui->webView->load(QUrl("http://www.alimama.com/member/logout.htm?forward=http%3A%2F%2Fwww.alimama.com%2Fabout.htm"));
    QWebSettings::clearMemoryCaches();
}

void AlimamaLogin::on_login_clicked()
{
    QString name(ui->name->text());
    QString pwd(ui->pwd->text());

    auto i=user_map.find(name);
    if(i!=user_map.end())
    {//找到
        ;
    }
    else
        ui->select->addItem(name);

    ui->webView->page()->mainFrame()->findFirstElement("#TPL_username_1").evaluateJavaScript("this.value='"+name+"'");
    ui->webView->page()->mainFrame()->findFirstElement("#TPL_password_1").evaluateJavaScript("this.value='"+pwd+"'");
    ui->webView->page()->mainFrame()->findFirstElement("#J_SubmitStatic").evaluateJavaScript("this.click()");
}

void AlimamaLogin::on_refresh_clicked()
{
    ui->webView->load(QUrl("http://www.alimama.com/member/logout.htm?forward=http%3A%2F%2Fwww.alimama.com%2Fabout.htm"));
    QWebSettings::clearMemoryCaches();
}

void AlimamaLogin::on_select_currentIndexChanged(const QString &arg1)
{
    ui->name->setText(arg1);
    ui->pwd->setText(user_map[arg1]);
}
