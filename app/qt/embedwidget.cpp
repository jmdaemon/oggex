#include "embedwidget.h"
#include "ui_embedwidget.h"

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget), model(new DataModel()) {

    ui->setupUi(this);

    // Set the current model
    ui->treeView->setModel(model);
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
