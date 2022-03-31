#include "embedwidget.h"
//#include "soundbutton.h"
#include "ui_embedwidget.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QTreeWidgetItem>


//class SoundButton : public QPushButton, public QStandardItem {
    //Q_OBJECT
//public:
        //explicit QLabelClickable( const QString& text="", QWidget* parent=0 );
    //~QLabelClickable();
//signals:
    //void clicked(int, int);
//protected:
    //void mousePressEvent(QMouseEvent* event);

//};

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget) {
    ui->setupUi(this);
    QStandardItemModel* model = new QStandardItemModel();
    //QTreeWidgetItem* item = new QTreeWidgetItem(QPushButton(""));

    QStandardItem* item1 = new QStandardItem(QIcon("test.png"), "ImageFile1.png");
    QStandardItem* item2 = new QStandardItem(QIcon("test.png"), "SoundFile1.ogg");
    QStandardItem* item3 = new QStandardItem(QIcon("test.png"), "SoundFile2.ogg");
    QStandardItem* soundButton = new QStandardItem("Add Sound");
    QStandardItem* item4 = new QStandardItem("OutputFile1.png");
    //QStandardItem* addImage = new QStandardItem(QIcon("test.png"), QPushButton("Add Image"));
    QStandardItem* addImage = new QStandardItem(QIcon("test.png"), "Add Image");

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
    item1->appendRow(soundButton);
    model->appendColumn(outputsList);

    // Sets the Column Headers
    model->setHeaderData(0, Qt::Horizontal, "Inputs", Qt::DisplayRole );
    model->setHeaderData(1, Qt::Horizontal, "Outputs", Qt::DisplayRole );

    // Add Soundbutton to the model
    //SoundButton sb;
    //model->appendRow(&sb);


    // Create one [Add Sound] Button
    //QWidget* addSoundWidget = new QWidget();
    //QPushButton* addSoundButton = new QPushButton();
    //addSoundButton->setText("Add Sound");

    //QHBoxLayout* pLayout = new QHBoxLayout(addSoundWidget);
    //pLayout->addWidget(addSoundButton);
    //pLayout->setAlignment(Qt::AlignCenter);
    //pLayout->setContentsMargins(0, 0, 0, 0);
    //addSoundWidget->setLayout(pLayout);

    ////ui->treeView->QAbstractItemView::setModel
    //model->appendRow(addSoundWidget);
    //model->setCellWidget(addSoundWidget);
    //ui->treeView->setCellWidget(0, 3, pWidget);

    // Set the current model
    ui->treeView->setModel(model);
}

// Creates an "Add Sound" button
QStandardItem* addSound() {
    QStandardItem* soundButton = new QStandardItem("Add Sound");
    return soundButton;
}

// Adds the image path to the tree hierarchy alongside an "Add Sound" button
QStandardItem* addImage(QString path) {
    QStandardItem* image = new QStandardItem(path);
    return image;
}

// Adds a new image with an "Add Sound" button to our model
void addToModel(QString path, QStandardItemModel* model) {
    QStandardItem* image = addImage(path);
    QStandardItem* soundButton = addSound();
    image->appendRow(soundButton);
    model->appendRow(image);
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
