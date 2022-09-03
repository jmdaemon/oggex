#include "mainwindow.h"
#include "oggex_qt.h"

int main(int argc, char **argv) {
    args.args[0] = (char*) "placeholder";
    args = set_default_args();
    argp_parse(&argp, argc, argv, 0, 0, &args);
    setup_logging(args);

    Media media = {args.sound, args.settings, args};
    if (strcmp(args.args[0], "placeholder") != 0) {
        return oggex(args.args[0], media);
    }

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
