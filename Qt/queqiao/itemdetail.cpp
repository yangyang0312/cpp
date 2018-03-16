#include "itemdetail.h"
#include "ui_itemdetail.h"
#include "autoclose.h"
#include <QClipboard>
#include <QDesktopServices>
#include <QWebFrame>
#include <QFile>
#include <QSettings>
#include <windows.h>

itemdetail::itemdetail(QWidget *parent) :
    QMainWindow(parent),
    log(),
    temp_html(),
    ui(new Ui::itemdetail)
{
    ui->setupUi(this);

    ui->pid_s->setToolTip("选择推广位后生成这个推广位的推广地址");
    ui->pid->setToolTip("选择推广位后生成这个推广位的推广地址");

    ui->update_pid->setToolTip("更新推广位");

    ui->item->setToolTip("商品信息");

    ui->activaty->setToolTip("活动信息");

    ui->auction_price->setToolTip("商品原价");
    ui->auction_price_s->setToolTip("商品原价");

    ui->discount_price->setToolTip("商品现价");
    ui->discount_price_s->setToolTip("商品现价");

    ui->sold_quantity->setToolTip("商品销量");
    ui->sold_quantity_s->setToolTip("商品销量");

    ui->remain_time->setToolTip("剩余推广天数");
    ui->remain_time_s->setToolTip("剩余推广天数");

    ui->share_rate->setToolTip("分成比例");
    ui->share_rate_s->setToolTip("分成比例");

    ui->mall->setToolTip("类别");
    ui->mall_s->setToolTip("类别");

    ui->income->setToolTip("预估收入为现价*佣金比例*分成比例，仅供参考，请以阿里妈妈的为准");
    ui->income_s->setToolTip("预估收入为现价*佣金比例*分成比例，仅供参考，请以阿里妈妈的为准");

    ui->com_rate->setToolTip("佣金比例");
    ui->com_rate_s->setToolTip("佣金比例");

    ui->is_sold_out->setToolTip("商品是否已经卖光");
    ui->is_sold_out_s->setToolTip("商品是否已经卖光");

    ui->discount_rate->setToolTip("商品折扣比例");
    ui->discount_rate_s->setToolTip("商品折扣比例");

    ui->time->setToolTip("活动推广时间");
    ui->time_s->setToolTip("活动推广时间");

    ui->event_title->setToolTip("活动标题");
    ui->event_title_s->setToolTip("活动标题");

    ui->alipay_num->setToolTip("活动30天推广笔数");
    ui->alipay_num_s->setToolTip("活动30天推广笔数");

    ui->cvr->setToolTip("活动点击率");
    ui->cvr_s->setToolTip("活动点击率");

    ui->avg_commission_rate->setToolTip("活动平均佣金比例");
    ui->avg_commission_rate_s->setToolTip("活动平均佣金比例");

    ui->tk_level->setToolTip("活动发起者淘客等级");
    ui->tk_level_s->setToolTip("活动发起者淘客等");

    ui->promotion_type_str->setToolTip("活动促销类型");
    ui->promotion_type_str_s->setToolTip("活动促销类型");

    ui->item_title->setToolTip("商品名");
    ui->item_title_s->setToolTip("商品名");
    ui->item_title_copy->setToolTip("复制商品名");

    ui->item_detail->setToolTip("商品详情地址");
    ui->item_detail_s->setToolTip("商品详情地址");
    ui->item_detail_open->setToolTip("复制商品详情地址");
    ui->item_detail_copy->setToolTip("打开商品详情地址");

    ui->item_href->setToolTip("特卖地址");
    ui->item_href_s->setToolTip("特卖地址");
    ui->item_href_open->setToolTip("生成特卖地址并复制");
    ui->item_href_copy->setToolTip("打开特卖地址");

    ui->dwz->setToolTip("短网址");
    ui->dwz_copy->setToolTip("短网址");
    ui->dwz_open->setToolTip("生成短网址(dwz)");
    ui->dwz_s->setToolTip("打开短网址");

    ui->event_detail->setToolTip("活动详情地址");
    ui->event_detail_s->setToolTip("活动详情地址");
    ui->event_detail_copy->setToolTip("复制活动详情地址");
    ui->event_detail_open->setToolTip("打开活动详情地址");

    ui->event_info->setToolTip("活动信息地址");
    ui->event_info_s->setToolTip("活动信息地址");
    ui->event_info_copy->setToolTip("复制活动信息地址");
    ui->event_info_open->setToolTip("打开活动信息地址");

    ui->item_review->setToolTip("商品评价");
    ui->item_review_s->setToolTip("商品评价");

    ui->templet_combo_box->setToolTip("选择要复制的模板");
    ui->templet_edit->setToolTip("编辑复制模板");
    ui->templet_s->setToolTip("选择要复制的模板");
    ui->templete_view->setToolTip("复制预览");
    ui->copy->setToolTip("一键复制");

    QSettings settings("user.ini",QSettings::IniFormat);
    ui->pid->addItem(settings.value("pid").toString());
}

itemdetail::~itemdetail()
{
    if(QFile::exists("temp.jpg"))
        QFile::remove("temp.jpg");
    log.clear();
    QSettings settings("user.ini",QSettings::IniFormat);
    settings.setValue("pid",ui->pid->currentText());
    delete ui;
}

void itemdetail::on_need_detail(Table item)
{
    this->item=item;
    update_window();

    this->show();
}

void itemdetail::open_browser(const QString &url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void itemdetail::update_window()
{
    ui->item_detail->setText(QString("http://item.taobao.com/item.htm?id="+item.itemId));
    ui->event_info->setText(QString("http://pub.alimama.com/myunion.htm?#!/promo/act/activity_detail?eventId=")+QString::number(item.eventId));
    ui->event_detail->setText(QString("http://temai.taobao.com/preview.htm?id=")+QString::number(item.eventId));
    ui->item_title->setText(item.itemTitle);
    ui->com_rate->setText(QString::number((double)(item.commissionRate/100.0))+" %");
    ui->is_sold_out->setText(item.isSoldOut==1?"商品已卖完":"未售完");
    ui->discount_price->setText(QString::number(item.discountPrice)+" 元");
    ui->auction_price->setText(QString::number(item.auctionPrice)+" 元");
    ui->discount_rate->setText(QString::number(item.discountRate));
    ui->sold_quantity->setText(QString::number(item.soldQuantity)+" 件");
    ui->mall->setText(item.mall==1?"天猫":"淘宝");
    ui->alipay_num->setText(QString::number(item.alipayNum)+"件");
    ui->cvr->setText(QString::number(item.cvr)+" %");
    ui->event_title->setText(item.eventTitle);
    ui->promotion_type_str->setText(item.promotionTypeStr);
    ui->avg_commission_rate->setText(QString::number(item.avgCommission)+" %");
    ui->time->setText(get_time(item.startTime,item.endTime));
    ui->remain_time->setText(get_remain_days(item.endTime)+" 天");
    ui->tk_level->setText(get_tk_level(item.tkLevel));
    ui->income->setText(QString::number((double)(item.discountPrice*item.commissionRate*item.shareRate/1000000.0),'f',2)+" 元");
    ui->share_rate->setText(QString::number((int)(item.shareRate))+" %");
}

void itemdetail::on_item_detail_open_clicked()
{
    open_browser(QString("http://item.taobao.com/item.htm?id=")+item.itemId);
}

void itemdetail::on_item_href_open_clicked()
{
    if(ui->item_href->text().size()>5)
    {
        open_browser(ui->item_href->text());
    }
    else
        log_ch("还未生成特卖地址");
}

void itemdetail::on_dwz_open_clicked()
{
    if(ui->dwz->text().size()>5)
    {
        open_browser(ui->dwz->text());
    }
    else
        log_ch("还未生成短网址");
}

void itemdetail::on_event_info_open_clicked()
{
    open_browser(ui->event_info->text());
}

void itemdetail::on_event_detail_open_clicked()
{
    open_browser(ui->event_detail->text());
}

void itemdetail::closeEvent(QCloseEvent *event)
{
    ui->dwz->clear();
    ui->item_href->clear();
    Table t;
    this->item=t;
    temp_html.clear();
    if(QFile::exists("temp.jpg"))
    {
        QFile::remove("temp.jpg");
    }
}

QString itemdetail::get_remain_days(int endTime)
{
    QDate start=QDate::currentDate();
    QDate end=QDate::fromString(QString::number(endTime),"yyyyMMdd");
    if(end>=start)
    {
        return QString::number((end.year()-start.year())*365+(end.month()-start.month())*30+(end.day()-start.day()));
    }
    else
    {
        emit log_changed(QString("活动日期错误，当前时间为：")+start.toString("yyyy-MM-dd")+("，而活动结束时间为：")+end.toString("yyyy-MM-dd")+"\r\n");
        return "日期错误";
    }
}

QString itemdetail::get_time(int start, int end)
{
    return QDate::fromString(QString::number(start),"yyyyMMdd").toString("yyyy-MM-dd")+" / "+QDate::fromString(QString::number(end),"yyyyMMdd").toString("yyyy-MM-dd");
}

QString itemdetail::get_tk_level(int level)
{
    QString s;
    switch(level)
    {
    case 0:
        s="新会员";
        break;
    case 1:
        s="普通会员";
        break;
    case 2:
        s="红心会员";
        break;
    case 3:
        s="钻石会员";
        break;
    case 4:
        s="皇冠会员";
        break;
    case 5:
        s="金冠会员";
        break;
    default:
        emit log_changed("获取活动发起者淘客等级失败，错误："+QString::number(level)+"\r\n");
        s="";
        break;
    }
    return s;
}

void itemdetail::on_event_info_copy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->event_info->text());
    emit log_changed("已复制活动信息链接...\r\n");
    log_ch("复制成功\r\n");
}

void itemdetail::on_copy_clicked()
{
    //ui->templete_view->selectAll();
    //ui->templete_view->copy();
    QImage img("temp.jpg");
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setImage(img);
    emit log_changed("已复制商品图片到剪切板...\r\n");
    log_ch("复制成功\r\n");
}

void itemdetail::on_imagin_complete()
{
    if(QFile::exists("temp.jpg"))
    {
        temp_html=("<html><img style=\"-webkit-user-select: none; cursor: zoom-in;\" src=\"temp.jpg\" width=\"250\" height=\"250\" />");
        temp_html=temp_html+ui->item_title->text()+"<br/>原价："+ui->auction_price->text()+"  现价:"+ui->discount_price->text()+"<br/>";
        temp_html+="</html>";
        ui->templete_view->setHtml(temp_html);
        qDebug()<<temp_html;
    }
}

void itemdetail::on_item_href_copy_clicked()
{
    QString p(ui->pid->currentText());
    if(int i=p.indexOf("_mm_"))
    {
        if(i>-1)
        {
            emit log_changed(QString("正在生成特卖地址,当前推广位为:")+p+" ,请注意检查推广位是不是自己的!\r\n");
            p=p.right(p.size()-i-1);
        }
        else
        {
            emit log_ch("推广位错误！\r\n");
            emit log_changed(QString("推广位错误！！！")+p+"\r\n");
        }
    }
    emit need_item(QString::number(item.eventId),item.itemId,p);
    log_ch("正在生成特卖\r\n");
}

void itemdetail::on_item_complete(Item it)
{
    ui->item_href->setText(QString("http:")+it.href);
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(QString("http:")+it.href);
    emit log_changed("已复制特卖推广链接到剪切板...\r\n");
    log_ch("特卖生成成功\r\n");
    log_ch("特卖复制成功\r\n");

    item.auctionPrice=it.auctionPrice;
    item.commissionRate=it.commissionRate;
    item.discountPrice=it.discountPrice;
    item.discountRate=it.discountRate;
    item.isSoldOut=it.isSoldOut;
    item.itemTitle=it.itemTitle;
    item.soldQuantity=it.soldQuantity;
    item.sellerId=it.sellerId;
    item.mall=it.mall;
    item.picUrl=it.picUrl;

    update_window();
}

void itemdetail::on_update_pid_clicked()
{
    emit pid_need_update();
    log_ch("更新推广位\r\n");
}

void itemdetail::on_pid_updated(QList<Pid>p,QString num_id)
{
    ui->pid->clear();
    for(auto i:p)
    {
        QString s=i.sitename+"_"+i.name+"(特卖)_mm_"+num_id+("_");
        s=s+QString::number(i.siteid)+("_");
        s=s+QString::number(i.adzoneid);
        ui->pid->addItem(s);
    }
    log_ch("推广位已更新\r\n");
}

void itemdetail::on_dwz_complete(QString s)
{
    ui->dwz->setText(s);
    QString h("<html><img style=\"-webkit-user-select: none; cursor: zoom-in;\" src=\"temp.jpg\" width=\"250\" height=\"250\" />");
    h=h+"<br/>"+ui->item_title->text()+"<br/>原价："+ui->auction_price->text()+"  现价:"+ui->discount_price->text()+"<br/>";
    h=h+"网址："+ui->dwz->text()+("</html>");
    ui->templete_view->setHtml(h);
    log_ch("短网址生成成功\r\n");
    emit log_changed("短网址生成成功\r\n");
}

void itemdetail::on_dwz_copy_clicked()
{
    if(ui->dwz->text().size()>5)
    {
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ui->dwz->text());
        emit log_changed("已复制特卖短网址到剪切板...\r\n");
        log_ch("短网址复制成功\r\n");
    }
    else
    {
        on_item_href_copy_clicked();
    }
}

void itemdetail::log_ch(QString s)
{
    if(log.size()>1000)
    {
        log=log.right(log.size()-800);
    }
    log+=s;
    ui->log->setPlainText(log);
    QTextCursor cursor = ui->log->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->log->setTextCursor(cursor);
}

void itemdetail::on_item_title_copy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->item_title->text());
    emit log_changed("已复制商品标题链接...\r\n");
    log_ch("复制成功\r\n");
}

void itemdetail::on_item_detail_copy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->item_detail->text());
    emit log_changed("已复制商品链接...\r\n");
    log_ch("复制成功\r\n");
}

void itemdetail::on_event_detail_copy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->event_detail->text());
    emit log_changed("已复制活动详情地址链接...\r\n");
    log_ch("复制成功\r\n");
}

void itemdetail::on_copy_char_clicked()
{
    ui->templete_view->selectAll();
    ui->templete_view->copy();
    emit log_changed("文字复制成功\r\n");
    log_ch("复制成功\r\n");
}
