#include "mainwindow.h"
#include "ogx.h"

int main(int argc, char **argv) {
    struct arguments arguments = init_args(argc, argv);

    //char* command = arguments.args[0];
    //Sound sound = arguments.sound;
    Settings settings = { 10, false };
    Media media = {arguments.sound, settings, arguments};
    //Media media = {sound, settings, arguments};
    setup_logging(arguments);
    //oggex(command, media);


    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
