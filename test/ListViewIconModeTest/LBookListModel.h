#ifndef CLBOOKMODEL_H
#define CLBOOKMODEL_H

#include <QAbstractListModel>

struct T_Book
{
    QString strName;
    int nPrice;
    QString strIconUrl;

    T_Book() {}
    T_Book(const QString & strName, int nPrice)
        : strName(strName), nPrice(nPrice)
    {}
};

class CLBookListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CLBookListModel(QObject *parent = nullptr);
    ~CLBookListModel();

    //QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    //QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList <T_Book> m_listBook;
};


#endif // CLBOOKMODEL_H
