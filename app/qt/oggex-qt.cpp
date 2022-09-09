#include "mainwindow.h"
#include "oggex_qt.h"

struct arguments args;

int main(int argc, char **argv) {
    args = init_args_gui(argc, argv);
    //args = set_default_args();
    //args.args[0] = (char*) "placeholder";
    //puts("Running");

    //
    //std::vector<const char*> new_argv(argv, argv + argc);
    //new_argv.push_back("-app_ver");
    //new_argv.push_back(nullptr); // or NULL if you are using an old compiler
    //argv = (char**) new_argv.data();
    //argc = argc + 1;

    //argp_parse(&argp, argc, argv, 0, 0, &args);
    //puts("Finished parsing");
    media = {args.sound, args.settings, args};
    setup_logging(args);
    //puts("Setup media, logging");
    //printf("%s\n", args.args[0]);
    if (cmd_specified(args)) {
        //puts("Running in oggex-cli compatibility mode");
        //printf("args.args[0] %s\n", args.args[0]);
        return oggex(args.args[0], media);
    }
    //printf("Source  : %s\n", args.sound.src);
    //printf("Image   : %s\n", args.sound.image);
    //printf("Tag     : %s\n", args.sound.tag);
    //printf("Dest    : %s\n", args.sound.dest);
    //puts("Spawning gui");

    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
