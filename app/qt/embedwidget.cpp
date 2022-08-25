#include "embedwidget.h"

std::shared_ptr<spdlog::logger> setup_logger(std::vector<spdlog::sink_ptr> sinks) {
  auto logger = spdlog::get(logger_name);
  if (!logger) {
    if (sinks.size() > 0) {
        logger = std::make_shared<spdlog::logger>(logger_name, std::begin(sinks), std::end(sinks));
        spdlog::register_logger(logger);
    } else {
        logger = spdlog::stdout_color_mt(logger_name);
    }
  }
  return logger;
}

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget) {

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    auto logger = setup_logger(sinks);

    // For now, enable logs
    spdlog::set_level(spdlog::level::level_enum::trace);

    ui->setupUi(this);

    connect(ui->le_image, &FileChooser::clicked, this, [this]() {
            ui->le_image->browse("Open Image", "Image Files (*.png *.jpg *.bmp)", "", true);
        });
    connect(ui->le_audio, &FileChooser::clicked, this, [this]() {
            ui->le_audio->browse("Open Audio", "Audio Files (*.ogg)", "", true);
        });
    connect(ui->btn_embed, &QPushButton::clicked, this, [this]() {
            arguments args;
            SPDLOG_INFO("Reading embed form data");
            
            // Parse Fields
            std::string s_image = ui->le_image->text().toStdString();
            std::string s_audio = ui->le_audio->text().toStdString();
            std::string s_tag   = ui->le_tag->text().toStdString();
            std::string s_dest  = ui->le_dest->text().toStdString();
            
            SPDLOG_DEBUG("s_image : {}", s_image);
            SPDLOG_DEBUG("s_audio : {}", s_audio);
            SPDLOG_DEBUG("s_tag   : {}", s_tag);
            SPDLOG_DEBUG("s_dest  : {}", s_dest);

            args.sound.image    = (char*) s_image.c_str();
            args.sound.src      = (char*) s_audio.c_str();
            args.sound.tag      = (char*) s_tag.c_str();
            args.sound.dest     = (char*) s_dest.c_str();

            SPDLOG_INFO("Embedding Files...");

            // Prepare data
            Sound sound = args.sound;
            Settings settings = { 10, false };
            Media media = {sound, settings, args};

            embed(media);
    });
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
