#ifndef CPPCLASS_H
#define CPPCLASS_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QQuickItem>

class cppClass : public QObject
{
    Q_OBJECT

public slots:
    //string类型的槽
    //void cppSlots(QString str)
    //{
    //    qDebug()<<"cpp slots recv:" + str;
    //}
    //对象+int类型的槽
    void cppSlots(const QVariant item,const QVariant text,int x,int y)
    {
        QQuickItem * it = qobject_cast<QQuickItem *>(item.value<QObject*>());
        QString s = QString("width:%1  height:%2  click:%3 %4").arg(it->width()).arg(it->height()).arg(x).arg(y);
        (qobject_cast<QQuickItem *>(text.value<QObject*>()))->setProperty("text",s);
    }

};

#endif // CPPCLASS_H
