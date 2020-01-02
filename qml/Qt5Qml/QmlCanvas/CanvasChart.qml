import QtQuick 2.0

Rectangle {
    id: root
    width: 640
    height: 360
    anchors.centerIn: parent
    color: "#3C3C3C"
    //test2

    ListModel {
        id: model
        ListElement { label:"Scientific Research";
            value:21; color:"#99e600" }
        ListElement { label:"Engineering & Design";
            value:18; color:"#99cc00" }
        ListElement { label:"Automotive";
            value:14; color:"#99b300" }
        ListElement { label:"Aerospace";
            value:13; color:"#9f991a" }
        ListElement { label:"Automation & Machine Tools";
            value:13; color:"#a48033" }
        ListElement { label:"Medical & Bioinformatics";
            value:13; color:"#a9664d" }
        ListElement { label:"Imaging & Special Effects";
            value:12; color:"#ae4d66" }
        ListElement { label:"Defense";
            value:11; color:"#b33380" }
        ListElement { label:"Test & Measurement Systems";
            value:9; color:"#a64086" }
        ListElement { label:"Oil & Gas";
            value:9; color:"#994d8d" }
        ListElement { label:"Entertainment & Broadcasting";
            value:7; color:"#8d5a93" }
        ListElement { label:"Financial";
            value:6; color:"#806699" }
        ListElement { label:"Consumer Electronics";
            value:4; color:"#8073a6" }
        ListElement { label:"Other";
            value:38; color:"#8080b3" }
    }
    ListView {
        id: view
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.horizontalCenter
        anchors.right: parent.right
        anchors.margins: 16
        clip: true
        focus: true
        model: model
        delegate: Item {
            width: view.width
            height: 32
            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 2
                color: model.color
                border.color: Qt.lighter(root.color)
                //border.color: root.color
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.margins: 8
                text: model.label
                color: "#1C1C1C"
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.margins: 8
                text: model.value
                color: "#1C1C1C"
            }
            // handle mouse clicks
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentIndex = index
                }
            }
        }
        // highlight the currently selected item
        highlight: Item {
            z: 10
            width: view.currentItem.width
            height: view.currentItem.height
            Rectangle {
                anchors.fill: parent
                anchors.margins: 1
                radius: 2
                color: "transparent"
                border.width: 3
                border.color: Qt.lighter(model.get(view.currentIndex).color)
                //border.color: model.get(view.currentIndex).color
                Behavior on border.color {
                    PropertyAnimation {}
                }
            }
        }
        // request a repaint of the canvas whenever
        // the currently selected item changes
        onCurrentIndexChanged: {
            canvas.requestPaint()
        }
    }

    Canvas {
        id: canvas
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.horizontalCenter
        smooth: true
        // animate the rotation
        Behavior on rotation {
            SpringAnimation { spring: 1; damping: 0.2 }
        }
        onPaint: {
            var ctx = canvas.getContext('2d')
            ctx.clearRect(0, 0, width, height)
            var centerX = width / 2
            var centerY = height / 2
            var radius = 0.9 * Math.min(width, height) / 2
            var radiusFactor = 1.0
            var startAngle = 0.0
            var endAngle = 0.0
            var angleFactor = 2 * Math.PI / modelSum()
            ctx.lineWidth = 2
            ctx.strokeStyle = Qt.lighter(root.color)
            for (var index = 0; index < model.count; index++) {
                startAngle = endAngle
                endAngle = startAngle + model.get(index).value * angleFactor
                // scale the currently selected piece and
                // rotate the canvas element accordingly
                if (index == view.currentIndex) {
                    radiusFactor = 1.02
                    canvas.rotation = - 180 / Math.PI * (startAngle +
                                                         (endAngle - startAngle) / 2)
                } else {
                    radiusFactor = 1.0
                }
                ctx.fillStyle = model.get(index).color
                ctx.beginPath()
                ctx.moveTo(centerX, centerY)
                ctx.arc(centerX, centerY, radius * radiusFactor,
                        startAngle, endAngle, false)
                ctx.lineTo(centerX, centerY)
                ctx.fill()
                ctx.stroke()
            }
            // overlay a radial gradient
            var gradient = ctx.createRadialGradient(centerX, centerY,
                                                    0, centerX, centerY, radius)
            gradient.addColorStop(0.0, Qt.rgba(1.0, 1.0, 1.0, 0.0))
            gradient.addColorStop(1.0, Qt.rgba(0.0, 0.0, 0.0, 0.3))
            ctx.beginPath()
            ctx.moveTo(centerX, centerY)
            ctx.arc(centerX, centerY, radius, 0, 2 * Math.PI, false)
            ctx.fillStyle = gradient
            ctx.fill()
        }
        function modelSum() {
            var modelSum = 0
            for (var index = 0; index < model.count; index++) {
                modelSum += model.get(index).value
            }
            return modelSum
        }
    }

}

