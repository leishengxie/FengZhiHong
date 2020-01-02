import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 800
        height: 480
    visible: true
        color: "lightblue"

        Column {
            anchors.centerIn: parent
            ChartTitleBar {
                height: 60
                color: "#85c5f4"
                arrayTitle: ["index", "name", "age", "height", "weight"]
                selectedWidth: [["1-1", 70*1.5], ["2-5", 70]]
            }

            ChartBar {
                height: 320
                selectedWidthBar: [["1-1", 70*1.5], ["2-5", 70]]
                selectedHeight: 60
                modelSomeData: listViewModel
                arrayName: ["index", "name", "age", "height", "weight"]
            }
        }

        ListModel {
            id: listViewModel

            ListElement {
                index: 1
                name: "Aaron"
                age: 22
                height: 186
                weight: 148
            }

            ListElement {
                index: 2
                name: "William"
                age: 21
                height: 178
                weight: 145
            }

            ListElement {
                index: 3
                name: "Li"
                age: 23
                height: 198
                weight: 140
            }
            ListElement {
                index: 4
                name: "mMark"
                age: 25
                height: 185
                weight: 142
            }
        }
}
