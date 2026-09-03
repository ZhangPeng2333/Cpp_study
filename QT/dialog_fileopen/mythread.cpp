#include "mythread.h"
#include <QFile>
#include <QDebug>

mythread::mythread(QObject *parent) : QThread(parent) {}

void mythread::setPaths(const QString &src, const QString &dst)
{
    srcPath = src;
    dstPath = dst;
}

void mythread::run()
{
    QFile srcFile(srcPath);
    QFile dstFile(dstPath);

    if (!srcFile.open(QIODevice::ReadOnly)) {
        emit copyFinished(false, "无法打开源文件: " + srcFile.errorString());
        return;
    }
    if (!dstFile.open(QIODevice::WriteOnly)) {
        emit copyFinished(false, "无法创建目标文件: " + dstFile.errorString());
        srcFile.close();
        return;
    }

    qint64 fileSize = srcFile.size();
    qint64 bytesCopied = 0;
    const qint64 bufferSize = 1024 * 1024;
    QByteArray buffer;

    while (!srcFile.atEnd()) {
        buffer = srcFile.read(bufferSize);
        if (buffer.isEmpty() && srcFile.error() != QFile::NoError) {
            emit copyFinished(false, "读取出错: " + srcFile.errorString());
            return;
        }

        qint64 written = dstFile.write(buffer);
        if (written == -1) {
            emit copyFinished(false, "写入出错: " + dstFile.errorString());
            return;
        }
        bytesCopied += written;

        int percent = static_cast<int>((bytesCopied * 100) / fileSize);
        emit progressUpdated(percent);
    }

    srcFile.close();
    dstFile.close();
    emit copyFinished(true, "拷贝成功");
}
