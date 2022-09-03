#include "mainwindow.h"
#include "oggex_qt.h"

int main(int argc, char **argv) {
    //args = init_args(argc, argv);
    args = init_args_gui(argc, argv);
    setup_logging(args);
    Media media = {args.sound, args.settings, args};
    if (cmd_specified(args))
      return oggex(args.args[0], media);

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
