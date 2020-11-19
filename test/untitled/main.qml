import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
//import Qt.labs.platform 1.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    //    TextInput {
    //        id: textInput1
    //        x: 145
    //        y: 221
    //        width: 80
    //        height: 20

    //        text: qsTr("Text Input")
    //        font.pixelSize: 12
    //        selectByMouse: true

    //        //TextInput是通过pressed事件来获取焦点的
    //        //ComboBox的弹窗也是通过pressed事件出发触发
    //        MouseArea {
    //            id: mouseArea
    //            anchors.fill: parent
    //            //propagateComposedEvents: true

    //            //onClicked: mouse.accepted = false
    //            onPressed: mouse.accepted = false
    //            onPressAndHold: Qt.quit();
    //        }
    //    }

//    TextInput {
//        id: textInput
//        text: "Hello world!"
//        width: 200;
//        height: 20;
//        //activeFocusOnPress: false
//        selectionColor: "#00FF00"
//        selectByMouse: true
//        //echoMode: TextInput.Password
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                if (!textInput.activeFocus) {
//                    textInput.forceActiveFocus()
//                    //textInput.openSoftwareInputPanel();
//                } else {
//                    textInput.focus = false;
//                }
//            }
////            onPressed: {
////                if (!textInput.activeFocus) {
////                    textInput.forceActiveFocus()
////                    //textInput.openSoftwareInputPanel();
////                } else {
////                    textInput.focus = false;
////                }
////            }
//            //onPressed: {
//               // mouse.accepted = mouse.wasHeld
//            //}
//            //onPressAndHold: textInput.closeSoftwareInputPanel();
//            //onPressAndHold: option_menu.popup();
//        }

//        Menu {
//            id: option_menu
//            MenuItem {
//                text: "剪切"
//                //shortcut: "Ctrl+X"
//                enabled: textInput.selectedText.length
//                onTriggered: {}
//            }

//            MenuItem {
//                text: "复制"
//                //shortcut: "Ctrl+C"
//                enabled: textInput.selectedText.length
//                onTriggered: {}
//            }

//            MenuItem {
//                text: "粘贴"
//                //shortcut: "Ctrl+V"
//                enabled: textInput.canPaste
//                onTriggered: {
//                    textInput.paste();
//                }
//            }

//            MenuSeparator { }

//            Menu {
//                title: "More Stuff"

//                MenuItem {
//                    text: "Do Nothing"
//                }
//            }
//        }

//    }

    TextField {
        id: textInput
        text: "Hello world!"
        selectByMouse: true

        onPressAndHold: option_menu.popup();


        Menu {
            id: option_menu
            MenuItem {
                text: "剪切"
                //shortcut: StandardKey.Cut
                enabled: textInput.selectedText.length
                onTriggered: {}
            }

            MenuItem {
                text: "复制"
                //shortcut: StandardKey.Copy
                enabled: textInput.selectedText.length
                onTriggered: {}
            }

            MenuItem {
                text: "粘贴"
                //shortcut: StandardKey.Paste
                enabled: textInput.canPaste
                onTriggered: {
                    textInput.paste();
                }
            }

            MenuSeparator { }

            Menu {
                title: "More Stuff"

                MenuItem {
                    text: "Do Nothing"
                }
            }
        }
    }



//    Text {
//        anchors.centerIn: parent
//        text: "Hello World"
//    }
}



