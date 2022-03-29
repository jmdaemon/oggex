#include "mainwindow.h"
#include "embedwindow.h"
#include "./ui/ui_mainwindow.h"
//#include "./ui/ui_embedwindow.h"

#include <QObject>

MainWindow::MainWindow(QWidget *parent)
    //: QMainWindow(parent), ui(new Ui::MainWindow), embedWindow(EmbedWindow(parent)) {
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Close window when quitButton is clicked
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // Navigate to embedwindow when embedButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(showEmbedWindow()));
    //connect(ui->embedButton, &QPushButton::released, [this] { emit clicked(); });
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(this->embedWindow.activateWindow()));
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(this->embedWindow.activateWindow()));
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(activateWindow()));
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(this->embedWindow.makeActive()));
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(EmbedWindow::makeActive()));
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(this.embedWindow.activateWindow()));
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(activateWindow()));
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(makeActive()));
    //connect(ui->embedButton, SIGNAL(clicked()), &this->embedWindow, SLOT(makeActive()));
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(hide()));

    // Navigate to extractwindow when extractButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());
}

//void MainWindow::showEmbedWindow() {
    // Create the EmbedWindow
    //Ui::EmbedWindow* w;
    //w->setupUi(this);
    //w->activateWindow();
    //w->raise();
    //w->EmbedWindow.activateWindow();
    // Show the window
    //w->activateWindow();
    //w.activateWindow();
    //w.raise();
//}

MainWindow::~MainWindow() {
    delete ui;
}
