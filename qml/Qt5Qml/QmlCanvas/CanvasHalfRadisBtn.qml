import QtQuick 2.0

// 真心难用！

Rectangle {
    id: root
    width: 100;
    height: 50
    //color: "#3C3C3C"
    //color: "#468966"
    Canvas {
        property int nLineWidth: 4

        z: 2
        id: canvasRect
        anchors.fill: parent
        anchors.margins: nLineWidth
        onPaint: {
            var ctx = canvasRect.getContext('2d')
            var nWidth = width// - nLineWidth * 2
            var nHeight = height// - nLineWidth * 2
            var radiusR = Math.min(nWidth, nHeight) / 2

            //ctx.clearRect(0, 0, width, height)
            ctx.fillStyle = "#77AFE6";
            ctx.strokeStyle = "red"
            ctx.lineWidth = 3
            //ctx.beginPath();
            ctx.moveTo(radiusR,nHeight)
            ctx.arc(radiusR, radiusR, radiusR, Math.PI / 2, Math.PI * 3 / 2); //context.arc(x, y, radius, startAngle, endAngle, anticlockwise)
            //ctx.moveTo(radiusR,0)
            ctx.lineTo(nWidth,0)
            ctx.lineTo(nWidth,nHeight)
            ctx.lineTo(radiusR,nHeight)
            ctx.closePath();
            ctx.stroke()
            ctx.fill()
        }
        function drawHalfBtn1() {
            var ctx = canvasRect.getContext('2d')
            ctx.clearRect(0, 0, width, height)
            ctx.moveTo(10, 50)
            ctx.arcTo(0,50,0,40,10)
            ctx.lineTo(0,10)
            ctx.arcTo(0,0,10,0,10)
            ctx.lineTo(100,0)
            ctx.lineTo(100,50)
            ctx.lineTo(10,50)
            ctx.lineWidth = 4
            ctx.strokeStyle = "#468966"
            ctx.stroke() //用笔画
        }

        function drawRect() {
            // get the drawing context
            var ctx = canvasRect.getContext('2d')
            ctx.clearRect(0, 0, width, height)
            //
            //ctx.moveTo(25, 25)
            //ctx.arcTo(0,0,0,50,25) //点1，点2，圆弧半径
            //test2
            //ctx.moveTo(90, 0) //点0
            //ctx.arcTo(100,0,100,10,10) //点1，点2，圆弧半径
            //ctx.arc(canvasRect.width/2, canvasRect.height/2, canvasRect.width/2, 0, Math.PI * 2, true);
            //ctx.stroke() //用笔画
            // create a rectangle path
            ctx.rect(0, 0, 100, 50)
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





