#ifndef APPDATA_H
#define APPDATA_H

#include <QDateTime>
#include <QObject>
#include <QTimer>

class appData : public QObject
{
    Q_OBJECT

public:
    appData()
    {
        QTimer * pTimer = new QTimer(this);
        pTimer->setInterval(1000);
        connect(pTimer,SIGNAL(timeout()),this,SIGNAL(timerChanged()));  //关联信号
        pTimer->start();
    }
    //可以使用Q_INVOKABLE的public函数或者public slots
    Q_INVOKABLE QDateTime getCurrentTime()
    {
        return QDateTime::currentDateTime();
    }

signals:
   void timerChanged();
};

#endif // APPDATA_H
