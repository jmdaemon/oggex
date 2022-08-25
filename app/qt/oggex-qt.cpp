#include "mainwindow.h"
#include "oggex_qt.h"

int main(int argc, char **argv) {
    //args = init_args(argc, argv);
    args = set_default_args();
    setup_logging(args);

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
