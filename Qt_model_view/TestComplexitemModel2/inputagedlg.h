#ifndef INPUTAGEDLG_H
#define INPUTAGEDLG_H
#include <QDialog>
namespace Ui {
class InputAgeDlg;
}
class InputAgeDlg : public QWidget
{
    Q_OBJECT
public:
    explicit InputAgeDlg(QWidget *parent = 0);
    ~InputAgeDlg();
    QString getage();
    QString getage_unit();
    void set_Age(const QString& a);
    void set_age_uint(const QString &u);
public:
    Ui::InputAgeDlg *ui;
    QString age;
    QString age_uint;
private slots:
    void on_ageedit_editingFinished();
    void on_ageunitbox_currentIndexChanged(const QString &arg1);
};
#endif // INPUTAGEDLG_H
