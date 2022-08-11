#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include "datamodel.h"

namespace Ui { class EmbedWidget; }

class EmbedWidget : public QWidget {
    Q_OBJECT

private:
    Ui::EmbedWidget *ui;
    //QStandardItemModel* model;
    //DataModel* model;

public:
    explicit EmbedWidget(QWidget *parent = nullptr);
    ~EmbedWidget();
};
#endif // OGGEX_EMBEDWIDGET_H
