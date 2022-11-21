#include "mainwindow.h"
#include "ui_mainwindow.h"

int G_COLUMNS = 3;
int G_ROWS = 0;

QColor COLORS[20] = {{255,153,153}, {255,204,153},{255,255,153},{204,255,153},{153,255,153},{153,255,204},
                     {153,255,255},{153,204,255}, {153,153,255}, {204,153,255}, {255,153,255},
                     {255,153,204},{255,102,102},{51,153,255},{153,51,255}, {255,0,127},{255,153,51}};

Ui::MainWindow *MainWindow::ui = new Ui::MainWindow;
std::map<std::string, QColor> MainWindow::mapOfUser;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    ui->setupUi(this);
    setWindowTitle("Forum");
    prepareTable();
    ui->lineEditAmount->setFixedSize(30,30);
    //serverProcessHandle = createServer("server\\server.exe ");
    try {
        socket1 = new MyServerSocket;
        socket1->acceptClient();
    } catch(const MyException &e){
        QMessageBox::critical(this, "ERROR!!!", e.what());
    }
}

MainWindow::~MainWindow() {
    delete ui;
    if(socket1)
        delete socket1;
    //closeServer(serverProcessHandle);
}

void MainWindow::prepareTable() {
    ui->tableWidgetMessages->setColumnCount(G_COLUMNS);
    ui->tableWidgetMessages->setRowCount(0);
    ui->tableWidgetMessages->setColumnWidth(0,150);
    ui->tableWidgetMessages->setColumnWidth(1,100);
    ui->tableWidgetMessages->setColumnWidth(2,500);
    QStringList labels = { "Time and data", "User", "Message" };
    ui->tableWidgetMessages->setHorizontalHeaderLabels(labels);
}

void MainWindow::updateTable(std::string message, std::string user, int amount) {
    int color = rand() % 17;
    mapOfUser.insert(std::pair(user,COLORS[color]));

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
        qDebug() << message.size();
        qDebug() << message.c_str();
    }
    ui->lineEditAmount->setText(QString::number(amount));
}

HANDLE MainWindow::createServer(std::string path) {
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    HANDLE handle;

    ZeroMemory(&si, sizeof(STARTUPINFOA));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    si.lpTitle = (LPSTR)"server";
    if (CreateProcessA(NULL, (LPSTR)path.c_str(), NULL, NULL, NULL,
        CREATE_NEW_CONSOLE | HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi)) {
        handle = pi.hProcess;
        logger.log("INFO", "Server process created successfully");
    } else
        logger.log("ERROR", "Server process failed to create");
    return handle;
}

void MainWindow::setSplashScreen() {
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("welcome.png"));
    splash->show();
    QTimer::singleShot(2000, splash, SLOT(close()));
}

void MainWindow::closeServer(HANDLE handle) {
    TerminateProcess(handle, EXIT_SUCCESS);
    CloseHandle(handle);
}
