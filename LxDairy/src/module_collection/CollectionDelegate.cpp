#include "CollectionDelegate.h"
#include <QPainter>
#include <QApplication>
#include "CollectionModel.h"

// qss盒子模型
static const int s_nPadding = 5;    // padding 5pix
static const int s_nIconTextSpace = 2;

CCollectionDelegate::CCollectionDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{
}

void CCollectionDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if (!index.isValid())
    {
        return;
    }

    painter->save();
    QVariant var = index.data(Qt::DisplayRole);
    T_CollectionItem tCollectionItem = var.value<T_CollectionItem>();

    // item 矩形区域
    QRectF rect;
    rect.setX(option.rect.x());
    rect.setY(option.rect.y());
    rect.setWidth(option.rect.width() - 1);
    rect.setHeight(option.rect.height() - 1);

    // name
    QFontMetrics fontMetrics(painter->font());
    int nWidthName = rect.width() - s_nPadding * 2;
    int nHeightName = fontMetrics.height();
    int nWidthElideWidth = fontMetrics.width("...");
    QString strName = fontMetrics.elidedText(tCollectionItem.strName, Qt::ElideRight, nWidthName - nWidthElideWidth);
    QRect rectName(rect.x() + s_nPadding, rect.y() + rect.height() - nHeightName - s_nPadding, nWidthName, nHeightName);
    QApplication::style()->drawItemText ( painter
                                          , rectName
                                          , Qt::AlignCenter
                                          , QApplication::palette()
                                          , true
                                          , strName);

    // icon
    QImage img(tCollectionItem.strIconPath);

    int nHeightIconTheory = rect.height() - s_nPadding - s_nIconTextSpace - nHeightName - s_nPadding;
    int nWidthIconTheory  = rect.width() - s_nPadding * 2;
    qreal dScale = 1;
    qreal dScaleWidth = 1;
    qreal dScaleHeight = 1;

    if (img.width() > nWidthIconTheory)
    {
        dScaleWidth = img.width() / (qreal)nWidthIconTheory;
    }
    if (img.height() > nHeightIconTheory)
    {
        dScaleHeight = img.height() / (qreal)nHeightIconTheory;
    }
    dScale = dScaleWidth > dScaleHeight ? dScaleWidth : dScaleHeight;

    int nWidthIcon = img.width() / dScale;
    int nHeightIcon = img.height() / dScale;

    int nX = rect.x() + (rect.width() - nWidthIcon) * 0.5;
    int nY = rect.y() + (rect.height() - nHeightName - s_nIconTextSpace - nHeightIcon) * 0.5;
    QRect rectIcon(nX, nY, nWidthIcon, nHeightIcon);
    painter->drawImage(rectIcon, img);

    painter->restore();
}

QSize CCollectionDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    Q_UNUSED(index)
    //return QSize(option.rect.width(), option.rect.height());
//    QSize size = QStyledItemDelegate::sizeHint(option, index);
//    if (index.column() == 0)
//    {
//        return QSize(40, size.height());
//    }
//    return size;
    return QSize(100, 100);
}
