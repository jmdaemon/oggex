#include "mainwindow.h"
#include "oggex_qt.h"

int main(int argc, char **argv) {
    args = init_args_gui(argc, argv);
    media = {args.sound, args.settings, args};
    setup_logging(args);
    if (cmd_specified(args))
      return oggex(args.args[0], media);

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
