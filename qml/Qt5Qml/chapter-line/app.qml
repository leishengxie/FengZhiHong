/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
//![0]
//import Charts 1.0
import LineCharts 1.0
import QtQuick 2.0

Rectangle {
    id: opacitytest;
//    width: 720;
//    height: 1280
    width: Qt.platform.os === "android"? Screen.width: 720
    height: Qt.platform.os === "android"? Screen.height: 1280
    color: "#edf0f0"
//    property string tramShowPackageTitle: ""
    property int monthNow: 0
    property int monthCount: 0
    property int nameWidth: 0
    property int today:0
    property int todayLocation:0
    Component.onCompleted: {
        var d = new Date();
        today=d.getDate()
        monthNow = d.getMonth()+1
        //today=25
        //monthNow=4
        if(monthNow==2){
            nameWidth=120*28;
            monthCount = 28;
        }else if(monthNow==1||monthNow==3||monthNow==5||monthNow==7
                 ||monthNow==8||monthNow==10||monthNow==12){
            nameWidth=120*31;
            monthCount = 31;
        }else{
            nameWidth=120*30;
            monthCount = 30;
        }

        textListModel.clear();
        var i=1;
        for(i = 1 ; i < monthCount+1; i++)
        {
            var tct = monthNow+"-"+i;
            if(i.toString()==today.toString()){
                textListModel.append({TextContent:qsTr("Today"),TextColor:"#ffffff"});
            }else{
                textListModel.append({TextContent:tct,TextColor:"#bad4c5"});
            }
        }
        if(today<6){
            today=0;
            todayLocation=0
        }else{
          todayLocation=-((today+1)*120-720)
        }
    }

    Rectangle {
        id: name
        anchors.top:pageHeader.bottom
        x:todayLocation//此处设置初始位置
        color: "#009955"
        width: nameWidth;
        height: 530

        LineChart {
            id: lineChart
            anchors.centerIn: parent
            width: nameWidth; height: 530
            color: "white"
            //onChartCleared: console.log("The chart has been cleared")
        }
        Rectangle{
            id:rectangle
            width: lineChart.width
            height: 50;
            anchors.top: lineChart.bottom
            color: "#006633"
            ListView{
                id:lisetview
                width: parent.width; height: parent.height
                model: textListModel
                delegate: delegate
                focus: true
                orientation: ListView.Horizontal//*****注意*****//
            }
            Component {
                id: delegate
                Item {
                    id: wrapper
                    width: 120; height: 50
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.horizontalCenter:parent.horizontalCenter
                        //anchors.left:rectangle.left
                        color:TextColor
                        //x:90
                        text:TextContent
                        font.pointSize: 24;
                    }
                }
            }
            ListModel {
                id: textListModel
                ListElement {
                    TextContent: ""
                    TextColor: ""
                }
            }
        }
    }
    Text{
        anchors.top:name.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text:qsTr("Daily traffic View")
        color: "#ffffff"
        font.pointSize: 30;
    }

    MouseArea {
        anchors.fill: parent
        drag.target: name
        drag.axis: "XAxis"//XAxis//XAndYAxis//YAxis
        drag.minimumX: -(nameWidth-720)
        drag.maximumX: 0
        onClicked: {
            console.log("----------------");
            lineChart.clearChart()
        }
    }
}
//![0]
