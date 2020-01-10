import QtQuick 2.4
import QtQuick.Layouts 1.3
import "./button"
import "./com_input"


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
            height: 50
            color: "lightgray"
            Layout.fillWidth: true
//            RowLayout {
//                anchors.horizontalCenter: parent.horizontalCenter
//                spacing: 10
//                anchors.verticalCenter: parent.verticalCenter

//                LineInput{
//                    id: lineInputSearch
//                    text: qsTr("")
//                    placeholderText: "请输入搜索内容"
//                }
//            }
        }


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
            clip: true


        }

        Rectangle {
            height: 50
            color: "lightgray"
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
                    font.pixelSize: 28
                }

                MouseArea {
                    id: mouseAreaAdd
                    anchors.fill: parent
                }
            }
        }


    }
}
