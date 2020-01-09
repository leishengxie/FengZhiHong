import QtQuick 2.4
import "button"
import QtQuick.Layouts 1.3

// Rectangle继承Item
Rectangle {
    id: rectDairyList
    width: 240
    height: 400
    property alias mouseAreaAdd: mouseAreaAdd

    // 此句会出现错误
    //property alias mouseAreaListItem: mouseAreaListItem
    property alias listViewDairyList: listViewDairyList

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: rectangle3
            height: 50
            color: "#ffffff"
            Layout.fillWidth: true

            TextInput {
                id: textInput1
                width: 80
                height: 20
                text: qsTr("")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
            }
        }

//        ListModel {
//            id: modelTest
//             ListElement {
//                 title: "Bill Smith"
//                 date: "555 3264"
//             }
//             ListElement {
//                 title: "John Brown"
//                 date: "555 8426"
//             }
//             ListElement {
//                 title: "Sam Wise"
//                 date: "555 0473"
//             }
//         }

        ListView {
            id: listViewDairyList
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: dairyListModel
            highlight: Rectangle {
                color:"lightsteelblue";
                radius:5
            }
            highlightFollowsCurrentItem: false

            //highlightRangeMode: ListView.StrictlyEnforceRange

            focus: true;
            spacing: 4


        }

        Rectangle {
            id: rectangle2
            height: 50
            color: "#ffffff"
            Layout.fillWidth: true

            Rectangle {
                id: rectangle1
                width: 30
                color: "#ffffff"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    id: textAdd
                    text: qsTr("+")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 16
                }

                MouseArea {
                    id: mouseAreaAdd
                    anchors.fill: parent
                }
            }
        }


    }
}
