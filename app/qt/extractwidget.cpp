#include "extractwidget.h"

/** Auto complete fields given from command line arguments */
void ExtractWidget::autocomplete(struct arguments *args) {
    Sound sound = args->sound;
    if (sound.image != nullptr)
        this->ui->le_embedded->savePath(true, QString::fromLocal8Bit(sound.image));
    if (sound.dest != nullptr)
        this->ui->le_destdir->savePath(true, QString::fromLocal8Bit(sound.dest));
}

ExtractWidget::ExtractWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ExtractWidget) {
    ui->setupUi(this);

    autocomplete(&args);

    connect(ui->le_embedded, &FileChooser::clicked, this, [this]() {
            ui->le_embedded->browse("Open Image", "Image Files (*.png)", "", true);
        });
    connect(ui->le_destdir, &FileChooser::clicked, this, [this]() {
            ui->le_destdir->browseDir("Open Directory", "", true);
        });

    connect(ui->btn_extract, &QPushButton::clicked, this, [this]() {
            SPDLOG_INFO("Reading extract form data");
            
            // Parse Fields
            std::string s_embed     = ui->le_embedded->getPath().toStdString();
            std::string s_destdir   = ui->le_destdir->getPath().toStdString();

            SPDLOG_DEBUG("s_embed   : {}", s_embed);
            SPDLOG_DEBUG("s_destdir : {}", s_destdir);

            SPDLOG_INFO("Setting arguments");
            args.sound.image    = (char*) s_embed.c_str();
            args.sound.dest     = (char*) s_destdir.c_str();

            SPDLOG_INFO("Extracting Files ...");
            extract(media);
        });
}

ExtractWidget::~ExtractWidget() {
    delete ui;
}
