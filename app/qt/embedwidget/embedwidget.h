#ifndef EMBEDWIDGET_H
#define EMBEDWIDGET_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>

namespace Ui { class EmbedWidget; }

class EmbedWidget : public QWidget {
    Q_OBJECT

private:
    Ui::EmbedWidget *ui;
    QStandardItemModel* model;

public:
    explicit EmbedWidget(QWidget *parent = nullptr);
    ~EmbedWidget();
    QStandardItem* makeEntry(QString path);
    QStandardItem* makeSoundButton();
    void addSound(QStandardItem* sound, QStandardItem* image);
    void addImage(QStandardItem* image, QStandardItemModel* model);
    void addToModel(QString path, QStandardItemModel* model);
    void setHeaders(QStandardItemModel* model);
};
#endif // EMBEDWIDGET_H
