#include "mythread.h"
#include <QFile>
#include <QDebug>

mythread::mythread(QObject *parent) :
    QThread(parent) {

}

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
        emit copyFinished(false, "无法打开源文件");
        return;
    }
    if (!dstFile.open(QIODevice::WriteOnly)) {
        emit copyFinished(false, "无法创建目标文件");
        srcFile.close();
        return;
    }

    qint64 fileSize = srcFile.size();
    qint64 bytesCopied = 0;
    const qint64 BUFFER_SIZE = 1024;
    QByteArray buffer;

    while (!srcFile.atEnd()) {
        buffer = srcFile.read(BUFFER_SIZE);
        if (buffer.isEmpty() && srcFile.error() != QFile::NoError) {
            emit copyFinished(false, "读取出错");
            return;
        }

        qint64 written = dstFile.write(buffer);
        if (written < 0) {
            emit copyFinished(false, "写入出错");
            return;
        }
        bytesCopied += written;

        int percent = static_cast<int>((bytesCopied * 100) / fileSize);
        emit progressUpdated(percent);
        //这里最好改成按百分比发信号，这样他 多就发100次 少也发100次

    }

    srcFile.close();
    dstFile.close();
    emit copyFinished(true, "拷贝成功");
}
