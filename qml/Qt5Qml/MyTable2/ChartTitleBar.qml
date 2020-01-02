import QtQuick 2.0

Rectangle {
    property variant arrayTitle: []
    property variant selectedWidth: [[]]

    id: rect
    height: 50
    color: "white"

    ListView {
        id: listView
        anchors.fill: parent
        orientation: ListView.Horizontal
        interactive: false
        model: listViewModel
        delegate: listViewDelegate
    }

    ListModel { id: listViewModel }

    Component {
        id: listViewDelegate
        Rectangle {
            width: rectWidth
            height: rectHeight
            color: "#00000000"
            border.color: "#d5d5d5"
            border.width: 1

            Text {
                width: rectWidth
                height: rectHeight
                wrapMode: Text.Wrap;
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
                text: String(arrayTitle[index])
                color: "black"
                font.pixelSize: 16
            }
        }
    }

    Component.onCompleted: {
        var i
        if (selectedWidth.length !== 0) {
            var wid, i, filterString
            for (i = 0; i < selectedWidth.length; i++) {
                rect.width += (count(i) * selectedWidth[i][1])
                for (var j = 0; j < count(i); j++) {
                    listView.model.append({
                   "rectWidth": parseInt(selectedWidth[i][1]), "rectHeight": rect.height,
                                          })
                }
            }
        }
    }

    function stringToInt(value) {
        return Number(value)
    }

    function count(i) {
        return (stringToInt(selectedWidth[i][0].substring(selectedWidth[i][0].indexOf('-')+1, selectedWidth[i][0].length)) -
                stringToInt(selectedWidth[i][0].substring(0, selectedWidth[i][0].indexOf('-'))) + 1)
    }
}


