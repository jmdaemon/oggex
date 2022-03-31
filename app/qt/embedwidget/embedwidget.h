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

public:
    explicit EmbedWidget(QWidget *parent = nullptr);
    ~EmbedWidget();
    //QStandardItem* makeSound();
    QStandardItem* makeSoundButton();
    //QStandardItem* makeImage(QString path);
    QStandardItem* makeEntry(QString path);
    void addSound(QStandardItem* sound, QStandardItem* image);
    void addImage(QStandardItem* image, QStandardItemModel* model);
    void addToModel(QString path, QStandardItemModel* model);
};
#endif // EMBEDWIDGET_H
