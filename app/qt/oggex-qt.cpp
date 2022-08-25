#include "mainwindow.h"

int main(int argc, char **argv) {
    struct arguments arguments = init_args(argc, argv);
    setup_logging(arguments);

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.setArgs(arguments);

    mainWindow.show();
    return app.exec();
}
