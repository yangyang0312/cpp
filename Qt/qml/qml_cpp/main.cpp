#include <QGuiApplication>
#include <QQuickView>
#include <QDateTime>
#include <QQmlContext>
#include <QIcon>
#include "appdata.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    appData appdata;
    QQuickView viewer;
    //设置qml属性时设置的顺序很重要，必须是先设置属性，然后再设置qml路径，不然总是会出现再qml中使用属性时出现找不到属性的情况
    viewer.rootContext()->setContextProperty("currentDateTime",QDateTime::currentDateTime());  //设置qml属性
    viewer.rootContext()->setContextProperty("appdata",&appdata);
    viewer.setIcon(QIcon(":/保存.png"));                                  //图标
    viewer.setTitle("qml_c++嵌入");                                       //标题
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);              //resize
    viewer.setSource(QUrl("qrc:/main.qml"));                             //qml
    viewer.show();

    return app.exec();
}
