import QtQuick 2.0
import QtQuick.Window 2.1

/**灯箱效果，禁止操作下层的对象*/
Rectangle {
    id:maskRec
    //anchors.fill: getRoot(this)
    color: 'lightgrey'
    opacity: 0.5
    z:99
    visible: false
    MouseArea{
        anchors.fill: parent;
        onPressed:{
             mouse.accepted = true
            console.log("click");
            maskRec.visible = false;
        }
    }

    function getRoot(item)
    {
        return (item.parent !== null) ? getRoot(item.parent) : item;
    }


    Component.onCompleted: {
        this.parent = getRoot(this);
        this.anchors.fill = parent;
    }
}
