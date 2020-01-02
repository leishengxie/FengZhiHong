import QtQuick 2.0

Rectangle
{
    id: rectTabHeader
    color: "transparent"

    function currentChanged(curIndex)
    {

    }

    Row
    {
        id: toolbar
        spacing: 6
        anchors.fill: parent
        property int current: 0
        onCurrentChanged:setCurrentToolBtn()

        function setCurrentToolBtn()
        {
            for(var i = 0; i < toolbar.children.length; i++)
            {
                toolbar.children[i].state = (toolbar.current == i ? 'checked' : 'leave')
            }
            rectTabHeader.currentChanged(toolbar.current)
        }

        RectRadisBtn
        {
            index:0
            state:"checked"
            btnText:"酒卡点单"
            onClicked:toolbar.current=btnIndex
        }
        RectRadisBtn
        {
            index:1
            btnText:"套餐"
            onClicked:toolbar.current=btnIndex
        }
        RectRadisBtn
        {
            index:2
            btnText:"删除"
            onClicked:toolbar.current=btnIndex
        }
        RectRadisBtn
        {
            index:3
            btnText:"数量"
            onClicked:toolbar.current=btnIndex
        }
        RectRadisBtn
        {
            index:4
            btnText:"特殊需求"
            onClicked:toolbar.current=btnIndex
        }
        RectRadisBtn
        {
            index:5
            btnText:"落单"
            onClicked:toolbar.current=btnIndex
        }
    }
}

