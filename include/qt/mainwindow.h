#pragma once
#ifndef OGGEX_MAINWINDOW_H
#define OGGEX_MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // OGGEX_MAINWINDOW_H
