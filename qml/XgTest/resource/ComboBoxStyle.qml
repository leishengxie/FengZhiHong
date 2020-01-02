/******************************************************************************
**
** @file
** ComboBoxStyle.qml
** @brief
** 自定义一个风格的ComboBox
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

ComboBox { //原生ComboBox
    width: 200
    height:30
    property string borderColor: "#4F4F4F"
    property int borderWidth: 0

    style: ComboBoxStyle{ //风格
        id:style
        background:Rectangle {
            id:background
            width: control.width - borderWidth
            height: control.height - borderWidth
            border.color: borderColor
            border.width: borderWidth
            Image { //三角
                id: imageDropdown
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                source: "images/drop.png"
            }
        }

        label: Text {
            id: text1
            text:control.currentText
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 20
        }
    }
}


