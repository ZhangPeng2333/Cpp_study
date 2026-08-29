#include "dialog1.h"
#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QColor>

int main(int argc, char *argv[])
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication a(argc, argv);

    // 设置 Fusion 风格
    if (QStyleFactory::keys().contains("Fusion")) {
        a.setStyle("Fusion");
    }

    // 调色板（柔和的灰白背景）
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(248, 249, 250));
    palette.setColor(QPalette::WindowText, QColor(40, 44, 52));
    palette.setColor(QPalette::Button, QColor(255, 255, 255));
    palette.setColor(QPalette::ButtonText, QColor(40, 44, 52));
    palette.setColor(QPalette::Highlight, QColor(0, 120, 212));
    palette.setColor(QPalette::HighlightedText, Qt::white);
    a.setPalette(palette);

    // 全局字体（微软雅黑或 Segoe UI）
    QFont font("Microsoft YaHei", 9);
    a.setFont(font);

    // 全局样式表（只设置背景和通用字体，控件样式由 dialog1 内部控制）
    a.setStyleSheet(
        "QDialog { background-color: #f8f9fa; }"
        "QLabel { color: #2c3e50; }"
    );

    Dialog1 w;
    w.show();

    return a.exec();
}
