import QtQuick 2.0

Rectangle {
    id: root
    width: 360; height: 360
    anchors.centerIn: parent
    color: "#3C3C3C"
    Canvas {
        id: canvas
        width: 300; height: 300
        anchors.centerIn: parent
        onPaint: {
            // get the drawing context
            var ctx = canvas.getContext('2d')
            // create a rectangle path
            ctx.rect(50, 50, 200, 200)
            // setup fill color
            ctx.fillStyle = "#FFF0A5"
            // fill path
            ctx.fill()
            // setup line width and stroke color
            ctx.lineWidth = 4
            ctx.strokeStyle = "#468966"
            // stroke path
            ctx.stroke()
        }
    }
}

