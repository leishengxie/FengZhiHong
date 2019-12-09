#ifndef JOKEEDITOR_H
#define JOKEEDITOR_H

#include <QWidget>

namespace Ui {
class CJokeEditor;
}

class CJokeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CJokeEditor(QWidget *parent = 0);
    ~CJokeEditor();

private:
    Ui::CJokeEditor *ui;
};

#endif // JOKEEDITOR_H
