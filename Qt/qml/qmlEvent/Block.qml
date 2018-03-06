import QtQuick 2.0


Rectangle
{
	property alias text: blockText.text
	width:80;height:80
	color:focus ? "red" : "gray"
	//鼠标按下设置焦点
	MouseArea
	{
		anchors.fill: parent
		onClicked: {parent.focus = true}
	}
	Text
	{
		id:blockText
		anchors.centerIn: parent
		font.family: "微软雅黑"
		font.pixelSize: 30
	}
}
