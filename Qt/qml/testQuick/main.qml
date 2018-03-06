import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true
    title: qsTr("Hello World")
    width: 640
    height: 480
    Item
    {
        id: item
        width: parent.width
        height: parent.height
        Keys.onReturnPressed:   //按键
        {
            console.log("return pressed.")
        }
        //信号与槽 与c++的一样，可以将信号绑定到多个信号，或者将信号绑定到多个槽 对应的有信号connct和disconnect
        signal mysignal(string msg,color color)
        function msg_recv(msg,color)
        {
            console.log("msg_recv " + msg + color)
        }
        Component.onCompleted:  //类似于html文档加载完成的消息一样
        {
            console.log("Component.onCompleted" + color)
            //链接信号与槽
            item.mysignal.connect(msg_recv)
            //发送信号
            item.mysignal("aaaaaaaaaaaaassssssss",color)
        }
        Rectangle
        {
            id: rect
            color: "gray"
            //width: parent.width
            //height: parent.height
            //属性绑定，绑定到父对象的宽度和高度
            width: Math.max(800,parent.width)
            height:
            {
                if (parent.height > 600)
                    parent.height
                else
                    parent.height / 2
            }
            Text
            {
                anchors.centerIn: parent    //居中
                text:"aaaaaaaa"
                font.family: "微软雅黑"
                font.pointSize: 30
                color: "red"
                //透明度
                opacity: 0.5
            }
            //渐变色
            //gradient: Gradient
            //{
            //    GradientStop
            //    {
            //        position: 0.0
            //        color: "yellow"
            //    }
            //    GradientStop
            //    {
            //        position: 1.0
            //        color: "green"
            //    }
            //}
            focus: true
            Keys.onSpacePressed:    //空格按下，重新定义宽度
            {
                //width = parent.width / 5                             //固定值，后续拖动宽度不会改变
                width = Qt.binding(function(){return parent.width / 5})//重新建立绑定关系，拖到后会改变,必须return
            }
        }
        Image   //图片
        {
            source: "qrc:/保存.png"
        }
        focus: true
        Keys.onSpacePressed:
        {
            rect.width = Qt.binding(function(){return width / 3})   //改变子控件的宽度
            console.log("rect.width:" + rect.width)
        }
        MouseArea
        {
            id: mouseArea
            anchors.fill: parent
        }
        //链接信号到mouseArea,处理mouseArea的鼠标按下消息
        Connections
        {
            target: mouseArea
            onClicked:
            {   //随机颜色
                rect.color = Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
                //鼠标点击位置
                console.log("click pos:" + mouse.x + " " + mouse.y)
                item.mysignal("rect color changed:",rect.color)
                //对应的有信号disconnect
                item.mysignal.disconnect(item.msg_recv)
            }
        }
        //鼠标处理
        //MouseArea
        //{
        //    anchors.fill: parent        //锚点位置，
        //    onClicked:
        //    {   //随机颜色
        //        rect.color = Qt.rgba(Math.random(),Math.random(),Math.random(),Math.random())
        //        //鼠标点击位置
        //        console.log("click pos:" + mouse.x + " " + mouse.y)
        //    }
        //    //鼠标事件
        //    onMouseXChanged:
        //    {
        //        console.log("onMouseXChanged");
        //    }
        //    onMouseYChanged:
        //    {
        //        console.log("onMouseYChanged")
        //    }
        //    onReleased:
        //    {
        //        console.log("onReleased")
        //    }
        //    onDoubleClicked:
        //    {
        //        console.log("onDoubleClicked")
        //    }
        //    onWheel:
        //    {
        //        console.log("onWheel")
        //    }
        //    onPressed:
        //    {
        //        console.log("onPressed")
        //    }
        //    onEntered:
        //    {
        //        console.log("onEntered")
        //    }
        //}
    }
}
