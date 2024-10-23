#include "mainwindow.h"

#include <QApplication>
#include <QCursor>
#include <QScreen>

void moveMouseToCenter() {
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->geometry();
        int centerX = screenGeometry.x() + screenGeometry.width() / 2;
        int centerY = screenGeometry.y() + screenGeometry.height() / 2;

        QCursor::setPos(centerX, centerY);
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    moveMouseToCenter();
    MainWindow w;
    w.show();
    return a.exec();
}
