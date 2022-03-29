#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Close window when quitButton is clicked
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // Navigate to embedwindow when embedButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());

    // Navigate to extractwindow when extractButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());
}

MainWindow::~MainWindow() {
    delete ui;
}
