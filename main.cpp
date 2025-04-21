#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QStyleFactory>
#include "Chess.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(760,700);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(240, 240, 240));     // light gray
    palette.setColor(QPalette::WindowText, Qt::black);
    palette.setColor(QPalette::Base, QColor(255, 255, 255));
    palette.setColor(QPalette::Highlight, QColor(0, 122, 255));    // macOS blue
    palette.setColor(QPalette::Button, QColor(240, 240, 240));

    QApplication::setPalette(palette);
    w.show();
    return a.exec();
}
