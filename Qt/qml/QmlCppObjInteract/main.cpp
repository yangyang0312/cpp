#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QObject>
#include <QDebug>
#include <QQmlProperty>
#include <QQuickItem>
#include <QMetaObject>
#include "cppclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQuickView viewer;
    viewer.setTitle("qml_c++对象交互");                                   //标题
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);              //resize
    viewer.setSource(QUrl("qrc:/main.qml"));                             //qml
    viewer.show();
    viewer.setProperty("width",640);                                    //设置属性的值
    viewer.setProperty("height",480);
    //查找qml对象，并修改其属性
    //viewer.rootObject()->findChild<QObject *>("text")->setProperty("text","Hello World.");
    //修改qml属性
    viewer.rootObject()->setProperty("value",1000);
    QQmlProperty::write(viewer.rootObject(),"value",1024);
    qDebug()<<"property value:"<<QQmlProperty::read(viewer.rootObject(),"value").toInt();
    //调用qml函数myQmlFunc
    QVariant ret;
    QVariant msg = "Hello Wolrd";
    QMetaObject::invokeMethod(viewer.rootObject(),"myQmlFunc",Q_RETURN_ARG(QVariant,ret),Q_ARG(QVariant,msg));
    qDebug()<<ret.toString();
    //关联qml的信号到c++的槽
    cppClass cls;
    //QString参数
    //QObject::connect(viewer.rootObject(),SIGNAL(qmlSignal(QString)),&cls,SLOT(cppSlots(QString)));
    //对象+int参数
    QObject::connect(viewer.rootObject(),SIGNAL(qmlSignal(QVariant,QVariant,int,int)),&cls,SLOT(cppSlots(QVariant,QVariant,int,int)));

    return app.exec();
}
