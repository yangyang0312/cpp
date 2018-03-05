#include "resource_minitor.h"
#include "sys/statfs.h"

resource_minitor::resource_minitor(QObject *parent) : QObject(parent)
{
    connect(&monitor_timer__, &QTimer::timeout, this, &resource_minitor::get_resource__);
    monitor_timer__.start(m_timer_interval__);
}

void resource_minitor::get_resource__()
{
    get_cpu_usage__ ();
    get_disk_speed__();
    get_mem_usage__ ();
    get_net_usage__ ();
    get_disk_space__();
    get_path_space("/");
    qDebug()<<"\n";
}

bool resource_minitor::get_mem_usage__()
{
    QProcess process;
    process.start("free -m");             //使用free完成获取
    process.waitForFinished();
    process.readLine();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");//将连续空格替换为单个空格 用于分割
    auto lst = str.split(" ");
    if(lst.size() > 6)
    {
        qDebug("mem total:%.0lfMB free:%.0lfMB",lst[1].toDouble(),lst[6].toDouble());
        return true;
    }
    return false;
}

bool resource_minitor::get_net_usage__()
{
    QProcess process;
    process.start("cat /proc/net/dev");        //读取文件/proc/net/dev获取网络收发包数量，再除取样时间得到网络速度
    process.waitForFinished();
    process.readLine();
    process.readLine();
    while(!process.atEnd())
    {
        QString str = process.readLine();
        str.replace("\n","");
        str.replace(QRegExp("( ){1,}")," ");
        auto lst = str.split(" ");
        if(lst.size() > 9 && lst[0] == "enp2s0:")
        {
            double recv = 0;
            double send = 0;
            if(lst.size() > 1)
                recv = lst[1].toDouble();
            if(lst.size() > 9)
                send = lst[9].toDouble();
            qDebug("%s  接收速度:%.0lfbyte/s 发送速度:%.0lfbyte/s",lst[0].toStdString().c_str(),(recv - m_recv_bytes__) / (m_timer_interval__ / 1000.0),(send - m_send_bytes__) / (m_timer_interval__ / 1000.0));
            m_recv_bytes__ = recv;
            m_send_bytes__ = send;
        }
    }
    return true;
}

bool resource_minitor::get_cpu_usage__()
{
    QProcess process;
    process.start("cat /proc/stat");
    process.waitForFinished();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
    auto lst = str.split(" ");
    if(lst.size() > 3)
    {
        double use = lst[1].toDouble() + lst[2].toDouble() + lst[3].toDouble();
        double total = 0;
        for(int i = 1;i < lst.size();++i)
            total += lst[i].toDouble();
        if(total - m_cpu_total__ > 0)
        {
            qDebug("cpu rate:%.2lf%%",(use - m_cpu_use__) / (total - m_cpu_total__) * 100.0);
            m_cpu_total__ = total;
            m_cpu_use__ = use;
            return true;
        }
    }
    return false;
}

bool resource_minitor::get_disk_speed__()
{
    QProcess process;
    process.start("iostat -k -d");
    process.waitForFinished();
    process.readLine();
    process.readLine();
    process.readLine();
    QString str = process.readLine();
    str.replace("\n","");
    str.replace(QRegExp("( ){1,}")," ");
    auto lst = str.split(" ");
    if(lst.size() > 5)
    {
        qDebug("disk read:%.0lfkb/s disk write:%.0lfkb/s",(lst[4].toDouble() - m_disk_read__ ) / (m_timer_interval__ / 1000.0),(lst[5].toDouble() - m_disk_write__) / (m_timer_interval__ / 1000.0));
        m_disk_read__  = lst[4].toDouble();
        m_disk_write__ = lst[5].toDouble();
        return true;
    }
    return false;
}

bool resource_minitor::get_disk_space__()
{
    QProcess process;
    process.start("df -k");
    process.waitForFinished();
    process.readLine();
    while(!process.atEnd())
    {
        QString str = process.readLine();
        if(str.startsWith("/dev/sda"))
        {
            str.replace("\n","");
            str.replace(QRegExp("( ){1,}")," ");
            auto lst = str.split(" ");
            if(lst.size() > 5)
                qDebug("挂载点:%s 已用:%.0lfMB 可用:%.0lfMB",lst[5].toStdString().c_str(),lst[2].toDouble()/1024.0,lst[3].toDouble()/1024.0);
        }
    }
    return true;
}

bool resource_minitor::get_path_space(const QString & path)
{
    struct statfs diskInfo;
    statfs(path.toUtf8().data(), &diskInfo);
    qDebug("%s 总大小:%.0lfMB 可用大小:%.0lfMB",path.toStdString().c_str(),(diskInfo.f_blocks * diskInfo.f_bsize)/1024.0/1024.0,(diskInfo.f_bavail * diskInfo.f_bsize)/1024.0/1024.0);
    return true;
}

