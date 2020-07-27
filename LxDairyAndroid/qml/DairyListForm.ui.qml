import QtQuick 2.12
import QtQuick.Layouts 1.12
import "./button"
import "./com_input"


// Rectangle继承Item
Rectangle {
    id: rectDairyList
    width: 240
    height: 400
    anchors.fill: parent
    property alias mouseAreaAdd: mouseAreaAdd

    // 此句会出现错误
    //property alias mouseAreaListItem: mouseAreaListItem

    property alias listViewDairyList: listViewDairyList

    ColumnLayout {
        id: columnMain
        anchors.fill: parent
        spacing: 0


        Rectangle {
            Layout.preferredHeight: parent.height*0.08
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
            Layout.preferredHeight: parent.height*0.08
            color: "lightgray"
            Layout.fillWidth: true

            Rectangle {
                height: parent.height*0.8
                width: height
                color: "#ffffff"
                anchors.centerIn: parent

                Text {
                    id: textAdd
                    text: qsTr("+")
                    anchors.centerIn: parent
                    font.pixelSize: parent.height*0.8
                }

                MouseArea {
                    id: mouseAreaAdd
                    anchors.fill: parent
                }
            }
        }


    }
}
