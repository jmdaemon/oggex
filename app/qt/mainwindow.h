#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

//#include "embedwindow.h"
//#include "ui/ui_embedwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    //EmbedWindow embedWindow;
    //Ui::EmbedWindow *embedWindow;

//public slots:
    //void makeActive();
//public slots:
    //void showEmbedWindow();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
