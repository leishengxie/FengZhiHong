#include "linechart.h"
#include <QPainter>
#include <QDate>
#include <QDebug>

//               1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26 27 28 29 30 31
int traffic[31]={700,300,600,622,644,800,723,777,500,800,766,728,234,245,222,678,443,778,235,900,923,618,845,98,128,300, 0, 0, 0, 0, 0};

LineChart::LineChart(QQuickPaintedItem *parent) :
    QQuickPaintedItem(parent)
{
    //setFlag(QGraphicsItem::ItemHasNoContents, false);
    monthCount= 0;
    nameWidth= 0;
    monthNow= 0;
    topDistance=120;
}
void LineChart::paint(QPainter *painter)
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    painter->setRenderHint(QPainter::Antialiasing);//平滑直线
    monthNow= current_date_time.date().month();
    dayNow= current_date_time.date().day();
    if(monthNow==2){
        nameWidth=120*28+2;
        monthCount = 28;
    }else if(monthNow==1||monthNow==3||monthNow==5||monthNow==7
             ||monthNow==8||monthNow==10||monthNow==12){
        nameWidth=120*31+2;
        monthCount = 31;
    }else{
        nameWidth=120*30+2;
        monthCount = 30;
    }
    int i=0;
    int flag=0;
    for(;i<31;i++){
        if(flag<traffic[i]){
            flag=traffic[i];
        }
    }
    painter->translate(0,530);//设置原点位置
    QPen penLine(Qt::white,3);
    painter->setPen(penLine);
    for (int var = 0; var < dayNow; ++var) {
        if(var==0){
            painter->drawLine(0,0,60,-traffic[var]*(530-topDistance)/flag);
        }else{
            painter->drawLine((60+(var-1)*120),-traffic[var-1]*(530-topDistance)/flag,120*var+60,-traffic[var]*(530-topDistance)/flag);
        }
    }

    for (int var = 0; var < dayNow; ++var) {
        if(var==(dayNow-1)){
            QPen Endpoint(Qt::white,10);
            painter->setPen(Endpoint);
            painter->drawEllipse((60+var*120)-5,(-traffic[var]*(530-topDistance)/flag)-5,10,10);//-5
        }else{
            //009955
//            QPen Endpoint(Qt::white,3);
//            painter->setPen(Endpoint);
//            painter->drawEllipse((60+var*120)-5,(-traffic[var]*(530-topDistance)/flag)-5,10,10);//-5
//            QColor insideBrushColor0(0,153,85,25);
//            painter->setBrush(insideBrushColor0);
//            QPen penpoints0(insideBrushColor0,10);
//            painter->setPen(penpoints0);
            painter->drawEllipse((60+var*120)-5,(-traffic[var]*(530-topDistance)/flag)-5,10,10);//-5
        }
    }
    QPen Vertical(Qt::white,1);
    painter->setPen(Vertical);
    for (int var = 0; var < dayNow; ++var) {
        painter->drawLine((60+var*120),0,(60+var*120),-traffic[var]*(530-topDistance)/flag+5);
    }
    QFont notToday("white",20);
    painter->setFont(notToday);
    for (int var = 0; var < dayNow; ++var) {
        if(var==(dayNow-1)){
            QFont isToday("white",30);
            painter->setFont(isToday);
            QString flagstr="";
            painter->drawText((60+var*120-60),-traffic[var]*(530-topDistance)/flag-65,"TodayUsed");
            flagstr = QString::number(traffic[var])+"MB";
            if(traffic[var]>100){
                painter->drawText((60+var*120-55),-traffic[var]*(530-topDistance)/flag-25,flagstr);
            }else{
                painter->drawText((60+var*120-35),-traffic[var]*(530-topDistance)/flag-25,flagstr);
            }
        }else{
            QString flagstr="";
            flagstr = QString::number(traffic[var])+"MB";
            painter->drawText((60+var*120-45),-traffic[var]*(530-topDistance)/flag-25,flagstr);
        }
    }

    QColor insideBrushColor(255,255,255,25);
    QPen penpoints(insideBrushColor,0.15);
    painter->setPen(penpoints);
    painter->setBrush(insideBrushColor);
    QPointF points[31];
    points[0]=QPointF(0.0, 0.0);
    for (int var = 1; var < dayNow+1; ++var) {
            float x = (60+(var-1)*120);
            float y = (-traffic[var-1]*(530-topDistance)/flag);
            points[var]=QPointF(x, y);
    }
    points[dayNow+1]=QPointF(60+(dayNow-1)*120, 0.0);
    painter->drawConvexPolygon(points,31);

}
void LineChart::clearChart()
{
    qDebug()<<"======";
    setColor(QColor(Qt::transparent));
    update();
    emit chartCleared();
}
QColor LineChart::color() const
{
    return m_color;
}

void LineChart::setColor(const QColor &color)
{
    m_color = color;
}
