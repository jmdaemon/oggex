#include "homewidget.h"

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::HomeWidget) {

    ui->setupUi(this);

    // Close window when quitButton is clicked
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));

    // Navigate to embedwindow when embedButton is clicked
    connect(ui->embedButton, &QPushButton::clicked, this, [=, this]() {
        // Show embedPage
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->comboBox, &QComboBox::activated,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);
}

HomeWidget::~HomeWidget() {
    delete ui;
}
