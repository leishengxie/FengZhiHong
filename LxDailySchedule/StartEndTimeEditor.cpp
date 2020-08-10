#include "StartEndTimeEditor.h"
#include <QTimeEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

CStartEndTimeEditor::CStartEndTimeEditor(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout* hLayMain = new QHBoxLayout;
    hLayMain->setMargin(0);
    pTimeStart = new QTimeEdit;
    connect(pTimeStart, SIGNAL(timeChanged(QTime)), this, SLOT(slot_startTimeChanged(QTime)));

    QLabel* label = new QLabel("-");
    pTimeEnd = new QTimeEdit;
    connect(pTimeEnd, SIGNAL(timeChanged(QTime)), this, SLOT(slot_endTimeChanged(QTime)));
    hLayMain->addWidget(pTimeStart);
    hLayMain->addWidget(label);
    hLayMain->addWidget(pTimeEnd);
    hLayMain->addStretch();
    setLayout(hLayMain);
}

void CStartEndTimeEditor::setEndStartTime(const QString &strStartTime, const QString &strEndTime)
{
    pTimeStart->setTime(QTime::fromString(strStartTime, "hh:mm"));
    pTimeEnd->setTime(QTime::fromString(strEndTime, "hh:mm"));
    pTimeStart->setMaximumTime(QTime::fromString(strEndTime, "hh:mm"));
    pTimeEnd->setMinimumTime(QTime::fromString(strStartTime, "hh:mm"));
}

QString CStartEndTimeEditor::startTime() const
{
    return pTimeStart->time().toString("hh:mm");
}

QString CStartEndTimeEditor::endTime() const
{
    return pTimeEnd->time().toString("hh:mm");
}

void CStartEndTimeEditor::paintEvent(QPaintEvent *event)
{
    //return QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    painter.fillRect(rect(), palette().background().color());
}

void CStartEndTimeEditor::slot_startTimeChanged(const QTime &time)
{
    pTimeEnd->setMinimumTime(time);
}

void CStartEndTimeEditor::slot_endTimeChanged(const QTime &time)
{
    pTimeStart->setMaximumTime(time);
}
