#ifndef CUSTOM_H
#define CUSTOM_H

#include <QWidget>
#include <QtDesigner/QDesignerExportWidget>

class QDESIGNER_WIDGET_EXPORT Custom : public QWidget
{
    Q_OBJECT

public:
    Custom(QWidget *parent = 0);
};

#endif
