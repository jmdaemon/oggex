#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //ui->QuitButton
    //QObject::connect(ui->quitButton,
            //&QPushButton::clicked, &ui, &QCoreApplication::quit, Qt::QueuedConnection);
    //QObject::connect(ui->quitButton, &QPushButton::clicked, nullptr, &QCoreApplication::quit, Qt::QueuedConnection);
    //QObject::connect(ui->quitButton, &QPushButton::clicked, nullptr, &QCoreApplication::quit, Qt::QueuedConnection);
    //QObject::connect(const QObject *asender, const char *asignal, const char *amember)
    //ui->quitButton->.
    //connect(ui->quitButton, SIGNAL(triggered()), this, SLOT(MainWindow::clickQuitButton()));
    //connect(ui->quitButton, SIGNAL(triggered()), this, SLOT(this->close()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

//void MainWindow::clickQuitButton() {
    //this->close();
//}

MainWindow::~MainWindow() {
    delete ui;
}
