#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QRadioButton>
//#include <QButtonGroup>
#include <QtDebug>
#include <QSortFilterProxyModel>
#include <QAbstractTableModel>
#include <QAbstractListModel>
#include <QListWidget>
#include <QColumnView>
#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QGridLayout>

struct T_CustomDdata
{
    QGridLayout l;
    int a;
    int b;

    enum E_SortField
    {
        ES_ByA,
        ES_ByB
    };

    T_CustomDdata() {
        m_eSortField = ES_ByA;
    }

    void setSortField(E_SortField eSortField)
    {
        m_eSortField = eSortField;
    }

    bool operator< ( const T_CustomDdata& rhs ) const
    {
        if (m_eSortField == ES_ByA)
        {
            return a < rhs.a;
        }
        else if (m_eSortField == ES_ByB)
        {
            return b < rhs.b;
        }

    }

    E_SortField m_eSortField;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    QRadioButton radio;
    //    QButtonGroup group;
        QStringList list;
        list << "age" << "balance" << "bool_col" << "str_02" << "str_03" << "A";
        //QRegExp r("*");
        ///总结
        // 当原模型数据改变时可用 emit layoutChanged 通知视图和QSortFilterProxyModel
        // 当原模型时多列，且要过滤所有项时QSortFilterProxyModel需要设置setFilterKeyColumn(-1)，重写filterAcceptsColumn
        QSortFilterProxyModel m;
        QModelIndex();

        m.setDynamicSortFilter(true);
        //QAbstractListModel l;
        QColumnView c;
        //m.setFilterRegExp();
        QRegExp rxp("^A", Qt::CaseInsensitive);
        Qt::SortOrder order;
        order = Qt::AscendingOrder;//升序
        order = Qt::DescendingOrder;
        //qSort
        foreach (QString str, list)
        {
            if (rxp.exactMatch(str))
            {
                qDebug() << str;
            }
            if (rxp.indexIn(str) != -1)
            {
                qDebug() << "indexIn" << str;
            }
        }

    //test
        QVector<T_CustomDdata> vecCustomDdata;
        T_CustomDdata t1, t2;
        t1.a = 5;
        t1.b = 2;
        t2.a = 3;
        t2.b = 4;
        vecCustomDdata.append(t1);
        vecCustomDdata.append(t2);
        std::sort(vecCustomDdata.begin(), vecCustomDdata.end());
        foreach (T_CustomDdata td, vecCustomDdata) {
            qDebug() << td.a;
        }

        for (T_CustomDdata & td : vecCustomDdata) {
            td.m_eSortField = T_CustomDdata::ES_ByB;
        }
        std::sort(vecCustomDdata.begin(), vecCustomDdata.end(), qGreater<T_CustomDdata>());
        foreach (T_CustomDdata td, vecCustomDdata) {
            qDebug() << td.a;
        }

        QListWidget* listwgt;
        QListView* listView;
        listwgt->takeItem(0);
//        将QListWidgetItem从QListWidget列表中删除有两种方法能够做到。但也要依据自己的须要进行选择。

//        第一种是

//        QListWidgetItem *takeItem(int row);
//        使用此方法须要知道删除的是第几个Item。而且返回删除的Item指针。
//        另外一种是


//        inline void removeItemWidget(QListWidgetItem *item);
//        须要知道删除的Item的对象
        listwgt->setItemWidget();

        QSet set;

}

MainWindow::~MainWindow()
{
    delete ui;
}

