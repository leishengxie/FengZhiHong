import QtQuick 2.0
import QtQuick.Controls 2.12

/*******
  *
    模拟Android程序复制、剪切、粘贴菜单
  */

TextArea {
    id: textArea
    selectByMouse: true         // 当前重要属性
    persistentSelection: true   // 当前重要属性
    onPressAndHold: menu.popup();

    onReleased: {
        if (textArea.selectedText.length > 0) {
            menu.popup();
        }
    }

    Menu {
        id: menu
        MenuItem {
            text: "剪切"
            enabled: textArea.selectedText.length
            onTriggered: {
                textArea.cut()
            }
        }

        MenuItem {
            text: "复制"
            enabled: textArea.selectedText.length
            onTriggered: {
                textArea.copy();
            }
        }

        MenuItem {
            text: "粘贴"
            enabled: textArea.canPaste
            onTriggered: {
                textArea.paste();
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
