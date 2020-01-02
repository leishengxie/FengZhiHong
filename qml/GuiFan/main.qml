import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

//import QtQuick 2.2
//import QtQuick.Window 2.2
//import QtQuick.Controls 1.1

import guifan.qt.qQmlManger 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    //Rectangle {
    //    visible: true
    //    width: 360
    //    height: 360
    //    id:rect

    signal skin

    //anchor.margins来指定四个相同的边距
    //leftMargin、rightMargin、topMargin和bottomMargin来独立指定锚边距
    Row {
        id: myContent
        objectName:"row"
        anchors.fill: parent

        RectSysBtn {
            id:rectBtnSkin
            x:0
            picHover: "image/image/skin_hover.png"
            picNormal: "image/image/skin_normal.png"
            picPressed: "image/image/skin_pressed.png"
            onClicked: {
                console.log("skin btn clicked")
            }
        }

        QQmlManger {
            id:qmlManger
            objectName:"manger"
        }

        EditPhone
        {

        }

        RectAnim
        {

        }

        PathViewL
        {

        }

        RectEarth{

        }

//        FenceButton
//        {
//        }

        RectToolBtn
        {
            id:rectBtnTool
            objectName: "btnT"
            //RectLabelBtn.left:rectBtnSkin.right
            index:5
            picSrc: "image/image/ico_expert.png"
            btnText:"电脑专家"
            //onClicked:toolbar.current=btnIndex
        }

        Button
        {
            //signal clicked(int btnIndex)
            //property int index:5
            id:btnTool

            //RectLabelBtn.left:rectBtnTool.right
            text: "click me"
            onClicked:
            {
                qmlManger.onTool(QQmlManger.LB_SET);
            }

            //clicked:index
        }
    }


}
