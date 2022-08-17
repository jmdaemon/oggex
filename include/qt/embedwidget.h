#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

#include <QWidget>
//#include <QStandardItem>
//#include <QStandardItemModel>
//#include <QString>
#include "datamodel.h"
#include "filechooser.h"
#include "ui_filechooser.h"

namespace Ui { class EmbedWidget; }

class EmbedWidget : public QWidget {
    Q_OBJECT

private:
    Ui::EmbedWidget *ui;

public:
    explicit EmbedWidget(QWidget *parent = nullptr);
    ~EmbedWidget();
    void browse(QString prompt);
};
#endif // OGGEX_EMBEDWIDGET_H
