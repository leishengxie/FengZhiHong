#ifndef DENGLV_H
#define DENGLV_H

#include <QWidget>

namespace Ui {
class denglv;
}

class denglv : public QWidget
{
    Q_OBJECT

public:
    explicit denglv(QWidget *parent = 0);
    ~denglv();

private slots:
    void on_pushButtonzhuce_clicked();

    void on_pushButtonxiugai_clicked();

    void on_pushButtondenglv_clicked();

    void on_lineEditzanghao_currentTextChanged(const QString &arg1);

private:
    Ui::denglv *ui;
    QStringList filenameInDir(QString path);

};

#endif // DENGLV_H
