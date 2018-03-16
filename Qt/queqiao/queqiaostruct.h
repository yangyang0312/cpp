#ifndef QUEQIAOSTRUCT
#define QUEQIAOSTRUCT

#include <QString>


typedef struct Activaty
{
    int eventId;//活动id，主键//int
    QString previewUrl;//活动地址//string
    int startTime;//开始时间//string
    int endTime;//结束时间//string
    double shareRate;//分成比例//string
    int eventStatus;//活动状态，推广中//int
    QString eventStatusStr;//活动状态字符串//string
    int alipayNum;//30天推广笔数//int
    double cvr;//活动点击率//string
    double avgCommission;//平均佣金比例//string
    int tkLevel;//活动发起者淘客等级，0,新会员,1,普通会员，2，红心会员，3，钻石会员，4，皇冠会员，5，金冠会员//int
    QString eventTitle;//活动标题//string
    QString comments;//内容//string
    int platformType;//平台类型//int
    QString platformTypeStr;//平台类型字符串//string
    int promotionType;//促销类型//int
    QString promotionTypeStr;//促销类型字符串//string
    QString auditEndTime;//字段未知//string
    int createFinish;//未知字段，似乎没用//int
    int canOperate;//未知字段，似乎没用//int
    int canEditFloor;//未知字段，似乎没用//int
    int highQualityType;//未知字段，似乎没用//int

public:
    QString toString()
    {
        QString s("eventId:");
        s=s+QString::number(eventId)+QString("\r\npreviewUrl:")+previewUrl;
        s=s+QString("\r\nstartTime:")+QString::number(startTime)+QString("\r\nendTime:")+QString::number(endTime);
        s=s+QString("\r\nshareRate:")+QString::number(shareRate)+QString("\r\neventStatus:")+QString::number(eventStatus);
        s=s+QString("\r\neventStatusStr:")+eventStatusStr+QString("\r\nalipayNum:")+QString::number(alipayNum);
        s=s+QString("\r\ncvr:")+QString::number(cvr)+QString("\r\navgCommission:")+QString::number(avgCommission);
        s=s+QString("\r\ntkLevel:")+QString::number(tkLevel)+QString("\r\neventTitle:")+eventTitle;
        s=s+QString("\r\ncomments:")+comments+QString("\r\nplatformType:")+QString::number(platformType);
        s=s+QString("\r\nplatformTypeStr:")+platformTypeStr+QString("\r\npromotionType:")+QString::number(promotionType);
        s=s+QString("\r\npromotionTypeStr:")+promotionTypeStr+QString("\r\nauditEndTime:")+auditEndTime;
        s=s+QString("\r\ncreateFinish:")+QString::number(createFinish)+QString("\r\ncanOperate:")+QString::number(canOperate);
        s=s+QString("\r\ncanEditFloor:")+QString::number(canEditFloor)+QString("\r\nhighQualityType:")+QString::number(highQualityType);
        s+="\r\n\r\n";
        //qDebug()<<s;
        return s;
    }
}Activaty;


typedef struct Item
{
    QString itemId;
    int eventId;
    QString sellerId;
    QString itemTitle;
    QString picUrl;
    int tag;
    QString href;
    int commissionRate;
    int isSoldOut;
    double discountPrice;
    double auctionPrice;
    double discountRate;
    int soldQuantity;
    int mall;
public:
    QString toString()
    {
        QString s("itemId:");
        s=s+itemId+("\r\nsellerId:")+sellerId;
        s=s+("\r\nitemTitle:")+itemTitle+("\r\npicUrl:")+picUrl;
        s=s+("\r\ntag:")+QString::number(tag)+("\r\nherf:")+href;
        s=s+("\r\ncommissionRate:")+QString::number(commissionRate);
        s=s+("\r\nisSoldOut:")+QString::number(isSoldOut)+("\r\ndiscountPrice:")+QString::number(discountPrice);
        s=s+("\r\nauctionPrice:")+QString::number(auctionPrice)+("\r\ndiscountRate:")+QString::number(discountRate);
        s=s+("\r\nsoldQuantity:")+QString::number(soldQuantity);
        s=s+("\r\nmall:")+QString::number(mall);
        s+=("\r\n\r\n");

        //qDebug()<<s;
        return s;
    }
}Item;

typedef struct Pid
{
    QString name;                 //:"123123",//推广位名字//string
    QString tag;                  //:"59",//类型，主题活动//string
    int siteid;                  //:10664071,//导购id//int
    int adzoneid;                 //:35042459,//推广位id//int
    QString sitename;           //:"jaklkla",//导购名字//string
    int mixPv30day;             //:0,//30天预览量//int
    int mixClick30day;           //:108,//30天点击数//int
    double mixCtr30day;          //:null,//不知道//double
    double rec30day;              //:0.00,//不知道，可能是最近30天收入//double
    QString clickRate;           //:"0",//点击率//string
    QString adzonePid;          //:"mm_null_10664071_35042459",//string
    int mixAlipayNum30day;      //:2,//30天付款笔数//int
    double mixAlipayRec30day;   //:7.21,//30天效果预览//double
public:
    QString toString()
    {
        QString s("name:");
        s=s+name+("\r\n")+("tag:")+tag+("\r\n")+("siteid:")+QString::number(siteid)+("\r\n");
        s=s+QString("adzoneid:")+QString::number(adzoneid)+("\r\n");
        s=s+QString("sitename:")+sitename+("\r\n")+("mixPv30day:")+QString::number(mixPv30day);
        s=s+("\r\nmixClick30day:")+QString::number(mixClick30day)+("\r\nmixCtr30day:");
        s=s+QString::number(mixCtr30day)+("\r\nrec30day:")+QString::number(rec30day);
        s=s+("\r\nclickRate:")+clickRate+("\r\nadzonePid:")+adzonePid+("\r\nmixAlipayNum30day:");
        s=s+QString::number(mixAlipayNum30day)+("\r\nmixAlipayRec30day:")+QString::number(mixAlipayRec30day);
        s+=("\r\n\r\n");

        return s;
    }
}Pid;


typedef struct Table
{
    QString itemId;
    int eventId;
    QString sellerId;
    QString itemTitle;
    QString picUrl;
    int commissionRate;
    int isSoldOut;
    double discountPrice;
    double auctionPrice;
    double discountRate;
    int soldQuantity;
    int mall;
    int startTime;//开始时间//string
    int endTime;//结束时间//string
    double shareRate;//分成比例//string
    int alipayNum;//30天推广笔数//int
    double cvr;//活动点击率//string
    double avgCommission;//平均佣金比例//string
    int tkLevel;//活动发起者淘客等级，0,新会员,1,普通会员，2，红心会员，3，钻石会员，4，皇冠会员，5，金冠会员//int
    QString eventTitle;//活动标题//string
    QString promotionTypeStr;//促销类型字符串//string

public:
    QString toString()
    {
        QString s("itemId:");
        s=s+itemId+("\r\neventId:")+QString::number(eventId)+("\r\nsellerId:")+sellerId;
        s=s+"\r\nitemTitle:"+itemTitle+"\r\npicUrl:"+picUrl+"\r\ncommissionRate:";
        s=s+QString::number(commissionRate)+"\r\nisSoldOut:"+QString::number(isSoldOut);
        s=s+"\r\ndiscountPrice:"+QString::number(discountPrice)+"\r\nauctionPrice:";
        s=s+QString::number(auctionPrice)+"\r\ndiscountRate:"+QString::number(discountRate);
        s=s+"\r\nsoldQuantuty:"+QString::number(soldQuantity)+"\r\nmall:"+QString::number(mall);
        s=s+"\r\nstartTime:"+QString::number(startTime)+"\r\nendTime:"+QString::number(endTime);
        s=s+"\r\nshareRate:"+QString::number(shareRate)+"\r\nalipayNum:"+QString::number(alipayNum);
        s=s+"\r\ncvr:"+QString::number(cvr)+"\r\navgCommission:"+QString::number(avgCommission);
        s=s+"\r\ntkLevel:"+QString::number(tkLevel)+"\r\neventTitle:"+eventTitle;
        s=s+"\r\npromotionTypeStr:"+promotionTypeStr+"\r\n\r\n";

        return s;
    }
}Table;

#endif // QUEQIAOSTRUCT
