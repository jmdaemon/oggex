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
    connect(ui->btn_embed, &QPushButton::clicked, this, [this]() {
            //FileChooser* fc = ui->le_image;
            //QLineEdit* fc_image = qobject_cast<QLineEdit*>(ui->le_image);
            //fc->text();
            qInfo("Parsing Fields");
            arguments args;

            //args.sound.image = (char*) ui->le_image->text().toStdString().c_str();
            //args.sound.src = (char*) ui->le_audio->text().toStdString().c_str();
            //args.sound.tag = (char*) ui->le_tag->text().toStdString().c_str();
            //args.sound.dest = (char*) ui->le_dest->text().toStdString().c_str();

            QLineEdit* qle_image = qobject_cast<QLineEdit*>(ui->le_image->parent());
            QLineEdit* qle_sound = qobject_cast<QLineEdit*>(ui->le_audio->parent());

            //ui->le_tag->text();
            //ui->le_dest->text();

            //QLineEdit* qle_tag = qobject_cast<QLineEdit*>(ui->le_tag->parent());
            std::string simage = qle_image->text().toStdString();
            std::string ssound = qle_sound->text().toStdString();

            //args.sound.image    = (char*) qle_image->text().toStdString().c_str();
            //args.sound.src      = (char*) qle_sound->text().toStdString().c_str();

            args.sound.image    = (char*) simage.c_str();
            args.sound.src      = (char*) ssound.c_str();

            args.sound.tag  = (char*) ui->le_tag->text().toStdString().c_str();
            args.sound.dest = (char*) ui->le_dest->text().toStdString().c_str();

            qInfo("Embedding");
            Sound sound = args.sound;
            Settings settings = { 10, false };
            Media media = {sound, settings, args};
            embed(media);

            //ui->le_image->text();
            // Get text from all fields
            //arguments args;
            // Create arguments struct
            // Call embed
            
            });
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}

//char* get_c_str(FileChooser* fc) {
    //return (char*) fc->text().toStdString().c_str()
//}
