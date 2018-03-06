import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
Rectangle
{
    property int value: 258
    Text
    {
        id: text
        anchors.centerIn: parent
        text: "Hello World."
        font.family: "微软雅黑"
        font.pointSize: 25
    }
    function myQmlFunc(msg)
    {
        console.log("myQmlFunc " + msg)
        return "myQmlFunc " + msg;
    }
    //qml信号及发送信号代码
    //signal qmlSignal(string str)
    signal qmlSignal(var obj,var text,int x,int y)
    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        //鼠标点击
        onClicked:
        {
            //QString类型参数
            //parent.qmlSignal("qmlSignal:clicked x:" + mouse.x + " y:" + mouse.y)
            //对象+int参数
            parent.qmlSignal(parent,text,mouse.x,mouse.y)
        }
    }
    //高度改变
    onHeightChanged:
    {
        qmlSignal(this,text,mouseArea.mouseX,mouseArea.mouseY)
    }
    //宽度改变
    onWidthChanged:
    {
        qmlSignal(this,text,mouseArea.mouseX,mouseArea.mouseY)
    }
}
