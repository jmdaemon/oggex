#include "embedwidget.h"
#include "ui_embedwidget.h"

#include <QStandardItemModel>
#include <QStandardItem>

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget) {
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel();

    QStandardItem* item1 = new QStandardItem(QIcon("test.png"), "ImageFile1.png");
    QStandardItem* item2 = new QStandardItem(QIcon("test.png"), "SoundFile1.ogg");
    QStandardItem* item3 = new QStandardItem(QIcon("test.png"), "SoundFile2.ogg");
    QStandardItem* item4 = new QStandardItem("OutputFile1.png");

    QList<QStandardItem*> outputs = { item4 };
    // Set up the hierarchy as:
    // First Column:
    // ImageFile1
    //  - Sound File1
    //  - Sound File2
    // Second Column
    //  - Sound File2

    model->appendRow(item1);
    item1->appendRow(item2);
    item1->appendRow(item3);
    model->appendColumn(outputs);

    ui->treeView->setModel(model);
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
