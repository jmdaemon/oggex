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

    QList<QStandardItem*> outputsList = { item4 };
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
    model->appendColumn(outputsList);

    //QStandardItem* inputs = new QStandardItem("Inputs");
    //QStandardItem* outputs = new QStandardItem("Outputs");

    //model->horizontalHeaderItem(0)->setText(tr("Inputs"));
    //model->horizontalHeaderItem(1)->setText(tr("Output"));
    //model->horizontalHeaderItem(0, inputs);
    //model->horizontalHeaderItem(1)->setText(tr("Output"));
    model->setHeaderData(0, Qt::Horizontal, "Inputs", Qt::DisplayRole );
    model->setHeaderData(1, Qt::Horizontal, "Outputs", Qt::DisplayRole );


    ui->treeView->setModel(model);
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
