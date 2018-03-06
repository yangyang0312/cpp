import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
//导入分离js文件  MyJsFunc首字母必须大写
import "myJsFunc.js" as MyJsFunc

Rectangle
{
    id:rect
    visible: true
    width: 800
    height: 600
    Column
    {
		id:colume
        anchors.centerIn: parent
        spacing: 10
        //添加qml文件，但是注意的是文件名必须是大写，这是QT规定的，然后就可以在其他qml文件中使用了，不需要包含文件
        MyButton{text:"button1"}
        MyButton{text:"button2"}
        MyButton
        {
            text:"button3"
            //MyButton clicked信号对应的槽函数
            //这里不用写参数 xPos yPos
            onClicked:
            {
                console.log(text + " clicked at " + xPos + " " + yPos)
                //销毁对象
                destroy(5000)
            }
        }
        //动态创建组件
        Component.onCompleted:
        {
            //槽函数
            function fun(xPos,yPos)
            {
                console.log("clicked at " + xPos + " " + yPos)
            }
            //创建组件
            var component = Qt.createComponent("MyButton.qml")
            for(var i = 0;i < 3;++i)
            {
                //创建对象
                var sprite = component.createObject(colume,{text:"动态MyButton" + i})
                //链接信号和槽
                sprite.clicked.connect(fun)
                //动态销毁对象
                sprite.destroy(5000 * (i + 1))
            }
        }
    }
    //内联js函数
    function func(n)
    {
        if(n <= 1)
            return 1;
        else
            return n * func(n - 1)
    }
    //使用内联js函数
    //Component.onCompleted: console.log(func(5))
    //使用分离的js文件中的函数
    //启动时触发
    Component.onCompleted:console.log(MyJsFunc.func(6))
    //组件销毁时触发
	Component.onDestruction: console.log(MyJsFunc.func(5))
}
