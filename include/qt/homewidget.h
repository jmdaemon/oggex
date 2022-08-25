#pragma once
#ifndef OGGEX_HOMEWIDGET_H
#define OGGEX_HOMEWIDGET_H

#include "oggex_qt.h"

// QT Libraries
#include <QWidget>
#include <QApplication>

// QT UI File
#include "ui_homewidget.h"

namespace Ui {
  class HomeWidget;
}

class HomeWidget : public QWidget {
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    ~HomeWidget();

private:
    Ui::HomeWidget *ui;
    //struct arguments arguments;
    //void setArgs(struct arguments args);
    //struct arguments getArgs();

};

#endif // OGGEX_HOMEWIDGET_H
