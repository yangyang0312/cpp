#ifndef RESOURCE_MINITOR_H
#define RESOURCE_MINITOR_H

#include <QObject>
#include <QTimer>
#include <QProcess>
#include <QDebug>

class resource_minitor : public QObject
{
    Q_OBJECT
public:

    explicit resource_minitor(QObject *parent = nullptr);

private slots:
    void get_resource__();

private:
    bool get_mem_usage__();
    bool get_net_usage__();
    bool get_disk_speed__();
    bool get_cpu_usage__();
    bool get_disk_space__();
    bool get_path_space(const QString & path);

private:
    const int m_timer_interval__ = 1000;
    QTimer monitor_timer__;
    double m_send_bytes__ = 0;
    double m_recv_bytes__ = 0;
    double m_disk_read__ = 0;
    double m_disk_write__ = 0;
    double m_cpu_total__ = 0;
    double m_cpu_use__ = 0;
};

#endif // RESOURCE_MINITOR_H
