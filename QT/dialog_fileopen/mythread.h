#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread(QObject *parent = 0);
    // 设置源和目标路径
    void setPaths(const QString &src, const QString &dst);

signals:
    void progressUpdated(int percent);      // 进度 0~100
    void copyFinished(bool success, QString errorMsg);

protected:
    void run();

private:
    QString srcPath;
    QString dstPath;
};

#endif // MYTHREAD_H
