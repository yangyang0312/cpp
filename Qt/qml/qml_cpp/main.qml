import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Rectangle
{
    visible: true
    width: 600
    height: 400
    Text
    {
        id: text
        anchors.centerIn: parent
        text: currentDateTime           //使用c++中添加的属性
        font.family: "微软雅黑"
        font.pointSize: 45
    }
    //方法一：直接响应c++设置的属性的信号
    //Connections
    //{
    //    target: appdata
    //    onTimerChanged:             //直接响应c++代码中的信号
    //    {
    //        text.text = appdata.getCurrentTime()
    //        color = Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
    //    }
    //}
    //方法二：在加载完成时手动链接c++设置的属性的信号到qml的一个函数
    Component.onCompleted:
    {
        appdata.timerChanged.connect(timerChanged)
    }
    function timerChanged()
    {
        text.text = appdata.getCurrentTime()
        color = Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
    }
}
