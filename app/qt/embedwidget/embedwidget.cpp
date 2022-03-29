#include "embedwidget.h"
#include "ui_embedwidget.h"

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget) {
    ui->setupUi(this);
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
