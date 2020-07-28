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

    QLabel* label = new QLabel("-");
    pTimeEnd = new QTimeEdit;
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
    return pTimeStart->text();
}

QString CStartEndTimeEditor::endTime() const
{
    return pTimeEnd->text();
}

void CStartEndTimeEditor::paintEvent(QPaintEvent *event)
{
    //return QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    painter.fillRect(rect(), palette().background().color());
}
