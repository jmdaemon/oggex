#include "embedwidget.h"

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget) {

    ui->setupUi(this);

    connect(ui->le_image, &FileChooser::clicked, this, [this]() {
            ui->le_image->browse("Open Image", "Image Files (*.png *.jpg *.bmp)", "", true);
        });
    connect(ui->le_audio, &FileChooser::clicked, this, [this]() {
            ui->le_image->browse("Open Audio", "Audio Files (*.ogg)", "", true);
        });
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
