#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Navigate to extractwindow when extractButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setArgs(struct arguments args) {
    this->arguments = args;
}
