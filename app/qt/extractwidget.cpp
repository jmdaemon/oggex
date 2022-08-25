#include "extractwidget.h"

ExtractWidget::ExtractWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ExtractWidget) {
    ui->setupUi(this);

    connect(ui->le_embedded, &FileChooser::clicked, this, [this]() {
            ui->le_embedded->browse("Open Image", "Image Files (*.png)", "", true);
        });
    connect(ui->le_destdir, &FileChooser::clicked, this, [this]() {
            ui->le_destdir->browseDir("Open Directory", "", true);
        });

    connect(ui->btn_extract, &QPushButton::clicked, this, [this]() {

            SPDLOG_INFO("Reading embed form data");
            
            // Parse Fields
            std::string s_embed     = ui->le_embedded->getPath().toStdString();
            std::string s_destdir   = ui->le_destdir->getPath().toStdString();

            SPDLOG_DEBUG("s_embed   : {}", s_embed);
            SPDLOG_DEBUG("s_destdir : {}", s_destdir);

            SPDLOG_INFO("Setting arguments");
            args.sound.image    = (char*) s_embed.c_str();
            args.sound.dest     = (char*) s_destdir.c_str();

            // Prepare data
            Media media = {args.sound, args.settings, args};
            SPDLOG_INFO("Embedding Files ...");
            extract(media);
        });
}

ExtractWidget::~ExtractWidget() {
    delete ui;
}
