#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H


#include <QDir>
#include <QFile>
#include <QThread>
#include <QImage>
#include <QString>
#include <QByteArray>
#include <string>


#include "TextRec.h"


class ProcessThread: public QThread
{
Q_OBJECT
signals:
    void errorStringSignal(const QString& err);
    void displayStepsImageSignal();
    void sendResutlTextSignal(const QByteArray& text);
public:
        explicit ProcessThread(const QString& filename);
        ~ProcessThread();

private:
    std::string m_filename;
private:
    void run();

    bool removeFolderContent(const QString &folderDir);
    void readResultByWordCount(int wordcount);


};


#endif // PROCESSTHREAD_H
