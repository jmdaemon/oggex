#pragma once
#ifndef OGGEX_HOMEWIDGET_H
#define OGGEX_HOMEWIDGET_H

#include <QWidget>

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
};

#endif // OGGEX_HOMEWIDGET_H
