#include "mainwindow.h"
#include "oggex_qt.h"

int main(int argc, char **argv) {
    //struct arguments arguments = init_args(argc, argv);
    //args = arguments;
    args = init_args(argc, argv);
    setup_logging(args);

    QApplication app(argc, argv);
    MainWindow mainWindow;

    //mainWindow.setArgs(arguments);

    mainWindow.show();
    return app.exec();
}
