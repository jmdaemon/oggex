#include "mainwindow/mainwindow.h"
//#include "embedwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    //EmbedWindow embedWindow;

    mainWindow.show();
    //embedWindow.show();
    return app.exec();
}
