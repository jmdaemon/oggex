#include "homewidget.h"

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::HomeWidget) {

    ui->setupUi(this);

    // Close window when quitButton is clicked
    connect(ui->quitButton, &QPushButton::clicked, this, &QApplication::quit);

    // Navigate to embedwindow when embedButton is clicked
    connect(ui->embedButton, &QPushButton::clicked, this, [=, this]() {
        ui->stackedWidget->setCurrentIndex(1);
    });

    // Navigate using ComboBox
    connect(ui->comboBox, &QComboBox::activated,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);
}

HomeWidget::~HomeWidget() {
    delete ui;
}
