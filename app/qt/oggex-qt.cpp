#include "mainwindow.h"
#include "oggex_qt.h"

int main(int argc, char **argv) {
    args = init_args(argc, argv);
    setup_logging(args);

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
