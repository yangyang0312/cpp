//声明为无状态的库，只做计算，不能直接访问和修改qml组件
.pragma library
//js文件包含
//Qt.include("ssssss.js")

function func(n)
{
    if(n <= 1)
        return 1;
    else
        return n * func(n - 1)
}
