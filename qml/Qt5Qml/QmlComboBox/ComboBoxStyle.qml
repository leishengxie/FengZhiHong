import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

ComboBox {
    width: 200
    height:30
    property string borderColor: "#4F4F4F"
    property int borderWidth: 0
    style: ComboBoxStyle{
        id:style
        background:Rectangle {
            id:background
            width: control.width - borderWidth
            height: control.height - borderWidth
            border.color: borderColor
            border.width: borderWidth
            Image {
                id: imageDropdown
                width: height
                height: 0.5 * parent.height
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.Stretch
                source: "images/drop.png"
            }
        }

        label: Text {
            id: text1
            height: control.height
            color: "#4f4f4f"
            text:control.currentText
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 36
        }
    }
}


