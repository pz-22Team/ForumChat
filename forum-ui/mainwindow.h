#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <map>
#include "myserversocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonSend_clicked();

private:
    std::map<std::string, QColor> mapOfUser;
    void updateTable(std::string message, std::string user);
    Ui::MainWindow *ui;
    MyServerSocket* socket1;
};
#endif // MAINWINDOW_H
