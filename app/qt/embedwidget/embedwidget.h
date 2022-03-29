#ifndef EMBEDWIDGET_H
#define EMBEDWIDGET_H

#include <QWidget>

namespace Ui { class EmbedWidget; }

class EmbedWidget : public QWidget {
    Q_OBJECT

public:
    explicit EmbedWidget(QWidget *parent = nullptr);
    ~EmbedWidget();

private:
    Ui::EmbedWidget *ui;
};

#endif // EMBEDWIDGET_H
