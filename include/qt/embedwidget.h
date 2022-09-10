#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

// QT Components
#include "datamodel.h"
#include "filechooser.h"
#include "oggex_qt.h"

// QT Widgets
#include <QWidget>

// QT UI File
#include "ui_embedwidget.h"

namespace Ui { class EmbedWidget; }

class EmbedWidget : public QWidget {
    Q_OBJECT

private:
    Ui::EmbedWidget *ui;
    
public:
    explicit EmbedWidget(QWidget *parent = nullptr);
    ~EmbedWidget();
    void autocomplete(struct arguments *args);
};
#endif // OGGEX_EMBEDWIDGET_H
