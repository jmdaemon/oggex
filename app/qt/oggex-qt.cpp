#include "mainwindow.h"
#include "oggex_qt.h"

int main(int argc, char **argv) {
    args.args[0] = (char*) "";
    args = set_default_args();
    args.verbose = 1;
    setup_logging(args);

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
