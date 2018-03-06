import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
//使用线性、锥形、径向渐变等需要包含
import QtGraphicalEffects 1.0

Rectangle
{
	id:root
	visible: true
	width: 640
	height: 480
	color:"lightgray"
	//图片
	Image
	{
		z:2
		width:300
		height:300
		anchors.bottom: parent.bottom
		anchors.right: parent.right
		source: "qrc:/关于.png"
		//填充方式 平铺
		fillMode: Image.Tile
	}
	//加载网络资源
	Image
	{
		z:1
		anchors.fill: parent
		scale: 0.5
		source: "http://www.baidu.com/img/bd_logo1.png"
		fillMode: Image.Pad
		//加载状态
		onStatusChanged:
		{
			if(status == Image.Ready)
			{
				//加载完成后销毁
				text1.text = "加载完成"
				text1.destroy(3000)
			}
			else if(status == Image.Loading)
				text1.text = "正在加载"
		}
		Text
		{
			id:text1
			anchors.centerIn: parent
			font{family: "微软雅黑";pointSize: 40}
		}
	}
	//边界图片，分区域缩放
	BorderImage
	{
		anchors.bottom: parent.bottom
		width: parent.height/3; height: parent.height/3
		border{left:30;top:30;right:30;bottom: 30}
		source: "qrc:/关机.png"
		horizontalTileMode: BorderImage.Stretch
		verticalTileMode: BorderImage.Stretch
	}
	//动态图片 gif等
	AnimatedImage
	{
		anchors.verticalCenter: parent.verticalCenter
		//缩放远点，取值为Center、Top、BottomLeft等
		transformOrigin: "Center"
		//缩放，大于1放大，小于1缩小，为负数的时候镜像显示，继承自Item的元素都有这个属性
		scale: -1
		//旋转角度，继承自Item的元素都有这个属性
		rotation: 45
		source: "qrc:/gif.gif"
		//平移
		transform: Translate{y:50;x:100}
	}
	//各种渐变
	Row
	{
		z:3
		anchors.top:parent.top
		anchors.topMargin: 20
		anchors.left: parent.left
		anchors.leftMargin: 20
		spacing: 20
		//一般的渐变，垂直方向
		Rectangle
		{
			width:root.width/8
			height:root.width/8
			gradient: Gradient
			{
				GradientStop
				{
				position: 0.02;
				color: "#c0db0e";
				}
				GradientStop
				{
					position: 1.00;
					color: "#db16c1";
				}
			}
		}
		//线性渐变
		LinearGradient
		{
			width:root.width/8
			height:root.width/8
			gradient: Gradient
			{
				GradientStop{position:0.0;color:"blue"}
				GradientStop{position:0.45;color:"green"}
				GradientStop{position:1.0;color:"red"}
			}
			//相对位置
			start:Qt.point(0,0)
			end:Qt.point(root.width/6,root.width/6)
		}
		//线性渐变 source
		LinearGradient
		{
			source: Image {source: "qrc:/关于.png"}
			width:root.width/8
			height:root.width/8
			gradient: Gradient
			{
				GradientStop{position:0.0;color:"blue"}
				GradientStop{position:0.45;color:"green"}
				GradientStop{position:1.0;color:"red"}
			}
			start:Qt.point(0,0)
			end:Qt.point(root.width/6,root.width/6)
		}
		//锥形渐变
		ConicalGradient
		{
			width:root.width/8
			height:root.width/8
			//角度
			angle:55
			gradient: Gradient
			{
				GradientStop{position:0.0;color:"blue"}
				GradientStop{position:1.0;color:"red"}
			}
			horizontalOffset: -10
			verticalOffset: -10
		}
		//source
		ConicalGradient
		{
			source: Image {source: "qrc:/关于.png"}
			width:root.width/8
			height:root.width/8
			//角度
			angle:55
			gradient: Gradient
			{
				GradientStop{position:0.0;color:"blue"}
				GradientStop{position:0.45;color:"green"}
				GradientStop{position:1.0;color:"red"}
			}
		}
		//径向渐变
		RadialGradient
		{
			width:root.width/8
			height:root.width/8
			gradient: Gradient
			{
				GradientStop{position:0.0;color:"blue"}
				GradientStop{position:0.45;color:"green"}
				GradientStop{position:1.0;color:"red"}
			}
			horizontalOffset: -10
			verticalOffset: -10
			angle:55
		}
		RadialGradient
		{
			source: Image {source: "qrc:/关于.png"}
			width:root.width/8
			height:root.width/8
			gradient: Gradient
			{
				GradientStop{position:0.0;color:"red"}
				GradientStop{position:0.2;color:"green"}
				GradientStop{position:0.4;color:"blue"}
				GradientStop{position:0.6;color:"yellow"}
				GradientStop{position:0.8;color:"gray"}
				GradientStop{position:1.0;color:"pink"}
			}
		}
	}
}
