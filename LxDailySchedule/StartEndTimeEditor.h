#ifndef CSTARTENDTIMEEDITOR_H
#define CSTARTENDTIMEEDITOR_H

#include <QWidget>
class QTimeEdit;

class CStartEndTimeEditor : public QWidget
{
    Q_OBJECT
public:
    explicit CStartEndTimeEditor(QWidget *parent = 0);

    void setEndStartTime(const QString & strStartTime, const QString & strEndTime);
    QString startTime() const;
    QString endTime() const;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private slots:
    void slot_startTimeChanged(const QTime &time);
    void slot_endTimeChanged(const QTime &time);

private:
    QTimeEdit* pTimeStart;
    QTimeEdit* pTimeEnd;
};

#endif // CSTARTENDTIMEEDITOR_H
