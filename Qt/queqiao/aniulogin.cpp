#include "aniulogin.h"
#include "ui_aniulogin.h"
#include <QSettings>
#include <QAxObject>
#include <QVariant>
#include <windows.h>
#include <QUuid>
#include <QUrl>
#include <Qdebug>

AniuLogin::AniuLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AniuLogin),
    is_aniu_(false)
{
    ui->setupUi(this);
}

AniuLogin::~AniuLogin()
{
    delete ui;
}

QString AniuLogin::getMcode()
{
    QString number_code;
    number_code+= getWMIHWInfo(1);
    number_code+= getWMIHWInfo(2);
    number_code+= getWMIHWInfo(3);
    number_code+= getWMIHWInfo(4);
    number_code+= getWMIHWInfo(5);
    QByteArray byte=QCryptographicHash::hash(number_code.toLatin1(),QCryptographicHash::Sha3_512);
    QString key=byte.toHex();
    return key;
}

QString AniuLogin::getWMIHWInfo(int type)
{
    /*
//0.当前原生网卡地址：
SELECT MACAddress FROM Win32_NetworkAdapter WHERE (MACAddress IS NOT NULL) AND (NOT (PNPDeviceID LIKE 'ROOT%'))
// 1.硬盘序列号
SELECT PNPDeviceID FROM Win32_DiskDrive WHERE(SerialNumber IS NOT NULL) AND (MediaType LIKE 'Fixed hard disk%')
//2.获取主板序列号
SELECT SerialNumber FROM Win32_BaseBoard WHERE (SerialNumber IS NOT NULL)
// 3.处理器ID
SELECT ProcessorId FROM Win32_Processor WHERE (ProcessorId IS NOT NULL)
// 4.BIOS序列号
SELECT SerialNumber FROM Win32_BIOS WHERE (SerialNumber IS NOT NULL)
// 5.主板型号
SELECT Product FROM Win32_BaseBoard WHERE (Product IS NOT NULL)*/
    QString hwInfo=("");
    QStringList sqlCmd;
    sqlCmd.clear();
    sqlCmd<<("SELECT MACAddress FROM Win32_NetworkAdapter WHERE (MACAddress IS NOT NULL) AND (NOT (PNPDeviceID LIKE 'ROOT%'))");
    //注意qt调用 wmi时，对查询语句要求很严格，所以 like之类的句子务必精确才能有结果出来
    sqlCmd<<("SELECT PNPDeviceID FROM Win32_DiskDrive WHERE( PNPDeviceID IS NOT NULL) AND (MediaType LIKE 'Fixed%')");
    sqlCmd<<("SELECT SerialNumber FROM Win32_BaseBoard WHERE (SerialNumber IS NOT NULL)");
    sqlCmd<<("SELECT ProcessorId FROM Win32_Processor WHERE (ProcessorId IS NOT NULL)");
    sqlCmd<<("SELECT SerialNumber FROM Win32_BIOS WHERE (SerialNumber IS NOT NULL)");
    sqlCmd<<("SELECT Product FROM Win32_BaseBoard WHERE (Product IS NOT NULL)");
    QStringList columnName;
    columnName.clear();
    columnName<<("MACAddress");
    columnName<<("PNPDeviceID");
    columnName<<("SerialNumber");
    columnName<<("ProcessorId");
    columnName<<("SerialNumber");
    columnName<<("Product");
    QAxObject *objIWbemLocator = new QAxObject("WbemScripting.SWbemLocator");
    QAxObject *objWMIService = objIWbemLocator->querySubObject("ConnectServer(QString&,QString&)",QString("."),QString("root\\cimv2"));
    QString query=("");
    if(type<sqlCmd.size())
        query=sqlCmd.at(type);
    QAxObject *objInterList = objWMIService->querySubObject("ExecQuery(QString&))", query);
    QAxObject *enum1 = objInterList->querySubObject("_NewEnum");
    IEnumVARIANT* enumInterface = 0;
    enum1->queryInterface(QUuid(IID_IEnumVARIANT), (void**)&enumInterface);
    enumInterface->Reset();
    for (int i = 0; i < objInterList->dynamicCall("Count").toInt(); i++)
    {
        VARIANT *theItem = (VARIANT*)malloc(sizeof(VARIANT));
        if (enumInterface->Next(1,theItem,NULL) != S_FALSE)
        {
            QAxObject *item = new QAxObject((IUnknown *)theItem->punkVal);
            if(item)
            {
                if(type<columnName.size())
                {
                    QByteArray datagram(columnName.at(type).toLatin1()); //Or
                    const char* tempConstChar = datagram.data();
                    hwInfo=item->dynamicCall(tempConstChar).toString();
                }
            }
            else
            {

            }
        }else
        {

        }
    }
    return hwInfo;
}


void AniuLogin::on_webView_loadFinished(bool arg1)
{
    QString url=ui->webView->url().toString();
    if(url=="http://120.26.193.48:30001/huodong/fangdan-activity-list")
    {
        QSettings s("user.ini",QSettings::IniFormat);
        s.setValue("mCode",getMcode());
        is_aniu_=true;
        emit is_aniu(is_aniu_);
        this->hide();
    }
    else
    {
        is_aniu_=false;
    }
}

void AniuLogin::closeEvent(QCloseEvent *event)
{
    if(is_aniu_==false)
    {
        exit(0);
    }
    else
        emit is_aniu(is_aniu_);
}

void AniuLogin::need_aniu()
{
    QSettings s("user.ini",QSettings::IniFormat);
    if(s.value("mCode").toString()==getMcode())
    {
        qDebug()<<"true";
        is_aniu_=true;
        emit is_aniu(is_aniu_);
        this->hide();
    }
    else
    {
        this->show();
        ui->webView->load(QUrl("http://120.26.193.48:30001/huodong/fangdan-activity-login"));
    }
}
