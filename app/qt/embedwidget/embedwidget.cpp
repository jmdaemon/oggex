#include "embedwidget.h"
#include "ui_embedwidget.h"

EmbedWidget::EmbedWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::EmbedWidget) {
    ui->setupUi(this);

    QStandardItemModel* model = new QStandardItemModel();

    auto image  = makeEntry("ImageFile1.png");
    auto sound1 = makeEntry("SoundFile1.ogg");
    auto sound2 = makeEntry("SoundFile2.ogg");
    auto sb     = makeSoundButton();
    auto output = makeEntry("OutputFile1.png");

    QList<QStandardItem*> outputsList = { output };

    // Set up the hierarchy as:
    // First Column:
    // ImageFile1
    //  - Sound File1
    //  - Sound File2
    // Second Column
    //  - Sound File2
    addSound(sound1, image);
    addSound(sound2, image);
    addSound(sb, image);
    addImage(image, model);

    model->appendColumn(outputsList);
    setHeaders(model);

    // Set the current model
    ui->treeView->setModel(model);
}
// Creates an "Add Sound" entry
QStandardItem* EmbedWidget::makeSoundButton() {
    QStandardItem* soundButton = new QStandardItem("Add Sound");
    return soundButton;
}

// Creates the image entry in the model
QStandardItem* EmbedWidget::makeEntry(QString path) {
    QStandardItem* image = new QStandardItem(path);
    return image;
}

// Sets the Column Headers
void EmbedWidget::setHeaders(QStandardItemModel* model) {
    model->setHeaderData(0, Qt::Horizontal, "Inputs", Qt::DisplayRole );
    model->setHeaderData(1, Qt::Horizontal, "Outputs", Qt::DisplayRole );
}

// Adds the sound to the image
void EmbedWidget::addSound(QStandardItem* sound, QStandardItem* image) {
    image->appendRow(sound);
}

// Adds the image path to the model
void EmbedWidget::addImage(QStandardItem* image, QStandardItemModel* model) {
    model->appendRow(image);
}

// Adds a new image with an "Add Sound" button to our model
void EmbedWidget::addToModel(QString path, QStandardItemModel* model) {
    QStandardItem* image = makeEntry(path);
    QStandardItem* soundButton = makeSoundButton();
    image->appendRow(soundButton);
    model->appendRow(image);
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
