#include "LLrc.h"
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QTextCodec>

CLLrc::CLLrc()
{
    m_bCurLrcTimeOut = true;
}

bool CLLrc::openLrcFile(const QString &strFileName)
{

    //打开歌词文件
    QFile file(strFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return false;
    }

    m_mapLrc.clear();

    QTextStream all(&file);
    // 需要判断文件内容的编码集，用相应的编码打开
    all.setCodec(QTextCodec::codecForName("utf-8"));
    QString allText = all.readAll();//获取歌词文本信息
    file.close();

    //按行吧歌词分解为歌词列表
    QStringList lines = allText.split("\n");

    //使用正则表达式吧时间标签和歌词分隔开
    QRegExp rx("\\[\\d{2}\\:\\d{2}\\.\\d{2}\\]");

    foreach(QString strline, lines)
    {
        QString temp = strline;
        temp.replace(rx,"");

        int pos = rx.indexIn(strline, 0);

        //将时间标签转换为以毫秒为单位的整形时间
        while (pos != -1)
        {
            QString cap = rx.cap(0);

            QRegExp regexep;
            regexep.setPattern("\\d{2}(?=\\:)");
            regexep.indexIn(cap);
            int minute = regexep.cap(0).toInt();

            regexep.setPattern("\\d{2}(?=\\.)");
            regexep.indexIn(cap);
            int second = regexep.cap(0).toInt();

            regexep.setPattern("\\d{2}(?=\\])");
            regexep.indexIn(cap);
            int millisecond = regexep.cap(0).toInt();

            qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;

            m_mapLrc.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(strline, pos);
        }
    }

    if(m_mapLrc.isEmpty())
    {
        return false;
    }
    qDebug() << m_mapLrc;
    return true;
}

///
/// \brief CLLrc::getLrc 当前应该显示的歌词
/// \param llPosTime    歌曲播放当前进度
/// \return
///
void CLLrc::refreshLrc(qint64 llPosTime)
{
    if(m_mapLrc.isEmpty())//
    {
        m_strCurLrc = "----LxMusic----";
    }
    qint64 llPosCurLrc = 0;  //llPosTime的前面的歌词的位置
    qint64 llPosNextLrc = 0;     //llPosTime的后面的歌词的位置
    // 直到找到下句歌词退出
    foreach(qint64 llPosKeyTime, m_mapLrc.keys())
    {
        if (llPosTime >= llPosKeyTime)
        {
            llPosCurLrc = llPosKeyTime;
        }
        else
        {
            llPosNextLrc = llPosKeyTime;
            break;
        }
    }

    if (llPosNextLrc == 0)
    {
        llPosNextLrc = m_llDurationTime;
    }
    QString strDestLrc = m_mapLrc.value(llPosCurLrc);

    // 如果歌词不一样，应该是当前歌词显示时间到了，应该切换歌词
    if(strDestLrc != m_strCurLrc)
    {
        m_llIntervalTime = llPosNextLrc - llPosCurLrc;
        m_strCurLrc = strDestLrc;
        m_bCurLrcTimeOut = true;
        qDebug() << m_strCurLrc;
    }
    else
    {
        m_bCurLrcTimeOut = false;
    }

}

void CLLrc::clearCurLrc()
{
    m_strCurLrc.clear();
}
