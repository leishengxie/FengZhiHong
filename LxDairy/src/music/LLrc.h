#ifndef CLLRC_H
#define CLLRC_H

#include <QMap>

///
/// \brief The CLIrc class 歌词解析器
///
class CLLrc
{
public:
    explicit CLLrc();

    // 打开歌词文件并解析歌词到m_mapLrc
    bool openLrcFile(const QString & strFileName);

    void refreshDuration(qint64 llDurationTime)
    {
        m_llDurationTime = llDurationTime;
    }

    // 获取时间轴上时间为llPosTime毫秒的歌词
    void refreshLrc(qint64 llPosTime);

    void clearCurLrc();

protected:
    // 一首歌全部歌词
    QMap<qint64, QString> m_mapLrc;

    // 一首歌的总时长
    qint64 m_llDurationTime;

    // 当前显示的本句歌词
    QString m_strCurLrc;

    // 本句歌词与下一句歌词显示的时间间隔
    qint64 m_llIntervalTime;

    // 本句歌词是否显示完成
    bool m_bCurLrcTimeOut;

};

#endif // CLLRC_H
