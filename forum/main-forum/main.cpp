#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow::setSplashScreen();
    MainWindow w;
    w.show();
    return a.exec();
}
