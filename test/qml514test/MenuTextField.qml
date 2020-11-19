import QtQuick 2.0
import QtQuick.Controls 2.12

//TextInput {
//    id:ss
//}

TextField {
    id: textField
    selectByMouse: true // 当前重要属性
    persistentSelection: true   // 当前重要属性
    onPressAndHold: menu.popup();
    //onSelectedTextChanged: menu.popup();

    onReleased: {
        if (textField.selectedText.length > 0) {
            menu.popup();
        }
    }

    Menu {
        id: menu
//        onAboutToHide: {
//            textField.deselect();
//        }

        MenuItem {
            text: "剪切"
          //shortcut: "Ctrl+X"
            enabled: textField.selectedText.length
            onTriggered: {
                textField.cut()
            }
        }

        MenuItem {
            text: "复制"
            //shortcut: "Ctrl+C"
            enabled: textField.selectedText.length
            onTriggered: {
                textField.copy();
            }
        }

        MenuItem {
            text: "粘贴"
            //shortcut: "Ctrl+V"
            enabled: textField.canPaste
            onTriggered: {
                textField.paste();
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
