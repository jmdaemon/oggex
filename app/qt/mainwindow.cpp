#include "mainwindow.h"
#include "./ui/ui_mainwindow.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Close window when quitButton is clicked
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
}
MainWindow::~MainWindow() {
    delete ui;
}
