#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Close window when quitButton is clicked
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // Navigate to embedwindow when embedButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());
    //connect(ui->embedButton, SIGNAL(clicked()), ui->stackedWidget, SLOT(&QStackedWidget::setCurrentIndex(0)));
    //connect(ui->embedButton, SIGNAL(clicked()), ui->stackedWidget, [this]{ setCurrentIndex(0);});
    //connect(ui->embedButton, SIGNAL(clicked()), ui->stackedWidget, { QStackedWidget::setCurrentIndex(0);});
    //connect(ui->embedButton, SIGNAL(clicked()), ui->stackedWidget, SLOT(setCurrentIndex(0)));
    //connect(ui->embedButton, SIGNAL(clicked()), ui->stackedWidget, SLOT(setCurrentIndex("page")));
    //connect(ui->embedButton, SIGNAL(clicked()), ui->stackedWidget, SLOT(setCurrentWidget(ui->widget)));
    //connect(ui->embedButton, SIGNAL(clicked()), ui->stackedWidget.setCurrentIndex(0));
    //QStackedWidget::setCurrentIndex();
    connect(ui->embedButton, &QPushButton::clicked, this, [=]() {
        // Show embedPage
        ui->stackedWidget->setCurrentIndex(0);
    });

    // Navigate to extractwindow when extractButton is clicked
    //connect(ui->embedButton, SIGNAL(clicked()), this, SLOT(activateWindow());
}

MainWindow::~MainWindow() {
    delete ui;
}
