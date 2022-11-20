#include "mainwindow.h"
#include "ui_mainwindow.h"
int G_COLUMNS = 3;
int G_ROWS = 0;
//int COLORS[15][3] = {

QColor COLORS[20] = {{255,153,153}, {255,204,153},{255,255,153},{204,255,153},{153,255,153},{153,255,204},
                     {153,255,255},{153,204,255}, {153,153,255}, {204,153,255}, {255,153,255},
                     {255,153,204},{255,102,102},{51,153,255},{153,51,255}, {255,0,127},{255,153,51}};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tableWidgetMessages->setColumnCount(G_COLUMNS);
    ui->tableWidgetMessages->setRowCount(0);
    ui->tableWidgetMessages->setColumnWidth(0,150);
    ui->tableWidgetMessages->setColumnWidth(1,100);
    ui->tableWidgetMessages->setColumnWidth(2,500);
    QStringList labels = { "Time and data", "User", "Message" };
    ui->tableWidgetMessages->setHorizontalHeaderLabels(labels);
    ui->textEdit->setFixedHeight(50);


    socket1 = new MyServerSocket;
    socket1->acceptClient();


}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateTable(std::string message, std::string user) {
    G_ROWS++;
    int oldRow = ui->tableWidgetMessages->rowCount();
    ui->tableWidgetMessages->setRowCount(G_ROWS);
    srand (time(NULL));


    for(int i = oldRow; i < ui->tableWidgetMessages->rowCount(); ++i) {
        for(int j = 0; j < ui->tableWidgetMessages->columnCount(); ++j) {
            QTableWidgetItem *item= new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            ui->tableWidgetMessages->setItem(i, j, item);
            ui->tableWidgetMessages->item(i,j)->setBackground(mapOfUser[user]);
        }
    }
    QLocale testLocale = QLocale(QLocale::Ukrainian, QLocale::Ukraine);
    QString dateTimeText = testLocale.toString(QDateTime::currentDateTime(), "HH:mm:ss dd-MM-yyyy");

    for(int i = oldRow; i < ui->tableWidgetMessages->rowCount(); ++i) {
        ui->tableWidgetMessages->item(i, 0)->setText(dateTimeText);
        ui->tableWidgetMessages->item(i, 1)->setText(QString::fromStdString(user));
        ui->tableWidgetMessages->item(i, 2)->setText(QString::fromStdString(message));

    }

}


void MainWindow::on_pushButtonSend_clicked() {
    std::string message = ui->textEdit->toPlainText().toStdString();
    std::string user = ui->lineEditUser->text().toStdString();

    int color = rand() % 17;
    mapOfUser.insert(std::pair(user,COLORS[color]));
    updateTable(message, user);
}


