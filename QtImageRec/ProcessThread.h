#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>




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
    QString m_strFilename;
private:
    void run();

    bool removeFolderContent(const QString &folderDir);
    void readResultByWordCount(int wordcount);


};


#endif // PROCESSTHREAD_H
