#ifndef CCHESSBOARDWIDGET_H
#define CCHESSBOARDWIDGET_H

#include "core/ChessBoard.h"
#include <QWidget>

class CChessBoardWidget : public QWidget, public CChessBoard
{
    Q_OBJECT
public:
    explicit CChessBoardWidget(QWidget *parent = nullptr);

signals:

};

#endif // CCHESSBOARDWIDGET_H
