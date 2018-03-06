import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


Rectangle
{
	width:640
	height:480
	color: "lightgray"
	Rectangle
	{
		id:rect
		width:parent.width/3
		height: parent.height/3
		//不能拖拽设置了anchors的控件
		//anchors.horizontalCenter: parent.horizontalCenter
		//anchors.verticalCenter: parent.verticalCenter
		color: "red"
		focus: true
		MouseArea
		{
			anchors.fill: parent
			//允许、按下、包含鼠标、报告鼠标位置等改变的消息
			enabled: true
			//read only property
			//pressed
			//containsMouse:
			hoverEnabled: true
			//接收的鼠标事件，默认似乎是鼠标左键
			acceptedButtons: Qt.LeftButton | Qt.MidButton | Qt.RightButton
			//鼠标事件改变颜色
			onClicked:
			{
				if(mouse.button == Qt.LeftButton)
					parent.color = "green"
				else if(mouse.button == Qt.RightButton)
					parent.color = "blue"
				//control + 鼠标中键
				else if(mouse.modifiers == Qt.ControlModifier && mouse.button == Qt.MidButton)
					parent.color = "red"
			}
			//拖拽 不能拖拽设置了anchors的控件
			drag
			{
				target:rect
				axis:Drag.XAndYAxis
			}
		}
		//键盘事件
		Keys.onPressed:
		{
			//Ctrl + A
			if(event.modifiers == Qt.ControlModifier && event.key == Qt.Key_A)
			{
				console.log("Ctrl + A pressed.")
				//接受事件，不再继续传递
				event.accepted = true
			}
		}
	}
	//按键处理，KeyNavigation导航界面，2*2棋盘格子切换
	Grid
	{
		anchors.centerIn: parent
		columns: 2
		spacing: 5
		Block
		{
			id:topLeft
			text:"1"
			KeyNavigation.right: topRight
			KeyNavigation.down: bottomLeft
		}
		Block
		{
			id:topRight
			text:"2"
			KeyNavigation.left: topLeft
			KeyNavigation.down: bottomRight
		}
		Block
		{
			id:bottomLeft
			text:"3"
			KeyNavigation.right: bottomRight
			KeyNavigation.up:topLeft
		}
		Block
		{
			id:bottomRight
			text:"4"
			KeyNavigation.left: bottomLeft
			KeyNavigation.up: topRight
		}
	}
	Column
	{
		anchors.horizontalCenter: parent.horizontalCenter
		//用activeFocus判断是否已经有焦点
		Text
		{
			text:"I" + (activeFocus ? "" : " do not") + " have focus."
			MouseArea
			{
				anchors.fill: parent
				onClicked: parent.focus = true
			}
		}
		//定时器
		Text
		{
			Timer
			{
				//时间、运行、重复、槽
				interval: 200
				running: true
				repeat: true
				onTriggered: parent.text = Date().toString()
			}
			font{family: "微软雅黑";pointSize: 15}
		}
		Item
		{
			//Loader动态加载控件
			width:100
			height:100
			Loader{id:loader}
			MouseArea
			{
				anchors.fill: parent
				onClicked: loader.source="Block.qml"
			}
		}
	}
}
