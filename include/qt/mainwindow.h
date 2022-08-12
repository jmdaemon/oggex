#pragma once
#ifndef OGGEX_MAINWINDOW_H
#define OGGEX_MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>

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
