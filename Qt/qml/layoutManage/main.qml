import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    id:root
	visible: true
	width: 640
    height: 480
    title: qsTr("Layout Manage")
	color: "lightgray"

	Column
	{
		//间隔
        spacing: 10
		//竖直方向的
		Column
		{
			spacing: 5
            Rectangle{color:"red";width:40;height:40}
            Rectangle{color:"green";width:30;height:30}
            Rectangle{color:"blue";width:20;height:20}
		}
		//水平方向的
		Row
		{
			spacing: 5
            Rectangle{color:"red";width:40;height:40}
            Rectangle{color:"green";width:30;height:30}
            Rectangle{color:"blue";width:20;height:20}
		}
		//Grid
		Grid
		{
			//行数
			columns: 2
			spacing: 5
			Rectangle{color:"red";width:50;height:50}
			Rectangle{color:"green";width:40;height:40}
			Rectangle{color:"blue";width:30;height:30}
			Rectangle{color:"yellow";width:20;height:20}
            Rectangle{color:"lightgreen";width:10;height:10}
		}
        Rectangle
        {
            id:rect
            height:root.height/3
            width:root.width/2
            color:"gray"
            //Grid布局
            Grid
            {
                //左边、上边的间距
                leftPadding: 15
                topPadding: 15
                //5 x 5个格子
                columns: 5
                rows:5
                spacing: 2
                //Repeater
                Repeater
                {
                    model: 25
                    Rectangle
                    {
                        //Repeater里边是个方块
                        width: rect.width/6
                        height: rect.height/6
                        color: "lightgreen"
                        Text
                        {
                            anchors.centerIn: parent
                            //文本是 1-25
                            text:index + 1
                        }
                    }
                }
            }
        }
        //锚布局
        Rectangle
        {
            id:rect1
            width:root.width/5
            height:root.height/5
            color:"red"
            Rectangle
            {
                //水平、竖直居中
                anchors.horizontalCenter: rect1.horizontalCenter
                anchors.verticalCenter: rect1.verticalCenter
                width:rect1.width/3
                height:rect1.height/3
                color:"green"
            }
        }
	}
	//Flow，像单词堆叠一样
	Flow
	{
		anchors.fill: parent
		//从左往右
        flow: Flow.LeftToRight
		//从上到下
        //flow: Flow.TopToBottom
		spacing: 10
		Text{text:"this";font.pixelSize: 40}
		Text{text:"is";font.pixelSize: 40}
		Text{text:"a";font.pixelSize: 40}
		Text{text:"qml";font.pixelSize: 40}
		Text{text:"program";font.pixelSize: 40}
		Text{text:"to";font.pixelSize: 40}
		Text{text:"show";font.pixelSize: 40}
		Text{text:"qml";font.pixelSize: 40}
		Text{text:"layout";font.pixelSize: 40}
		Text{text:"management";font.pixelSize: 40}
        //动画效果
        move:Transition
        {
            NumberAnimation
            {
                properties: "x,y"
                //ease: "easeOutBounce"
            }
        }
    }
}
