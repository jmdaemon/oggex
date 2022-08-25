#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "oggex_qt.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Navigate to extractwindow when extractButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());
    //ui->widget_main->ui->widget->setArgs(this->getArgs());
}

MainWindow::~MainWindow() {
    delete ui;
}

//void MainWindow::setArgs(struct arguments args) {
    //this->arguments = args;
//}

//struct arguments MainWindow::getArgs() {
    //return this->arguments;
//}
