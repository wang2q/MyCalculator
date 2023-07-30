#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 创建一个 QPalette 对象

    w.setFixedSize(720,480);

    // 获取当前窗口标志
    Qt::WindowFlags flags = w.windowFlags();

        // 移除全屏标志
    flags &= ~Qt::WindowFullScreen;
    w.setWindowFlags(flags);
    w.show();
    return a.exec();
}
