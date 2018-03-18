#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QUrl>
#include <QtWebKitWidgets/qwebview.h>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QByteArray>
#include <QNetworkReply>
#include <QtNetwork>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QEventLoop>
#include <QVariant>
#include <string>

//std::mutex mutex;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_name(),
    m_tb_token(),
    m_seller_num_id(),
    m_search_name(),
    detail(),//详情，同步到ui->detail
    order(),//全部订单，同步到ui->order
    order_list(),
    detail_map(),
    cookie(),
    stop_flag(false),
    post_url("https://trade.taobao.com/trade/itemlist/list_sold_items.htm"),
    m_close_reason("未及时付款"),
    order_map()
{
    ui->setupUi(this);
    //connect(this,SIGNAL(post_complete(QString)),this,SLOT(translate_html_to_order(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_flag(QString name,QString tb_token,QString seller_num_id,QList<QNetworkCookie>cookielist)
{
    //同步数据
    m_name=name;
    m_tb_token=tb_token;
    m_seller_num_id=seller_num_id;
    this->cookie=cookielist;
    //登录成功，设置cookie

    ui->start->setFocus();
    ui->start->setDefault(true);
    ui->start->setShortcut(Qt::Key_Enter);
    ui->start->setShortcut(Qt::Key_Return);

    network_manager=new QNetworkAccessManager(this);
    QNetworkCookieJar *cookieJar=new QNetworkCookieJar();
    cookieJar->setCookiesFromUrl(cookie,QUrl("https://mai.taobao.com/seller_admin.htm"));
    network_manager->setCookieJar(cookieJar);

    connect(this,SIGNAL(order_changed()),this,SLOT(on_order_changed()));
    connect(this,SIGNAL(detail_changed()),this,SLOT(auto_scroll()));
    //connect(network_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(on_reply_finish(QNetworkReply*)));

    ui->comboBox->addItem("未及时付款");
    ui->comboBox->addItem("买家不想买");
    ui->comboBox->addItem("买家信息填写错误，重新拍");
    ui->comboBox->addItem("恶意买家/同行捣乱");
    ui->comboBox->addItem("缺货");
    ui->comboBox->addItem("同城见面交易");
    ui->comboBox->addItem("其他原因");
    ui->user_name->setText(name);
    this->show();//登录成功的话，隐藏登录窗口显示当前窗口
    //QMessageBox(QMessageBox::NoIcon,"登录成功","登陆成功，欢迎"+name).exec();
}

void MainWindow::on_start_clicked()
{
    qDebug()<<order_list.size();
    stop_flag=false;
    m_search_name=ui->search_name->text();
    detail=ui->detail->toPlainText();
    //detail_changed();
    if(detail.length()>10000)
    {
        detail=detail.right(2000);
    }
    order.clear();
    order_list.clear();
    detail_map.clear();
    order_map.clear();
    //ui->order->setPlainText(order);
    emit order_changed();

    get_order_list();
    if(order_list.size()>0)
    {
        order_list.clear();
        while(stop_flag==false)
        {
            get_order_list();
            //qDebug()<<"order_list.size"<<order_list.size();
            if(order_list.size()>0)
            {
                trade_close();
                order_list.clear();
            }
            else
            {
                detail+=QString("本次成功关闭交易 ")+QString::number(order_map.size())+QString(" 个\r\n\r\n");
                //ui->detail->setPlainText(detail);
                detail_changed();
                break;
            }
        }
    }
    else
    {
        //QMessageBox(QMessageBox::NoIcon,"未找到订单","未找到符合搜索条件 \""+m_search_name+" \"的未关闭交易的订单");
        detail+="未找到符合搜索条件 \""+m_search_name+"\" 的订单\r\n"+"可能是没有符合条件的订单或者搜索频率过高，如果是搜索频率过高，请到网页手动搜索并输验证码，再重试！\r\n\r\n";
        //ui->detail->setPlainText(detail);
        detail_changed();
    }
}

int MainWindow::translate_html_to_order(QString html)
{
    std::string strHtml=html.toStdString();
    for (auto&i : strHtml)
        if ('\n' == i)
            i = ' ';
    /*
    QFile file("get.html");
    file.open(QFile::Append);
    file.write(html.toLatin1());
    file.close();
    */
    std::string m_order_begin("<tbody id=\"order");
    std::string m_order_end("</tbody>");
    //订单查找的位置
    int m_order_pos_begin = -1;
    int m_order_pos_end = 0;
    while ((m_order_pos_begin = strHtml.find(m_order_begin, m_order_pos_end)) != std::string::npos)
    {
        //从末尾的位置开始查找
        //确定能找到订单开始的部分，才找他的结束位置
        if ((m_order_pos_end = strHtml.find(m_order_end, m_order_pos_begin)) != std::string::npos)
        {
            std::string m_order(strHtml.begin() + m_order_pos_begin, strHtml.begin() + m_order_pos_end);
            order_info temp_order;
            std::string number(m_order.begin() + 16, m_order.begin() + 32);
            temp_order.m_number = QString (number.c_str());
            //订单号获取成功
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //关闭链接查找部分的处理
            //找到订单号之后，要找关闭交易的链接，
            std::string url_begin("<div class=\"trade-actions\">");
            std::string url_end("</div>");
            //关闭交易链接查找的开始位置和结束位置
            int url_pos_begin = m_order.find(url_begin);
            //记录真正关闭交易的链接地址
            std::string url = "";
            if (std::string::npos != url_pos_begin)
            {
                //外层的交易状态的位置，里边包含关闭交易的地址，先获取这部分的代码，再在里边找要的地址
                int url_pos_end = std::string::npos;
                if ((url_pos_end = m_order.find(url_end, url_pos_begin)) != std::string::npos)
                {
                    //链接的初始位置和结束位置
                    std::string url_be("href=\"//");
                    std::string url_en("\"");
                    //这是这部分的strHtml代码，里边有关闭交易的地址
                    std::string url_frame(m_order.begin() + url_pos_begin, m_order.begin() + url_pos_end);
                    int url_begin = url_frame.find(url_be);
                    if (std::string::npos != url_begin)
                    {
                        int url_end = std::string::npos;
                        if ((url_end = url_frame.find(url_en, url_begin + 9)) != std::string::npos)
                        {
                            url = std::string(url_frame.begin() + url_begin + 8, url_frame.begin() + url_end);
                        }
                    }
                }
            }
            //关闭链接查找结束
            temp_order.m_url = QString(url.c_str());
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //查找买家名字的部分
            //一个是标签的开始，一个是真正买家名字开始之前的地方，也是标签结束的位置，最后一个是买家名字查找结束的位置
            std::string m_name_frame_begin("<a class=\"nickname\" href=\"//member1");
            std::string m_name_begin("\">");
            std::string m_name_end("</a>");
            int m_name_frame_pos_begin = m_order.find(m_name_frame_begin);
            std::string name(" ");
            if (std::string::npos != m_name_frame_pos_begin)
            {
                int m_name_pos_begin = std::string::npos;
                if ((m_name_pos_begin = m_order.find(m_name_begin, m_name_frame_pos_begin)) != std::string::npos)
                {
                    int m_name_pos_end = std::string::npos;
                    if ((m_name_pos_end = m_order.find(m_name_end, m_name_pos_begin)) != std::string::npos)
                    {
                        name = std::string(m_order.begin() + m_name_pos_begin + 2, m_order.begin() + m_name_pos_end);
                    }
                }
            }
            temp_order.m_name = QString(name.c_str());
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //这里要获取订单生成的时间
            std::string m_time("");
            std::string m_time_begin("<span class=\"deal-time\">");
            std::string m_time_end("</span>");
            int m_time_pos_begin = std::string::npos;
            if ((m_time_pos_begin = m_order.find(m_time_begin)))
            {
                int m_time_pos_end = std::string::npos;
                if ((m_time_pos_end = m_order.find(m_time_end, m_time_pos_begin)) != std::string::npos)
                {
                    m_time = std::string(m_order.begin() + m_time_pos_begin + 40, m_order.begin() + m_time_pos_end);
                }
            }
            temp_order.m_time = QString(m_time.c_str());
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            order_list.push_back(temp_order);
        }
        else
            break;
    }
    //剔除可能不对的订单
    //qDebug()<<"before order size"<<order_list.size();
    for (auto i = order_list.begin(); i != order_list.end();)
    {
        if (i->m_url.length() < 10)
            i =order_list.erase(i);
        else
        {
            //qDebug()<<i->m_name<<i->m_number<<i->m_time<<i->m_url;
            ++i;
        }
    }
    for(auto i:order_list)
    {
        auto it=order_map.find(i.m_number);
        if(order_map.end()==it)
        {
            QString o;
            o+="订单编号: "+i.m_number+" 卖家昵称: "+i.m_name+" 订单生成时间: "+i.m_time/*+" 关闭地址: "+i.m_url*/+"\r\n";
            order+=o;
            order_map.insert(i.m_number,o);
            //ui->order->setPlainText(order);
            emit order_changed();
        }
    }
    //qDebug()<<"after order size"<<order_list.size();
    //qDebug()<<order_map.size();
    return order_list.size();
}

void MainWindow::on_stop_clicked()
{
    stop_flag=true;
}

void MainWindow::get_order_list()//返回得到的订单数
{
    //获取输入框文字，编码
    m_search_name=ui->search_name->text();
    QTextCodec * codec = QTextCodec::codecForName("UTF-8");//这里换一下就好了
    QByteArray byteArray = codec->fromUnicode(m_search_name);
    m_search_name=QString(byteArray);
    //QByteArray byteArrayPercentEncoded = byteArray.toPercentEncoding();
    //QString search_name_encode(byteArrayPercentEncoded);
    //ui->order->setText(search_name_encode);
    //QMessageBox(QMessageBox::NoIcon,"",m_search_name).exec();
    //组合要发送的数据
    QByteArray post_data;
    post_data.append("event_submit_do_query=1&closeorder_flag=1&isArchive=false&isArchiveDefault=0&user_Type=1&pageNum=0&order=desc&order_Type=orderList&");
    post_data.append("isQueryMore=false&select_shop_name=&isOwnOfficialShop=false&sellerNumID=");
    post_data.append(m_seller_num_id);
    post_data.append("&from_flag=&timeStamp=&sessionID=&authType=1&auctionTitle=");
    post_data.append(m_search_name);
    post_data.append("&bizOrderTimeBegin=&bizOrderHourBegin=00&bizOrderMinBegin=00&bizOrderTimeEnd=&bizOrderHourEnd=00&bizOrderMinEnd=00&buyerNick=&");
    post_data.append("auctionStatus=NOT_PAID&commentStatus=ALL&bizOrderId=&logisticsService=ALL&tradeDissension=ALL&auctionType=0&queryBizType=&shopName=All&action=itemlist/QueryAction");

    QNetworkRequest network_request;
    network_request.setUrl(QUrl(post_url));
    network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=\"UTF-8\"");
    network_request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

    QByteArray responseData;
    QEventLoop eventLoop;
    connect(network_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = network_manager->post(network_request, post_data);
    eventLoop.exec();       //事件循环
    responseData = reply->readAll();
    //qDebug()<<responseData.size();
    /*QFile file("reply.html");
    file.open(QIODevice::Append);
    file.write(responseData);
    file.close();*/

    translate_html_to_order(QString(responseData));
    //http_post(post_data);
    //network_manager->post(network_request,post_data);
    reply->deleteLater();
}

void MainWindow::trade_close()
{
    for(auto i:order_list)
    {
        if(stop_flag==true)
        {
            detail+=QString("本次成功关闭交易 ")+QString::number(order_map.size())+QString(" 个\r\n\r\n");
            //ui->order->setPlainText(detail);
            emit detail_changed();
            break;
        }
        else
        {
            QString close_reason=ui->comboBox->currentText();
            //detail+=close_reason;
            QTextCodec * codec = QTextCodec::codecForName("GB2312");//这里换一下就好了
            QByteArray byteArray = codec->fromUnicode(close_reason);
            //close_reason=QString(byteArray);
            QByteArray byteArrayPercentEncoded = byteArray.toPercentEncoding();
            QString close_reason_encode(byteArrayPercentEncoded);
            //QString close_reason_GBK(byteArray);
            //detail+=close_reason_GBK;

            QByteArray post_data;
            post_data.append("_tb_token_=");
            post_data.append(m_tb_token);
            post_data.append("&bizType=200&bizOrderId=");
            post_data.append(i.m_number);
            post_data.append("&action=cancelOrderAction.htm&event_submit_do_cancel=1&J_CloseReason=");
            post_data.append(close_reason_encode);

            //detail+=QString(post_data);

            QNetworkRequest network_request;
            network_request.setUrl(QUrl(post_url));//这里其实只需要那个url就行了，没必要用关闭交易的url
            network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
            network_request.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

            QByteArray responseData;
            QEventLoop eventLoop;
            connect(network_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
            QNetworkReply *reply = network_manager->post(network_request,post_data);;
            eventLoop.exec();       //事件循环
            responseData = reply->readAll();
           /* qDebug()<<"close_reply"<<responseData.size();
            QFile file("close_reply.html");
            file.open(QIODevice::Append);
            file.write(responseData);
            file.close();*/
            reply->deleteLater();

            auto it=detail_map.find(i.m_number);
            if(it==detail_map.end())
            {
                QString d;
                d+="订单: "+i.m_number+" 已关闭"+" 关闭原因: "+close_reason+"\r\n";
                detail+=d;
                //ui->detail->setPlainText(detail);
                detail_changed();
                detail_map.insert(i.m_number,d);
            }
        }
    }
    order_list.clear();
}

void MainWindow::on_pushButton_clicked()
{
    detail.clear();
    order.clear();
    //ui->detail->setPlainText(detail);
    detail_changed();
    //ui->order->setPlainText(order);
    emit order_changed();
}

void MainWindow::auto_scroll()
{
    ui->detail->setPlainText(detail);
    QTextCursor cursor = ui->detail->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->detail->setTextCursor(cursor);
}

void MainWindow::on_order_changed()
{
    ui->order->setPlainText(order);
    QTextCursor cursor = ui->order->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->order->setTextCursor(cursor);
}

/*void MainWindow::on_reply_finish(QNetworkReply *reply)
{
    int http_status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"reply finish"<<http_status;
    if(http_status==302||http_status==301)
    {
        qDebug()<<"链接被重定向";
        //qDebug()<<"Location"<<reply->rawHeader("Location");
        //network_manager->post;
    }
    else
    {
       // qDebug()<<"无重定向";
        //QString content(reply->readAll());
        if(reply->error()==QNetworkReply::NoError)
        {
            qDebug()<<"无错误";
            //emit post_complete(QString(reply->readAll()));
            QByteArray array=reply->readAll();
           if(array.length()>100)
            {
                translate_html_to_order(QString(array));
                //mutex.unlock();
            }

            for(auto i:reply->rawHeaderPairs())
            {
                qDebug()<<i.first<<" "<<i.second;
            }
            ui->textBrowser->setText(content);
            qDebug()<<"ah"<<content;

            QFile file("taobao.html");
            file.open(QIODevice::Append);
            file.write(array);
            file.close();

            NetworkCookie*cookieJar;
            cookieJar=(NetworkCookie*)network_manager->cookieJar();
            QList<QNetworkCookie>cooklist=cookieJar->getCookies();
            qDebug()<<"cookie";
            QString cookie;
            for(auto i:cooklist)
            {
                cookie+=i.name()+"="+i.value()+";";
            }
            qDebug()<<cookie;

        }
        else
            qDebug()<<"error"<<http_status;
    }
    return NULL;
    reply->deleteLater();
}

void MainWindow::http_post(QByteArray post_data)
{
    QVariant var;
    var.setValue(cookie);
    QString str;
    for(auto i:cookie)
    {
        str+=i.name()+"="+i.value()+";";
        qDebug()<<i.name()<<" "<<i.value();
    }

    //初始化请求
    //QNetworkRequest network_request;

    qDebug()<<post_data;
    network_request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
    network_request.setRawHeader(QNetworkRequest::ContentLengthHeader,post_data.length());
    network_request.setHeader(QNetworkRequest::CookieHeader,var);
    network_request.setRawHeader("Set-Cookie",str.toStdString().c_str());

    qDebug()<<"post begin";

    NetworkCookie*cookieJ;
    cookieJ=(NetworkCookie*)network_manager->cookieJar();
    QList<QNetworkCookie>ql=cookieJ->getCookies();
    qDebug()<<endl<<"network cookies";
    for(auto i:ql)
    {
        qDebug()<<i.name()<<i.value();
    }


    network_manager->post(network_request,post_data);
    if(reply!=NULL)
    {
        QFile file("reply.html");
        file.open(QFile::Append);
        QByteArray array(reply->readAll());
        file.write(array);
        file.close();
        reply->deleteLater();
    }
}
*/
