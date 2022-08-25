#pragma once
#ifndef OGGEX_MAINWINDOW_H
#define OGGEX_MAINWINDOW_H

#include "ogx.h"

// QT Widgets
#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QComboBox>

// QT UI File
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    struct arguments arguments;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setArgs(struct arguments args);
};
#endif // OGGEX_MAINWINDOW_H
