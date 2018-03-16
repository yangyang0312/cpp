#include "json_net.h"


Json_Net::Json_Net():
    m_cookie_list(),
    m_user_name(),
    m_user_num_id(),
    m_alimama_tb_token(),
    response(),
    default_pid(),
    pid_list(),
    login_flag(false),
    insert_s()
{
    this->alimama_network_manager=new QNetworkAccessManager(this);
    connect(this,SIGNAL(pid_need_update()),this,SLOT(on_pid_need_update()));
}

Json_Net::~Json_Net()
{
    delete this->alimama_network_manager;
}

void Json_Net::on_alimama_login_flag(QString m_user_name,QString m_alimama_tb_token,QList<QNetworkCookie> m_cookie_list)
{
    //qDebug()<<"登录信号进路Json_Net";
    this->m_alimama_tb_token=m_alimama_tb_token;
    this->m_cookie_list=m_cookie_list;
    this->m_user_name=m_user_name;
    if(this->m_alimama_tb_token.size()>0&&this->m_cookie_list.size()>0&&this->m_user_name.size()>0)
    {
        //qDebug()<<"json_net登录成功";
        //this->alimama_network_manager=new QNetworkAccessManager(this);
        QNetworkCookieJar *cookieJar=new QNetworkCookieJar();
        cookieJar->setCookiesFromUrl(m_cookie_list,QUrl("http://pub.alimama.com/myunion.htm"));
        this->alimama_network_manager->setCookieJar(cookieJar);

        emit pid_need_update();
        //QDateTime current_date_time=QDateTime::currentDateTime();
        //QMessageBox(QMessageBox::NoIcon,"当前系统时间",current_date_time.toString());
    }
    else
    {
        //QMessageBox(QMessageBox::NoIcon,"错误","网络部分未获取到登录相关信息，登录未成功！").exec();
        emit log_changed("网络部分登录参数未传递成功");
    }
}

bool Json_Net::http_post(const QString &url,const QByteArray &data,QByteArray&response)
{
    QNetworkRequest alimama_network_request;
    alimama_network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=\"UTF-8\"");
    alimama_network_request.setUrl(QUrl(url));

    QEventLoop eventLoop;
    connect(alimama_network_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = alimama_network_manager->post(alimama_network_request,data);
    eventLoop.exec();       //事件循环
    response = reply->readAll();

    reply->deleteLater();
    disconnect(alimama_network_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    return true;
}

bool Json_Net::http_get(const QString &url,QByteArray&response)
{
    QNetworkRequest alimama_network_request;
    alimama_network_request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=\"UTF-8\"");
    alimama_network_request.setUrl(QUrl(url));

    QEventLoop eventLoop;
    connect(alimama_network_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = alimama_network_manager->get(alimama_network_request);
    eventLoop.exec();       //事件循环
    response = reply->readAll();

    reply->deleteLater();
    disconnect(alimama_network_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    return true;
}

bool Json_Net::json_ok(Json::Value &root,const QByteArray &data)
{
    Json::Reader reader;
    if(reader.parse(data.toStdString(),root))//no error
    {
        if(root["ok"].asBool()!=true||root["info"]["ok"].asBool()!=true)
        {
            emit log_changed(QString("json not ok:")+QString(root["info"]["message"].asString().c_str())+("\r\n"));
            return false;
        }
        else
        {
            qDebug()<<"json ok";
            return true;
        }
    }
    return false;
}

bool Json_Net::json_to_activaty(Json::Value &root, QList<Activaty> &activaty_list,bool&has_next_page,int&total_page)
{
    has_next_page=root["data"]["hasNext"].asBool();
    total_page=root["data"]["totalPages"].asInt();
    if(!root["data"]["result"].isNull()&&root["data"]["result"].isArray())
    {
        Json::Value data(root["data"]["result"]);
        for(auto item:data)
        {
            Activaty temp;
            temp.eventId=item["eventId"].asInt();
            temp.previewUrl=QString(item["previewUrl"].asString().c_str());
            temp.startTime=date_to_int(QString(item["startTime"].asString().c_str()));
            temp.endTime=date_to_int(QString(item["endTime"].asString().c_str()));
            temp.shareRate=QString(item["shareRate"].asString().c_str()).toDouble();
            temp.eventStatus=item["eventStatus"].asInt();
            temp.eventStatusStr=QString(item["eventStatusStr"].asString().c_str());
            temp.alipayNum=item["alipayNum"].asInt();
            temp.cvr=QString(item["cvr"].asString().c_str()).toInt();
            temp.avgCommission=QString(item["avgCommission"].asString().c_str()).toInt();
            temp.tkLevel=item["tkLevel"].asInt();
            temp.eventTitle=QString(item["eventTitle"].asString().c_str()).replace("'","''");
            temp.comments=QString(item["comments"].asString().c_str()).replace("'","''");
            temp.platformType=item["platformType"].asInt();
            temp.platformTypeStr=QString(item["platformTypeStr"].asString().c_str());
            temp.promotionType=item["promotionType"].asInt();
            temp.promotionTypeStr=QString(item["promotionTypeStr"].asString().c_str());
            temp.auditEndTime=QString(item["auditEndTime"].asString().c_str());
            temp.createFinish=item["createFinish"].asInt();
            temp.canOperate=item["canOperate"].asInt();
            temp.canEditFloor=item["canEditFloor"].asInt();
            temp.highQualityType=item["highQualityType"].asInt();

            activaty_list.push_back(temp);
        }
        return true;
    }
    else
    {
        emit log_changed("json result error\r\n");
    }
    return false;
}

bool Json_Net::insert_activaty(const QList<Activaty> &ac_list)
{
    if(ac_list.size()<=0)
        return true;
    QString s("insert into activaty values ");
    for(auto it:ac_list)
    {
        s+="(";
        s=s+QString::number(it.eventId)+(",'")+it.previewUrl+("',");
        s=s+QString::number(it.startTime)+(",")+QString::number(it.endTime)+(",");
        s=s+QString::number(it.shareRate)+(",")+QString::number(it.eventStatus)+(",'");
        s=s+it.eventStatusStr+("',")+QString::number(it.alipayNum)+(",");
        s=s+QString::number(it.cvr)+(",")+QString::number(it.avgCommission)+(",");
        s=s+QString::number(it.tkLevel)+(",'")+it.eventTitle+("','");
        s=s+it.comments+("',")+QString::number(it.platformType)+(",'");
        s=s+it.platformTypeStr+("',")+QString::number(it.promotionType)+(",'");
        s=s+it.promotionTypeStr+("','")+it.auditEndTime+("',");
        s=s+QString::number(it.createFinish)+(",")+QString::number(it.canOperate)+(",");
        s=s+QString::number(it.canEditFloor)+(",")+QString::number(it.highQualityType);
        s+=("),");
    }
    s[s.size()-1]='\0';
    emit sql_insert(s);
    insert_item(ac_list);
    return true;
}

bool Json_Net::activaty_get(const int &page,QList<Activaty>&activaty_list,const int &page_size,bool&has_next_page,int &total_page)
{
    QString url("http://pub.alimama.com/event/squareList.json?toPage=");
    url+=QString::number(page);
    url+="&eventStatus=5&orderType=3&perPageSize=";
    url+=QString::number(page_size);
    url+="&highQuality=-1&key=&platformType=-1&catId=-1&commissionRangeType=-1&promotionType=-1&_tb_token_=";
    url+=this->m_alimama_tb_token;
    url+="&_input_charset=utf-8";

    http_get(url,response);

    Json::Value root;
    bool jsonok=json_ok(root,response);
    if(!root.isNull()&&jsonok==true)
    {
        json_to_activaty(root,activaty_list,has_next_page,total_page);
        if(!activaty_list.empty())
        {
            return true;
        }
        else
            emit log_changed("没有解析到活动\r\n");
    }
    return false;
}

bool Json_Net::item_get(const int &eventId,const QString&pid,QList<Item>&item_list,const int &page,const int&page_size)
{
    QString url("http://temai.taobao.com/event/items.json?toPage=");
    url+=QString::number(page);
    url+=("&perPageSize=");
    url+=QString::number(page_size);
    url+=("&catId=&tagId=&pid=");
    url+=pid;
    url+=("&unid=&platformType=1&isPreview=0&id=");
    url+=QString::number(eventId);

    http_get(url,response);

    Json::Value root;
    bool jsonok=json_ok(root,response);
    bool has_next_page=false;
    if(!root.isNull()&&jsonok==true)
    {
        json_to_item(eventId,root,item_list,has_next_page);
        if(!item_list.empty())
        {
            return true;
        }
        else
            emit log_changed(QString::number(eventId)+"没有解析到商品\r\n");
    }
    return false;
}
bool Json_Net::item_get_insert(const int &eventId,const QString&pid,const int &page,const int&page_size)
{
    QString url("http://temai.taobao.com/event/items.json?toPage=");
    url+=QString::number(page);
    url+=("&perPageSize=");
    url+=QString::number(page_size);
    url+=("&catId=&tagId=&pid=");
    url+=pid;
    url+=("&unid=&platformType=1&isPreview=0&id=");
    url+=QString::number(eventId);

    if(!http_get(url,response))
    {
        qDebug()<<"http_get false";
        return false;
    }

    Json::Value root;
    bool jsonok=json_ok(root,response);
    bool has_next_page=false;
    if(!root.isNull()&&jsonok==true)
    {
        if(json_to_item_insert(eventId,root,has_next_page))
        {
            qDebug()<<"活动："<<eventId<<"获取成功";
            return true;
        }
    }
    qDebug()<<"item_get_insert false";
    return false;
}

bool Json_Net::json_to_item(const int &eventId,Json::Value &root, QList<Item> &item_list, bool &has_next_page)
{
    has_next_page=root["hasNext"].asBool();
    if(!root["data"]["result"].isNull()&&root["data"]["result"].isArray())
    {
        Json::Value data(root["data"]["result"]);
        for(auto item:data)
        {
            Item temp;
            temp.itemId=QString::number((long long)(item["itemId"].asDouble()));
            temp.eventId=eventId;
            temp.sellerId=QString::number((long long)(item["sellerId"].asDouble()));
            //替换单引号，防止出错
            temp.itemTitle=QString(item["itemTitle"].asString().c_str());
            temp.picUrl=QString(item["picUrl"].asString().c_str());
            temp.tag=item["tag"].asInt();
            //链接地址不要了
            temp.href=QString("");
            temp.commissionRate=item["commissionRate"].asInt();
            temp.isSoldOut=item["isSoldOut"].asInt();
            temp.discountPrice=QString(item["discountPrice"].asString().c_str()).toDouble();
            temp.auctionPrice=QString(item["auctionPrice"].asString().c_str()).toDouble();
            temp.discountRate=QString(item["discountRate"].asString().c_str()).toDouble();
            temp.soldQuantity=item["soldQuantity"].asInt();
            temp.mall=item["mall"].asInt();
            item_list.push_back(temp);
        }
        return true;
    }
    else
    {
        emit log_changed("item json result error\r\n");
    }
    return false;
}

bool Json_Net::json_to_item_insert(const int &eventId,Json::Value &root, bool &has_next_page)
{
    has_next_page=root["hasNext"].asBool();
    if(!root["data"]["result"].isNull()&&root["data"]["result"].isArray())
    {
        int i=0;
        QString temp_s;
        Json::Value data(root["data"]["result"]);
        for(auto item:data)
        {
            temp_s+="('";
            temp_s+=QString::number((long long)(item["itemId"].asDouble()))+"',";
            temp_s+=QString::number(eventId)+",'";
            temp_s+=QString::number((long long)(item["sellerId"].asDouble()))+"','";
            //替换单引号，防止出错
            temp_s+=QString(item["itemTitle"].asString().c_str()).replace("'","''")+"','";
            temp_s+=QString(item["picUrl"].asString().c_str())+"',";
            temp_s+=QString::number(item["tag"].asInt())+",";
            //链接地址不要了
            temp_s+=QString::number(item["commissionRate"].asInt())+",";
            temp_s+=QString::number(item["isSoldOut"].asInt())+",";
            temp_s+=QString(item["discountPrice"].asString().c_str())+",";
            temp_s+=QString(item["auctionPrice"].asString().c_str())+",";
            QString d_r=QString(item["discountRate"].asString().c_str());
            temp_s+=(d_r.size()>0?d_r:"10.0")+",";
            temp_s+=QString::number(item["soldQuantity"].asInt())+",";
            temp_s+=QString::number(item["mall"].asInt());
            temp_s+="),";
            ++i;
        }
        insert_s+=temp_s;
        emit log_changed(QString("活动")+QString::number(eventId)+QString("获取成功，获取到")+QString::number(i)+QString("个商品\r\n"));
        return true;
    }
    else
    {
        emit log_changed("item json result error\r\n");
    }
    qDebug()<<"json_to_item_insert false";
    return false;
}

bool Json_Net::insert_item(const QList<Activaty> &ac_list)
{
    if(ac_list.size()<=0)
        return true;
    insert_s=("insert into item values ");
    qDebug()<<"这次插入的活动数量："<<ac_list.size();
    for(int i=0;i<ac_list.size();++i)
    {
        qDebug()<<"获取活动："<<ac_list[i].eventId;
        emit log_changed(QString("正在获取活动:")+QString::number(ac_list[i].eventId)+("\r\n"));
        if(item_get_insert(ac_list[i].eventId,default_pid,1,1000))
        {
            ;
        }
        else
        {
            emit log_changed(QString("活动")+QString::number(ac_list[i].eventId)+QString("获取失败,正在重试\r\n"));
            if(item_get_insert(ac_list[i].eventId,default_pid,1,1000))
            {
                emit log_changed(QString("活动")+QString::number(ac_list[i].eventId)+QString("重试获取成功\r\n"));
            }
            else
            {
                emit log_changed(QString("活动")+QString::number(ac_list[i].eventId)+QString("重试获取失败，跳过\r\n"));
            }
        }
    }
    insert_s[insert_s.size()-1]='\0';
    qDebug()<<"商品信号开始发射了:";
    qDebug()<<"size:"<<insert_s.size();
    emit sql_insert(insert_s);
    insert_s.clear();
    qDebug()<<"商品信号发射结束";
    return true;
}

bool Json_Net::pid_get(QList<Pid> &pid_list)
{
    QString url("http://pub.alimama.com/common/adzone/adzoneManage.json?tab=3&toPage=1&perPageSize=40&gcid=8&_tb_token_=");
    url+=m_alimama_tb_token;
    url+=("&_input_charset=utf-8");

    http_get(url,response);
    //qDebug()<<response;
    Json::Value root;
    bool jsonok=json_ok(root,response);
    if(!root.isNull()&&jsonok==true)
    {
        if(json_to_pid(root,pid_list))
        {
            if(!pid_list.empty())
            {
                qDebug()<<"推广位解析完成";
                return true;
            }
            else
                emit log_changed("没有发现推广位\r\n");
        }
    }
    return false;
}

bool Json_Net::json_to_pid(Json::Value &root, QList<Pid> &pid_list)
{
    emit log_changed("正在解析推广位\r\n");
    if(!root["data"]["pagelist"].isNull()&&root["data"]["pagelist"].isArray()&&!root["data"]["adzonesDO"].isNull())
    {
        m_user_num_id=QString::number((long long)(root["data"]["adzonesDO"]["memberid"].asDouble()));
        qDebug()<<m_user_num_id;
        Json::Value data(root["data"]["pagelist"]);
        for(auto item:data)
        {
            if(QString(item["tag"].asString().c_str())==QString("59"))
            {
                Pid temp;
                temp.name=QString(item["name"].asString().c_str());
                temp.tag=QString("59");
                temp.siteid=item["siteid"].asInt();
                temp.adzoneid=item["adzoneid"].asInt();
                temp.sitename=QString(item["sitename"].asString().c_str());
                temp.mixPv30day=item["mixPv30day"].asInt();
                temp.mixClick30day=item["mixClick30day"].asInt();
                temp.mixCtr30day=item["mixCtr30day"].asDouble();
                temp.rec30day=item["rec30day"].asDouble();
                temp.clickRate=QString(item["clickRate"].asString().c_str());
                temp.adzonePid=QString(item["adzonePid"].asString().c_str());
                temp.mixAlipayNum30day=item["mixAlipayNum30day"].asInt();
                temp.mixAlipayRec30day=item["mixAlipayRec30day"].asDouble();

                //QString s(ui->textEdit->toPlainText());
                //s+=temp.toString();
                //ui->textEdit->setPlainText(s);

                pid_list.push_back(temp);
            }

        }
        return true;
    }
    else
    {
        emit log_changed("pid json result error\r\n");
    }
    return false;
}

bool Json_Net::get_pid_list()
{
    this->pid_list.clear();//更新前清空
    if(pid_get(this->pid_list))
    {
        emit log_changed(QString("推广位更新完成")+QString::number(pid_list.size())+"个\r\n");
        return true;
    }
    return false;
}

void Json_Net::on_pid_need_update()
{
    emit log_changed("正在更新推广位信息\r\n");
    if(get_pid_list())
    {
        emit pid_updated(this->pid_list,m_user_num_id);
    }
}

void Json_Net::get_default_pid()
{
    if(pid_list.size()>0&&m_user_name.size()<=0)
    {
        default_pid=("mm_")+m_user_num_id+("_");
        default_pid=default_pid+QString::number(pid_list[0].siteid)+("_");
        default_pid=default_pid+QString::number(pid_list[0].adzoneid);
    }
    if(default_pid.size()<=0)
    {
        QMessageBox(QMessageBox::NoIcon,"错误","未找到默认推广位").exec();
        emit log_changed("错误,未找到默认推广位\r\n");
    }
}

int Json_Net::date_to_int(QString date)
{
    //qDebug()<<date;
    //emit log_changed(date);
    QDate d=QDate::fromString(date,"yyyy-MM-dd");
    return d.toString("yyyyMMdd").toInt();
}

void Json_Net::on_update(QMap<int, int>activaty_map)
{
    QList<Activaty>activaty_list;
    int count=0;
    int page=1;
    int page_size=100;
    bool has_next_page=true;
    int total_page=0;
    int r_t=0;
    int c=0;
    while(true)
    {
        ++r_t;
        activaty_list.clear();
        if(activaty_get(page,activaty_list,page_size,has_next_page,total_page))
        {
            emit log_changed(QString("第")+QString::number(page)+QString("页成功获取到")+QString::number(activaty_list.size())+QString("个活动\r\n"));
        }
        else
        {
            emit log_changed(QString("第")+QString::number(page)+QString("页获取失败，重试一次\r\n"));
            if(activaty_get(page,activaty_list,page_size,has_next_page,total_page))
            {
                emit log_changed(QString("第")+QString::number(page)+QString("页重试获取到\r\n")+QString::number(activaty_list.size())+QString("个活动\r\n"));
            }
            else
            {
                emit log_changed(QString("第")+QString::number(page)+QString("页重试获取失败，跳过\r\n"));
            }
        }
        qDebug()<<"map before"<<activaty_map.size();
        qDebug()<<"before"<<activaty_list.size();
        activaty_contain(activaty_map,activaty_list);
        emit log_changed(QString::number(activaty_list.size())+QString("个需要插入\r\n"));
        count+=activaty_list.size();
        qDebug()<<"after"<<activaty_list.size();
        qDebug()<<"map after"<<activaty_map.size();
        /*if(activaty_list.size()<=0)
        {
            break;
        }*/
        //else
       // {
            insert_activaty(activaty_list);
            for(auto i:activaty_list)
            {
                activaty_map.insert(i.eventId,i.eventId);
            }
        //}
        ++page;
        if(has_next_page==false)
        {
            break;
        }
        if(r_t>total_page*2)
            break;
        qDebug()<<"totalpage:"<<total_page;
        if(total_page!=0&&r_t>total_page)
            break;
        if(activaty_list.size()<=0)
        {
            ++c;
        }
        if(c>=5)
        {
        //    break;
        }
    }
    emit log_changed(QString("数据库更新完成,更新活动")+QString::number(count)+"个\r\n");
    QSettings s("user.ini",QSettings::IniFormat);
    s.setValue("time",QDate::currentDate().toString("yyyy-MM-dd"));
}

bool Json_Net::activaty_contain(QMap<int, int> &map, QList<Activaty> &list)
{
    for(auto i=list.begin();i!=list.end();)
    {
        auto it=map.find(i->eventId);
        if(map.end()!=it)
        {
            i=list.erase(i);
        }
        else
            ++i;
    }
    return true;
}

void Json_Net::on_need_imagin(QString url)
{
    http_get(url,this->response);
    if(QFile::exists("temp.jpg"))
    {
        QFile::remove("temp.jpg");
    }
    QFile file("temp.jpg");
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(response);
        file.close();
        emit imagin_complete();
    }
}

void Json_Net::on_need_item(QString eventId, QString itemId,QString pid)
{
    QString url("http://temai.taobao.com/event/items.json?toPage=1");
    url+=("&perPageSize=1000");
    url+=("&catId=&tagId=&pid=");
    url+=pid;
    url+=("&unid=&platformType=1&isPreview=0&id=");
    url+=eventId;

    http_get(url,response);

    Json::Value root;
    bool jsonok=json_ok(root,response);
    if(!root.isNull()&&jsonok==true)
    {
        if(!root["data"]["result"].isNull()&&root["data"]["result"].isArray())
        {
            Json::Value data(root["data"]["result"]);
            for(auto item:data)
            {
                if(QString::number((long long)(item["itemId"].asDouble()))==itemId)
                {
                    Item temp;
                    temp.itemId=itemId;
                    temp.eventId=eventId.toInt();
                    temp.sellerId=QString::number((long long)(item["sellerId"].asDouble()));
                    temp.itemTitle=QString(item["itemTitle"].asString().c_str());
                    temp.picUrl=QString(item["picUrl"].asString().c_str());
                    temp.tag=item["tag"].asInt();
                    temp.href=QString(item["href"].asString().c_str());
                    temp.commissionRate=item["commissionRate"].asInt();
                    temp.isSoldOut=item["isSoldOut"].asInt();
                    temp.discountPrice=QString(item["discountPrice"].asString().c_str()).toDouble();
                    temp.auctionPrice=QString(item["auctionPrice"].asString().c_str()).toDouble();
                    temp.discountRate=QString(item["discountRate"].asString().c_str()).toDouble();
                    temp.soldQuantity=item["soldQuantity"].asInt();
                    temp.mall=item["mall"].asInt();
                    emit item_complete(temp);
                    get_dwz(temp.href);
                    if(pid.size()>2)
                    {
                        emit log_changed(QString("获取特卖网址成功，特卖推广位为：")+pid+"\r\n");
                    }
                    else
                        emit log_changed(QString("获取特卖网址成功，特卖推广位为空，此时推广可能无法获得佣金，请先登录或更新推广位，请注意！！！\r\n"));
                    break;
                }
            }
        }
        else
            emit log_changed(eventId+"没有解析到商品\r\n");
    }
}

bool Json_Net::get_dwz(QString href)
{
    href="url=http:"+href+"&alias=&access_type=web";
    QNetworkAccessManager manager;
    QNetworkRequest req;
    req.setUrl(QUrl("http://dwz.cn/create.php"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded;charset=\"UTF-8\"");
    QEventLoop loop;
    QByteArray array(href.toLatin1());
    connect(&manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));
    QNetworkReply *reply=manager.post(req,array);
    loop.exec();
    QByteArray data=reply->readAll();
    disconnect(&manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));

    Json::Value root;
    Json::Reader reader;
    if(reader.parse(data.toStdString(),root))//no error
    {
        if(root["status"].asInt()==0)
        {
            emit dwz_complete(QString(root["tinyurl"].asString().c_str()));
        }
        else
            emit log_changed(QString("获取短网址失败！")+QString(root["err_msg"].asString().c_str())+"\r\n");
    }
    else
        emit log_changed("获取短网址失败");

    reply->deleteLater();
    return true;
}
