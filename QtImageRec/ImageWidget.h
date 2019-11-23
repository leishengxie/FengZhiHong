#ifndef _IMAGE_WIDGET_H
#define _IMAGE_WIDGET_H

#include <QRect>
#include <QLabel>
#include <QObject>
#include <QString>
#include <QPixmap>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include "ui_widget.h"



class ImageWidget : public QWidget ,  public Ui_Form
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    ~ImageWidget();
private:
    int image_cur_index;
    const int image_max_index;
    const QString image_path_prefix;
private:
    void init();
    QString getCurrentImagePath();
    void displayImageInLabel(QLabel *label,const QString& imagename);
    void displayImageInLabel(QLabel *label,const QPixmap& pixmap);
    void startProcessThread(const QString& filename);

private slots:
    void click_UpPushButton();
    void click_DownPushButton();
    void deleteProcessThread();

    void errorStringSlot(const QString& err);
    void displayStepsImageSlot();
    void sendResutlTextSlot(const QByteArray& text);
protected:

};

#endif // _IMAGE_WIDGET_H
