import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Rectangle
{
    id:root
	width:640
	height:480
    color:"lightgray"
	//状态
    Rectangle
    {
        id:rect
        width:200
        height: 200
        //anchors.centerIn: parent
        color: "blue"
        Text
        {
            anchors.centerIn: parent
            text:"状态"
            font{family: "微软雅黑";pointSize: 20}
        }
        MouseArea
        {
            id:mouseArea
            anchors.fill: parent
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            onClicked:
            {
                //改变对象的状态
                if(mouse.button == Qt.RightButton)
                    rect.state = "moved"
                else
                    rect.state = "clicked"
            }
        }
        states:
        [
            State
            {
                //点击状态
                name: "clicked"
                //when属性，当处于某种状态时自动调用
                when:mouseArea.pressed
                PropertyChanges
                {
                    target: rect
                    width:100
                    height:100
                }
                PropertyChanges
                {
                    target: root
                    color:"gray"
                }
            },
            State
            {
                //移动状态
                name:"moved"
                //状态改变时可以改变多个对象的的属性
                PropertyChanges
                {
                    target:rect
                    x:100
                    y:100
                }
                PropertyChanges
                {
                    target: root
                    color:"lightblue"
                }
            }
        ]
    }
	//属性动画
    Rectangle
    {
        width:parent.width/5
        height: parent.height/5
        color:"red"
        Text
        {
            anchors.centerIn: parent
            text:"属性动画"
            font{family: "微软雅黑";pointSize: 20}
        }
        //属性动画
        PropertyAnimation on x
        {
            //属性目标值
            to:300
            //时间
            duration:1000
            //重复
            loops:Animation.Infinite
        }
        PropertyAnimation on y
        {
            to:300
            duration:2000
            loops:Animation.Infinite
        }
        PropertyAnimation on opacity
        {
            to:0.05
            duration:3000
            loops:Animation.Infinite
        }
        PropertyAnimation on scale
        {
            to:0.05
            duration:4000
            loops:Animation.Infinite
        }
    }
	//行为动画
    Rectangle
    {
        x:300
        y:300
        width:parent.width/5
        height: parent.height/5
        color: "green"
        //行为动画，当属性改变时触发动画
        Text
        {
            anchors.centerIn: parent
            text:"行为动画"
            font{family: "微软雅黑";pointSize: 20}
        }
		Behavior on x{PropertyAnimation{duration: 1000;easing.type: Easing.OutElastic}}
		Behavior on y{PropertyAnimation{duration: 1000;easing.type: Easing.OutElastic}}
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                parent.x = mouse.x
                parent.y = mouse.y
            }
        }
    }
	//槽中的动画
    Rectangle
    {
        id:rect1
        x:200
        y:200
        width:parent.width/5
        height: parent.height/5
        color: "lightblue"
        Text
        {
            anchors.centerIn: parent
            text:"槽触发的动画"
            font{family: "微软雅黑";pointSize: 20}
        }
        //槽中的动画
        MouseArea
        {
            anchors.fill: rect1
            onClicked: PropertyAnimation{target: rect1;properties: "x,y";to:350;duration: 3000}
        }
    }
	//独立动画
    Rectangle
    {
        id:rect2
        x:100
        y:200
        width:parent.width/5
        height: parent.height/5
        color: "yellow"
        Text
        {
            anchors.centerIn: parent
            text:"独立动画"
            font{family: "微软雅黑";pointSize: 20}
        }
        //独立动画
        PropertyAnimation
        {
            id:animate
            properties: "x,y"
            duration: 3000
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                //设置独立动画的属性
                animate.target = rect2
                animate.to = 500
                //启动动画
                animate.running = true
            }
        }
    }
	//切换
    Rectangle
    {
        id:rect3
        x:200
        y:100
        width:parent.width/5
        height: parent.height/5
        color: "pink"
        Text
        {
            anchors.centerIn: parent
            text:"切换"
            font{family: "微软雅黑";pointSize: 20}
        }
        //切换
        states: State
        {
            name: "moved"
            PropertyChanges {target: rect3;x:100;y:450}
        }
		//所有PropertyAnimation动画都可以设置easing属性来控制动画，具有反弹、缓冲、曲线、加速、减速等多种效果
		transitions: Transition {PropertyAnimation{properties: "x,y";duration: 5000;easing.type: Easing.OutElastic}}
        MouseArea
        {
            anchors.fill: parent
            onClicked:rect3.state = "moved"
        }
    }
	//属性动画元素
    Rectangle
    {
        id:rect4
        x:400
        y:150
        width:parent.width/5
        height: parent.height/5
        color: "pink"
        Text
        {
            anchors.centerIn: parent
            text:"属性动画元素"
            font{family: "微软雅黑";pointSize: 20}
        }
        //属性动画元素，包括NumberAnimation,ColorAnimation,RotationAnimation,Vector3dAnimation,SmoothedAnimation(平滑过渡的动画)，SpringAnimation(像弹簧一样Q弹的动画),
        //ParentAnimation(父对象改变时产生动画),AnchorAnimation(锚改变时产生动画), PathAnimation(路径动画)等，这些动画对指定类型的动画有优化
        ColorAnimation on color
        {
            to: "lightgreen"
            duration: 10000
        }
        RotationAnimation on rotation
        {
            from:75
            to:1154
            duration:10000
        }
    }
	//属性动画元素 Q弹
    Rectangle
    {
        id:rect5
        x:150
        y:400
        width:parent.width/5
        height: parent.height/5
        color: "pink"
        Text
        {
            anchors.centerIn: parent
            text:"属性动画元素 Q弹"
            font{family: "微软雅黑";pointSize: 20}
        }
        //属性动画元素 Q弹 弹簧一样的
        Behavior on x{SpringAnimation{spring: 5; damping: 0.2}}
        Behavior on y{SpringAnimation{spring: 5; damping: 0.2}}
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                rect5.x = mouse.x - rect5.width/2
                rect5.y = mouse.y - rect5.height/2
            }
        }
    }
	//组合动画可以用ParallelAnimation(动画同时运行)或SequentialAnimation(动画一个接一个的运行)
	Image
	{
		id:img
		x:350
		y:400
		source: "qrc:/保存.png"
		Text
		{
			anchors.centerIn: parent
			text:"组合动画"
			font{family: "微软雅黑";pointSize: 20}
		}
		//SequentialAnimation组合动画，动画顺序执行
		//SequentialAnimation on y
		//{
		//	loops:Animation.Infinite
		//	NumberAnimation{to:100;easing.type: Easing.OutBounce;duration: 2000}
		//	PauseAnimation {duration: 200}
		//	NumberAnimation{to:400;easing.type: Easing.OutElastic;duration: 2000}
		//}
		//SequentialAnimation和ParallelAnimation组合的组合动画
		SequentialAnimation
		{
			running: true
            loops:Animation.Infinite
            //ParallelAnimation组合动画
			ParallelAnimation
            {
				NumberAnimation{target:img;to:100;easing.type: Easing.OutBounce;duration: 1000;properties: "x"}
				NumberAnimation{target:img;to:400;easing.type: Easing.OutElastic;duration: 2000;properties: "y"}
			}
			ParallelAnimation
            {
				NumberAnimation{target:img;to:400;easing.type: Easing.OutBounce;duration: 2000;properties: "x"}
				NumberAnimation{target:img;to:100;easing.type: Easing.OutElastic;duration: 1000;properties: "y"}
			}
        }
    }
}
