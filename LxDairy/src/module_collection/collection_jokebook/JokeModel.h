#ifndef CJOKEMODEL_H
#define CJOKEMODEL_H
#include <QAbstractTableModel>


struct T_JokeRating
{
    int jId;        // 被评价的资源id 既是主键也是外键
    int uId;        // 评价用户id 既是主键也是外键
    qreal dRating;  // 评分

};

struct T_Joke
{
    T_Joke()
        : jId(-1)
        , bOriginal(false)
        , upUid(-1)
        , llRatingNumOfPeople(0)
        , dRatingToatalScore(0)
        , dRatingAverageScore(0)
    {

    }

    int jId;
    QString strTitle;
    QString strDate;
    QString strContent;

    bool bOriginal; // 是否原创

    int upUid;        // 上传者用户id
    QString strNickname; // 上传者昵称


    quint64 llRatingNumOfPeople; // 评价总人数
    qreal dRatingToatalScore ; // 评价总评分
    qreal dRatingAverageScore;  // 评价平均评分 0-5

    //QVector<T_Rating> vecRating;    // 评价列表

};
Q_DECLARE_METATYPE(T_Joke)



class CJokeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CJokeModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<T_Joke> listJoke()
    {
        return m_lstJoke;
    }

    void setListJoke(const QList<T_Joke> & lstJoke);


private:


private:
    QList<T_Joke> m_lstJoke;
    QStringList m_strlstHeader;
};

#endif // CJOKEMODEL_H
