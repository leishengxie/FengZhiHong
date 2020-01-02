import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0


Rectangle {
        Rectangle{
            anchors.top:parent.top
            width: parent.width
            height:40
            id: concel
            Text{
                id:concelText
                text: qsTr("取消")
                anchors.centerIn: parent
                color: "white"
            }
            color: "#2e4aff"
            radius:5

        }

        RowLayout{
            y:50
            width:parent.width
            height: 40
            RadioButton{
                id:noUseRadio
                text:qsTr("不使用SD加密卡")
                checked:true
            }
            RadioButton{
                id:useRadio
                text:qsTr("使用SD加密卡")


            }
        }



        TextInput{
            y:100
            width: parent.width
            height: 40
            id:numberInput
            text:qsTr("密讯电话号码")

        }
        Row{
            y:150
            width: parent.width
            height: 40
            TextInput{
                id:verificationInput
                text:qsTr("验证码")
            }
            Button{
                id:verificationButton
                text:qsTr("获取验证码")
            }
        }
        Rectangle{
            y:200
            id:exit
            anchors.bottom: parent.bottom
            width: parent.width
            height: 40
            Text{
                id:exitText
                text: qsTr("退出")
                anchors.centerIn:parent
                color: "white"
            }
            color: "#2e4aff"
            MouseArea{
                anchors.fill: parent
                onClicked: Qt.quit()
            }
        }
}

