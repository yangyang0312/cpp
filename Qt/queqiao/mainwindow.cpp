#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkCookieJar>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QEventLoop>
#include <QFile>
#include <json/json.h>
#include "autoclose.h"
#include "itemdetail.h"
#include <QDate>
#include <QSettings>
#include <QDesktopServices>
#include <regex>
#include <fstream>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_cookie_list(),
    m_user_name(),
    m_alimama_tb_token(),
    alimama_network_manager(),
    pid_list(),
    is_login(false),
    log(),
    table_list(),
    aniu_login(),
    version("1.1")
{
    if(checkUpdate())
    {
        QMessageBox(QMessageBox::NoIcon,"新版本","发现新版本，点击确定升级").exec();
        QString program = "update.exe";
        QStringList arguments;
        arguments << "update.txt";
        QProcess myProcess;
        myProcess.start(program,arguments);
        exit(0);
    }
    //setupui之前检查更新

    ui->setupUi(this);

    ui->key_word->setToolTip("输入商品关键词查询，商品关键词越准确查询越快，选填");
    ui->key_word_s->setToolTip("输入商品关键词查询，商品关键词越准确查询越快，选填");

    ui->id->setToolTip("根据商品id查询，选填");
    ui->id_s->setToolTip("根据商品id查询，选填");

    ui->price_high->setToolTip("选择商品现价范围,选填");
    ui->price_low->setToolTip("选择商品现价范围,选填");
    ui->price_s->setToolTip("选择商品现价范围,选填");
    ui->price_s_->setToolTip("选择商品现价范围,选填");

    ui->com_rate_high->setToolTip("选择佣金比例范围，选填");
    ui->com_rate_low->setToolTip("选择佣金比例范围，选填");
    ui->com_rate_s->setToolTip("选择佣金比例范围，选填");
    ui->com_rate_s_->setToolTip("选择佣金比例范围，选填");

    ui->sold->setToolTip("选择销量范围，选填");
    ui->sold_s->setToolTip("选择销量范围，选填");

    ui->event_id->setToolTip("根据活动id查询,选填");
    ui->event_id_s->setToolTip("根据活动id查询，选填");

    ui->begin_time->setToolTip("根据弹出的日历选择适当的日期");
    ui->begin_time_s->setToolTip("根据弹出的日历选择适当的日期");
    ui->begin_time_select->setToolTip("根据弹出的日历选择适当的日期");

    ui->repeat->setToolTip("选择结果是否去重，去重的话只保留最高佣金的结果");

    ui->sort->setToolTip("选择显示结果是升序还是降序");

    ui->sort_method->addItem("按佣金比例");
    ui->sort_method->addItem("按佣金");
    ui->sort_method->addItem("按销量");
    ui->sort_method->addItem("按现价");
    ui->sort_method->addItem("按时间");
    ui->sort_method->setToolTip("选择查询后的排序方式");
    ui->sort_method_s->setToolTip("选择查询后的排序方式");

    ui->share_rate->addItem("全部");
    ui->share_rate->addItem("100%");
    ui->share_rate->addItem("95%");
    ui->share_rate->addItem("90%");
    ui->share_rate->addItem("80%");
    ui->share_rate->setToolTip("选择活动发起者分成比例");
    ui->share_rate_s->setToolTip("选择活动发起者分成比例");

    ui->type->addItem("全部");
    ui->type->addItem("天猫");
    ui->type->addItem("淘宝");
    ui->type->setToolTip("选择店铺类型");
    ui->type_s->setToolTip("选择店铺类型");

    ui->start->setFocus();
    ui->start->setDefault(true);
    ui->start->setShortcut(Qt::Key_Enter);
    ui->start->setShortcut(Qt::Key_Return);
    ui->start->setToolTip("点击开始查询");

    ui->com_rate_low->setText("30");
    ui->com_rate_high->setText("100");
    ui->sold->setText("20");
    ui->begin_time->setText("2015-01-01");
    ui->repeat->setChecked(false);
    ui->sort->setChecked(true);
    ui->user_name_s->setText("未登录");

    ui->login->setText("登录");
    ui->login->setToolTip("点击登录");

    ui->pid_update->setToolTip("点击更新推广位");

    ui->login_time->setToolTip("登录时长");
    ui->login_time_s->setToolTip("登录时长");

    ui->update->setToolTip("点击更新数据库");

    ui->table->setColumnCount(12);
    QStringList headers;
    headers<<"活动标题"<<"商品名称"<<"原价"<<"现价"<<"佣金比例"<<"佣金"<<"总销量"<<"淘客地址"<<"推广时间"<<"推广天数"<<"类别"<<"分成";
    ui->table->setHorizontalHeaderLabels(headers);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setToolTip("双击查看详情");

    this->calendar=new QCalendarWidget(this);
    this->calendar->hide();

    //检查日志文件大小，大了就删除它
    QFile file("log.txt");
    if(file.size()>204800)
    {
        file.open(QIODevice::ReadOnly);
        QString s=QString::fromLocal8Bit(file.readAll());
        s=s.right(51200);
        QFile::remove("log.txt");
        QFile f("log.txt");
        f.open(QIODevice::WriteOnly);
        f.write(s.toLocal8Bit());
        f.close();
    }
    file.close();
    //删除error.txt文件
    if(QFile::exists("error.txt"))
    {
        QFile file("error.txt");
        if(file.size()>10485760)
            QFile::remove("error.txt");
        file.close();
    }

    connect(&aniu_login,SIGNAL(is_aniu(bool)),this,SLOT(is_aniu(bool)));
    aniu_login.need_aniu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    log=log+"log更新时间:"+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd\r\n");
    QFile file("log.txt");
    file.open(QIODevice::Append);
    file.write(log.toLocal8Bit());
    file.close();
    emit exit_queqiao();
}

void MainWindow::on_alimama_login_flag(QString m_user_name,QString m_alimama_tb_token,QList<QNetworkCookie> m_cookie_list)
{
    this->m_alimama_tb_token=m_alimama_tb_token;
    this->m_cookie_list=m_cookie_list;
    this->m_user_name=m_user_name;

    if(this->m_alimama_tb_token.size()>0&&this->m_cookie_list.size()>0&&this->m_user_name.size()>0)
    {
        qDebug()<<"主窗口登录成功";
        alimama_network_manager=new QNetworkAccessManager(this);
        QNetworkCookieJar *cookieJar=new QNetworkCookieJar();
        cookieJar->setCookiesFromUrl(m_cookie_list,QUrl("http://pub.alimama.com/myunion.htm"));
        alimama_network_manager->setCookieJar(cookieJar);

        is_login=true;
        ui->login->setText("切换账号");
        ui->login->setToolTip("点击切换账号或重新登录");
        ui->user_name_s->setText("账号：");
        ui->user_name->setText(m_user_name+"  登陆成功");

        AutoClose *msgbox=new AutoClose("登陆成功",m_user_name+QString(" 登陆成功"),3000);
        msgbox->show();
        //QDateTime current_date_time=QDateTime::currentDateTime();
       // AutoClose a("当前系统时间",current_date_time.toString(),10000);
        //a.show();
    }
    else
    {
        QMessageBox(QMessageBox::NoIcon,"错误","未获取到登录相关信息，登录未成功！").exec();
        emit log_changed("登录参数传递失败");
    }
    this->show();
}

void MainWindow::pid_updated(QList<Pid> pid_list,QString num_id)
{
    qDebug()<<"主窗口获取到了： "<<pid_list.size()<<" 个推广位";
    this->pid_list=pid_list;
}

void MainWindow::on_pid_update_clicked()
{
    if(is_login)
    {
        emit pid_need_update();
    }
    else
    {
        emit alimama_need_login();
    }
}

void MainWindow::on_begin_time_select_clicked()
{
    calendar->hide();
    this->calendar=new QCalendarWidget(this);
    calendar->setToolTip("根据日历选择适当的活动开始时间");
    QRect rect=ui->begin_time_select->geometry();
    calendar->setGeometry(rect.x(),rect.y()+40,300,300);
    QEventLoop loop;
    QObject::connect(calendar,SIGNAL(clicked(QDate)),&loop,SLOT(quit()));
    QObject::connect(calendar,SIGNAL(clicked(QDate)),this,SLOT(on_begin_time_changed(QDate)));
    calendar->show();
    loop.exec();
}

void MainWindow::on_begin_time_changed(QDate date)
{
    ui->begin_time->setText(date.toString("yyyy-MM-dd"));
    calendar->hide();
}

void MainWindow::on_sort_clicked()
{
    if(ui->sort->isChecked())
    {
        ui->sort->setText("降序");
    }
    else
    {
        ui->sort->setText("升序");
    }
}

void MainWindow::on_repeat_clicked()
{
    if(ui->repeat->isChecked())
    {
        ui->repeat->setText("去重");
    }
    else
    {
        ui->repeat->setText("不去重");
    }
}

void MainWindow::on_login_clicked()
{
    emit alimama_need_login();

    if(is_login&&ui->login->text()=="切换账号")
    {
        ui->login->setText("登录");
        ui->login->setToolTip("点击登录");
        ui->user_name_s->setText("未登录");
        ui->user_name->clear();
        is_login=false;
    }
}

void MainWindow::on_start_clicked()
{
    QString s;
    s="select itemId,item.eventId,sellerId,itemTitle,picUrl,commissionRate,isSoldOut,";
    s+="disCountPrice,auctionPrice,discountRate,soldQuantity,mall,startTime,endTime,";
    s+="shareRate,alipayNum,cvr,avgCommission,tkLevel,eventTitle,promotionTypeStr";
    if(ui->repeat->isChecked())
    {
        s+=",max(commissionRate*discountPrice*shareRate)";
    }
    s+=" from item,activaty";
    s+=" where activaty.eventId=item.eventId ";
    QString l("正在搜索：");//log
    QString key_word(ui->key_word->text());
    if(key_word.size()>0)
    {
        key_word=QString(" and itemTitle like '%%")+key_word+"%%' ";
        s+=key_word;
        l=l+"关键字为\""+ui->key_word->text()+"\" ";
    }
    QString itemId(ui->id->text());
    if(itemId.size()>6)
    {
        itemId=QString(" and itemId='")+itemId+"' ";
        s+=itemId;
        l=l+"商品id为:"+ui->id->text()+" ";
    }
    QString price_h(ui->price_high->text());
    QString price_l(ui->price_low->text());
    if(is_number(price_h)&&is_number(price_l)&&price_h.size()>0&&price_l.size()>0)
    {
        if(price_h.toDouble()<price_l.toDouble())
            emit log_changed("价格区间不对，高价低于低价，请注意！！！\r\n");
        else
        {
            s=s+QString(" and discountPrice>=")+price_l+" and discountPrice<="+price_h+" ";
        }
        l=l+"价格大于："+ui->price_low->text()+"元，小于："+ui->price_high->text()+"元 ";
    }
    QString com_h(ui->com_rate_high->text());
    QString com_l(ui->com_rate_low->text());
    if(is_number(com_h)&&is_number(com_l)&&com_h.size()>0&&com_l.size()>0)
    {
        if(com_h.toInt()<com_l.toInt())
            emit log_changed("佣金区间不对，佣金上限小于下限，请注意!!!\r\n");
        else
        {
            s=s+QString(" and commissionRate>=(")+com_l+"*100.0)and commissionRate<=("+com_h+"*100.0) ";
        }
        l=l+"佣金比例大于："+ui->com_rate_low->text()+"%，小于："+ui->com_rate_high->text()+"% ";
    }
    QString eventId(ui->event_id->text());
    if(eventId.size()>1)
    {
        s=s+QString(" and eventId=")+eventId+" ";
        l=l+"活动id为："+ui->event_id->text()+" ";
    }
    if(ui->begin_time->text().size()>5)
    {
        QDate date=QDate::fromString(ui->begin_time->text(),"yyyy-MM-dd");
        s=s+" and startTime>="+date.toString("yyyyMMdd")+" ";
        l=l+"活动开始时间大于："+QString::number(date.year())+"年"+QString::number(date.month())+"月"+QString::number(date.day())+"日 ";
    }
    QString share(ui->share_rate->currentText());
    if(share=="100%")
    {
        s=s+" and shareRate>=100.0 ";
    }
    else if(share=="95%")
    {
        s=s+" and shareRate>=95.0 ";
    }
    else if(share=="90%")
    {
        s=s+" and shareRate>=90.0 ";
    }
    else if(share=="80%")
    {
        s=s+" and shareRate>=80.0 ";
    }
    QString mall(ui->type->currentText());
    if(mall=="天猫")
    {
        s=s+" and mall=1 ";
    }
    else if(mall=="淘宝")
    {
        s=s+" and mall=0 ";
    }
    if(ui->repeat->isChecked())
    {
        s+="group by itemId";
    }
    QString sort_m(ui->sort_method->currentText());
    if(sort_m=="按现价")
    {
        s=s+" order by discountPrice ";
    }
    else if(sort_m=="按佣金比例")
    {
        s=s+" order by commissionRate ";
    }
    else if(sort_m=="按佣金")
    {
        s=s+" order by (discountPrice*commissionRate*shareRate) ";
    }
    else if(sort_m=="按销量")
    {
        s=s+" order by soldQuantity ";
    }
    else
    {
        s=s+" order by startTime ";
    }
    if(ui->sort->isChecked())
    {
        s=s+" desc";
    }
    else
        s=s+" asc ";
    s+=" limit 0,150000";
    l+="的商品\r\n请稍候...\r\n";
    emit log_changed(l);
    emit search_sql(s);
    qDebug()<<s;
}

void MainWindow::on_log_changed(QString s)
{
    if(log.size()>10000)
    {
        QFile file("log.txt");
        file.open(QFileDevice::Append);
        file.write(log.left(8000).toLocal8Bit());
        file.close();
        log=log.right(log.size()-8000);
    }
    log+=s;
    ui->log->setPlainText(log);
    QTextCursor cursor = ui->log->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->log->setTextCursor(cursor);
}

void MainWindow::on_update_clicked()
{
    if(is_login)
    {
        emit update_sql();
    }
    else
    {
        emit log_changed("未登录,请先登录\r\n");
        emit alimama_need_login();
    }
}

void MainWindow::on_search_complete(QSqlQuery query)
{
    qDebug()<<"查询完成";
    table_list.clear();
    while(query.next())
    {
        Table temp;
        temp.itemId=query.value(0).toString();
        temp.eventId=query.value(1).toInt();
        temp.sellerId=query.value(2).toString();
        temp.itemTitle=query.value(3).toString();
        temp.picUrl=query.value(4).toString();
        temp.commissionRate=query.value(5).toInt();
        temp.isSoldOut=query.value(6).toInt();
        temp.discountPrice=query.value(7).toDouble();
        temp.auctionPrice=query.value(8).toDouble();
        temp.discountRate=query.value(9).toDouble();
        temp.soldQuantity=query.value(10).toInt();
        temp.mall=query.value(11).toInt();
        temp.startTime=query.value(12).toInt();
        temp.endTime=query.value(13).toInt();
        temp.shareRate=query.value(14).toDouble();
        temp.alipayNum=query.value(15).toInt();
        temp.cvr=query.value(16).toDouble();
        temp.avgCommission=query.value(17).toDouble();
        temp.tkLevel=query.value(18).toInt();
        temp.eventTitle=query.value(19).toString();
        temp.promotionTypeStr=query.value(20).toString();

        table_list.push_back(temp);
    }
    table_changed();
    emit log_changed("查询成功\r\n");
}

void MainWindow::table_changed()
{
    if(table_list.size()<=0)
    {
        emit log_changed("未找到符合条件的商品\r\n");
        ui->table->clearContents();
        ui->table->setRowCount(1);
    }
    else
    {
        if(table_list.size()>=150000)
            emit log_changed("搜索结果过多，显示前15万条记录,正在显示...\r\n");
        else
            emit log_changed(QString("搜索到商品")+QString::number(table_list.size())+"个,正在显示...\r\n");
        ui->table->setRowCount(table_list.size());
        for(int i=0;i<table_list.size();++i)
        {
            ui->table->setItem(i, 0, new QTableWidgetItem(table_list[i].eventTitle));
            ui->table->setItem(i, 1, new QTableWidgetItem(table_list[i].itemTitle));
            ui->table->setItem(i, 2, new QTableWidgetItem(QString::number(table_list[i].auctionPrice)));
            ui->table->setItem(i, 3, new QTableWidgetItem(QString::number(table_list[i].discountPrice)));
            ui->table->setItem(i, 4, new QTableWidgetItem(QString::number(table_list[i].commissionRate/100)+"%"));
            ui->table->setItem(i, 5, new QTableWidgetItem(QString::number((double)(table_list[i].discountPrice*table_list[i].commissionRate*table_list[i].shareRate/1000000.0),'f',2)+" 元"));
            ui->table->setItem(i, 6, new QTableWidgetItem(QString::number(table_list[i].soldQuantity)));
            ui->table->setItem(i, 7, new QTableWidgetItem(QString("查看详情")));
            ui->table->setItem(i, 8, new QTableWidgetItem(QDate::fromString(QString::number(table_list[i].startTime),("yyyyMMdd")).toString("yyyy-MM-dd")+"到"+QDate::fromString(QString::number(table_list[i].endTime),"yyyyMMdd").toString("yyyy-MM-dd")));
            ui->table->setItem(i, 9, new QTableWidgetItem(QString::number(get_days(table_list[i].startTime))+"天"));
            ui->table->setItem(i, 10, new QTableWidgetItem(table_list[i].mall==1?QString("天猫"):QString("淘宝")));
            ui->table->setItem(i, 11, new QTableWidgetItem(QString::number(table_list[i].shareRate)+" %"));
        }
    }
}

int MainWindow::get_days(const int& s)
{
    QDate start=QDate::fromString(QString::number(s),"yyyyMMdd");
    QDate end=QDate::currentDate();
    if(end>=start)
    {
        return (end.year()-start.year())*365+(end.month()-start.month())*30+(end.day()-start.day());
    }
    else
    {
        return -1;
    }
}

void MainWindow::on_table_clicked(const QModelIndex &index)
{
    int row=index.row();
    if(row<0||row>=table_list.size())
        ;
    else
    {
        QString h("<html><img style=\"-webkit-user-select: none; cursor: zoom-in;\" src=\"https:");
        h+=table_list[row].picUrl;
        h+=("\" width=\"184\" height=\"184\"><\html>");
        ui->picture->setHtml(h);
    }
}

void MainWindow::on_table_doubleClicked(const QModelIndex &index)
{
    int row=index.row();
    if(row<0||row>=table_list.size())
        ;
    else
    {
        emit need_imagin(QString("https:")+table_list[row].picUrl);
        emit need_detail(table_list[row]);
        emit log_changed(QString("正在查看商品\"")+table_list[row].itemTitle+"\"的详细信息...\r\n");
    }
}

void MainWindow::resizeEvent(QResizeEvent *resize)
{
    int width=ui->table->width();
    ui->table->setColumnWidth(0,(1.0/14.75)*width);
    ui->table->setColumnWidth(1,(2.0/14.75)*width);
    ui->table->setColumnWidth(2,(1.0/14.75)*width);
    ui->table->setColumnWidth(3,(1.0/14.75)*width);
    ui->table->setColumnWidth(4,(1.0/14.75)*width);
    ui->table->setColumnWidth(5,(1.0/14.75)*width);
    ui->table->setColumnWidth(6,(1.0/14.75)*width);
    ui->table->setColumnWidth(7,(1.0/14.75)*width);
    ui->table->setColumnWidth(8,(2.0/14.75)*width);
    ui->table->setColumnWidth(9,(1.0/14.75)*width);
    ui->table->setColumnWidth(10,(1.0/14.75)*width);
    ui->table->setColumnWidth(11,(1.0/14.75)*width);
}

bool MainWindow::is_number(QString s)
{
    for(auto i:s)
    {
        if(i>'9'||i<'0')
            return false;
    }
    return true;
}

void MainWindow::is_aniu(bool f)
{
    if(f)
    {
        this->show();

        QSettings s("user.ini",QSettings::IniFormat);
        QDate date=QDate::fromString(s.value("time").toString(),"yyyy-MM-dd");
        if(date<QDate::currentDate())
        {
            on_log_changed(QString("数据库有更新,请登录后更新数据库\r\n")+"上次更新时间:"+date.toString("yyyy-MM-dd\r\n"));
            AutoClose *msgbox=new AutoClose("提示","数据库有更新,请登录后更新数据库",3000);
            msgbox->show();
        }
    }
    else
        exit(0);
}

bool MainWindow::checkUpdate()
{
    QString udata(http_get("http://121.41.177.103/bridge/update/update.txt"));
    std::string udata_str=udata.toLocal8Bit().data();
    qDebug()<<"udata:"<<udata;
    std::regex reg("version:(.*)");
    std::smatch sm;
    if(std::regex_search(udata_str,sm,reg))
    {
        double newVer=atof(sm[1].str().c_str());
        if(newVer>version.toFloat())
        {
            std::ofstream fo("update.txt");
            if(!fo)
            {
                return false;
            }
            fo<<udata_str;
            fo.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

QByteArray MainWindow::http_get(const QString &url)
{
    QNetworkRequest alimama_network_request;
    alimama_network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=\"UTF-8\"");
    alimama_network_request.setUrl(QUrl(url));

    QNetworkAccessManager mgr;

    QEventLoop eventLoop;
    connect(&mgr,SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = mgr.get(alimama_network_request);
    eventLoop.exec();       //事件循环

    reply->deleteLater();
    disconnect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    return reply->readAll();
}
