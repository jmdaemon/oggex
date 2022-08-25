#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

//#include "oggex.h"
#include "oggex_qt.h"

// QT Widgets
#include <QWidget>

// QT Components
#include "datamodel.h"
#include "filechooser.h"

// QT UI File
//#include "ui_embedwidget.h"

namespace Ui { class EmbedWidget; }

class EmbedWidget : public QWidget {
    Q_OBJECT

private:
    Ui::EmbedWidget *ui;
    //struct arguments arguments;
    
public:
    explicit EmbedWidget(QWidget *parent = nullptr);
    ~EmbedWidget();
    //void setArgs(struct arguments args);
    //struct arguments getArgs();
};
#endif // OGGEX_EMBEDWIDGET_H
