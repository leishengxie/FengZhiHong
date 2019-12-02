#ifndef CJOKEMODEL_H
#define CJOKEMODEL_H
#include <QAbstractTableModel>


struct T_Joke
{
    int jId;
    QString strTitle;
    QString strDate;
    QString strContent;
    QString strNickname; // 作者昵称

    quint64 llRatingNumOfPeople; // 评价总人数
    quint64 llRatingToatalScore ; // 评价总评分
    qreal dRatingAverageScore;  // 评价平均评分 0-5



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
