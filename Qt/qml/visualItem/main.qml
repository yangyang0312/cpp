import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

//可视元素基类，可向它添加各种类型的元素
Item
{
	id:root
	visible: true
	width: 640
	height: 480
	//Rectangle边框、圆角、z序、定位
	Rectangle
	{
		//z序
		z:2
		width:root.width/3
		height:root.height/2
		//anchors.centerIn: parent
		anchors.horizontalCenter: parent.horizontalCenter
		//anchors.verticalCenter: parent.verticalCenter
		color:"gray"
		// 边框，圆角
		border.color: "red"
		border.width: 5
		radius: 10
	}
	Rectangle
	{
		//z序
		z:1
		width:root.width/4
		height:root.height/4
		color: "lightgreen"
		anchors.centerIn: parent
		// 边框，圆角
		border.color: "blue"
		border.width: 5
		radius: 10
		//圆滑
		smooth: true
	}
	//文本设置 文本省略、自动换行、字体、文本对齐、富文本、链接
	Column
	{
		spacing: 10
		Text
		{
			width:80
			text:"单行文本不会进行省略"
		}
		Text
		{
			width:80
			elide: Text.ElideLeft
			text:"单行文本从左边进行省略"
		}
		Text
		{
			width:80
			elide: Text.ElideRight
			text:"单行文本从右边进行省略"
		}
		Text
		{
			width:160
			wrapMode: Text.WrapAnywhere
			// 文本对齐
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			font
			{
				//加粗、大小写、字体、斜体、字母间距、大小、删除线、下划线、重量、单词间距
				bold:true
				capitalization:Font.AllUppercase
				family:"微软雅黑"
				italic:true
				letterSpacing:1
				pointSize:20
				strikeout:true
				underline:true
				weight:Font.Bold
				wordSpacing:3
			}
			text:"演示单行文本设置的自动换行 this is english"
		}
		Text
		{
			//富文本、链接
			textFormat: Text.RichText
			text:"<a href=\"https:www.baidu.com\">百度</a>"
			onLinkActivated: {console.log(link + " href actived.")}
			onLinkHovered: {console.log(link + " href hovered.")}
		}
	}
	Column
	{
		z:3
		padding: root.width/3
		//TextEdit是多行编辑控件，但是没有提供鼠标跟随、滚动等特性，使用Flickable去做这些事情
		Flickable
		{
			id: flick
			width: 300; height: 200;
			contentWidth: edit.paintedWidth
			contentHeight: edit.paintedHeight
			clip: true
			function ensureVisible(r)
			{
				if (contentX >= r.x)
					contentX = r.x;
				else if (contentX+width <= r.x+r.width)
					contentX = r.x+r.width-width;
				if (contentY >= r.y)
					contentY = r.y;
				else if (contentY+height <= r.y+r.height)
					contentY = r.y+r.height-height;
			}
			TextEdit
			{
				id: edit
				width: flick.width
				height: flick.height
				//focus: true
				wrapMode: TextEdit.Wrap
				onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
				font{family: "微软雅黑";pointSize: 20}
			}
		}
		TextInput
		{
			focus: true
			width: flick.width
			height: flick.height
			color: "black"
			//密码模式
			//echoMode: TextInput.Password
			//过滤，正则表达式
			validator: RegExpValidator{regExp: /[0-9]*/}
		}
	}
}
