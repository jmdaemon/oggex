#include "embedwidget.h"
#include "ui_embedwidget.h"
//#include "mainwindow.h"

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget) {

    ui->setupUi(this);
    //MainWindow* mainwindow = qobject_cast<MainWindow*>(this->parent());
    //this->setArgs(mainwindow->getArgs());

    /* TODO: Autocomplete/set fields from cli arguments */

    connect(ui->le_image, &FileChooser::clicked, this, [this]() {
            ui->le_image->browse("Open Image", "Image Files (*.png *.jpg *.bmp)", "", true);
        });
    connect(ui->le_audio, &FileChooser::clicked, this, [this]() {
            ui->le_audio->browse("Open Audio", "Audio Files (*.ogg)", "", true);
        });
    connect(ui->btn_embed, &QPushButton::clicked, this, [this]() {
            //struct arguments args = this->getArgs();

            SPDLOG_INFO("Reading embed form data");
            
            // Parse Fields
            std::string s_image = ui->le_image->getPath().toStdString();
            std::string s_audio = ui->le_audio->getPath().toStdString();
            std::string s_tag   = ui->le_tag->text().toStdString();
            std::string s_dest  = ui->le_dest->text().toStdString();
            
            SPDLOG_DEBUG("s_image : {}", s_image);
            SPDLOG_DEBUG("s_audio : {}", s_audio);
            SPDLOG_DEBUG("s_tag   : {}", s_tag);
            SPDLOG_DEBUG("s_dest  : {}", s_dest);

            SPDLOG_INFO("Setting arguments");
            args.sound.image    = (char*) s_image.c_str();
            args.sound.src      = (char*) s_audio.c_str();
            args.sound.tag      = (char*) s_tag.c_str();
            args.sound.dest     = (char*) s_dest.c_str();

            // Prepare data
            Sound sound = args.sound;
            Settings settings = { 10, false };
            Media media = {sound, settings, args};
            SPDLOG_INFO("Embedding Files ...");
            embed(media);
    });
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}

//void EmbedWidget::setArgs(struct arguments args) {
    //this->arguments = args;
//}

//struct arguments EmbedWidget::getArgs() {
    //return this->arguments;
//}
