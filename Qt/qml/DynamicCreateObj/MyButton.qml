import QtQuick 2.7


Rectangle
{
    //设置btnText.text属性别名，为text，这样就能够在外部访问属性，方便编写控件模板
    property alias text: btnText.text
    width: 200
    height: 70
    color: "lightgray"
    border.color: "blue"
    border.width: 2
    radius: 12
    //定义信号
    signal clicked(int xPos,int yPos)
    Text
    {
        id: btnText
        font.family: "微软雅黑"
        font.pixelSize: 25
        color: "black"
        anchors.centerIn: parent
    }
    MouseArea
    {
        anchors.fill: parent
        //发送信号
        onClicked: parent.clicked(mouse.x,mouse.y)
    }
}
