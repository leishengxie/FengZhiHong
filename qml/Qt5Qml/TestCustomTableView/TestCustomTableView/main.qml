import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Test Custom TableView")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    ListModel
    {
        id: tableModel

        ListElement
        {
            checked: false
            color: "blue"
        }

        ListElement
        {
            checked: true
            color: "green"
        }

        ListElement
        {
            checked: false
            color: "red"
        }
    }

    TableView
    {
        id: tableView
        anchors.fill: parent
        model: tableModel

        TableViewColumn
        {
            id: checkedColumn
            role: "checked"
            title: qsTr( "Checked" )
        }

        TableViewColumn
        {
            role: "color"
            title: qsTr( "Color" )
        }

        itemDelegate: Item
        {
            CheckBox
            {
                anchors.centerIn: parent
                checked: styleData.value
                visible: isCheckColumn( styleData.column )
            }

            Text
            {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text: styleData.value
                color: isCheckColumn( styleData.column )? "black": styleData.value
                visible: !isCheckColumn( styleData.column )
            }

            function isCheckColumn( columnIndex )
            {
                return tableView.getColumn( columnIndex ) === checkedColumn
            }
        }
    }

    Text
    {
        text: qsTr( "Made by jiangcaiyang" )
        color: "white"
        style: Text.Outline
        styleColor: "black"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
