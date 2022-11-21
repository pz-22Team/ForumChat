#pragma once
#include <QMainWindow>
#include <QtWidgets>
#include <map>
#include "myserversocket.h"
#include "myexception.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static void setSplashScreen();
    static void updateTable(std::string message, std::string user, int amount);
    static Ui::MainWindow *ui;

private:
    HANDLE serverProcessHandle;
    MyServerSocket* socket1;

    void prepareTable() ;
    static std::map<std::string, QColor> mapOfUser;
    HANDLE createServer(std::string path);
    void closeServer(HANDLE handle);
    Logger logger;
};

