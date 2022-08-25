#pragma once
#ifndef OGGEX_EXTRACTWIDGET_H
#define OGGEX_EXTRACTWIDGET_H

// QT Components
#include "oggex_qt.h"

// QT Libraries
#include <QWidget>

// QT UI File
#include "ui_extractwidget.h"

namespace Ui {
class ExtractWidget;
}

class ExtractWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExtractWidget(QWidget *parent = nullptr);
    ~ExtractWidget();

private:
    Ui::ExtractWidget *ui;
};

#endif // OGGEX_EXTRACTWIDGET_H
