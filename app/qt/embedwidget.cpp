#include "embedwidget.h"
#include <QSignalMapper>

EmbedWidget::EmbedWidget(QWidget *parent)
    //: QWidget(parent), ui(new Ui::EmbedWidget), model(new DataModel()) {
    : QWidget(parent), ui(new Ui::EmbedWidget) {

    ui->setupUi(this);

    // Set the current model
    //ui->treeView->setModel(model);
    //connect(ui->lbl_image, SIGNAL(clicked()), this, SLOT(browse()));
    //connect(ui->lbl_image, SIGNAL(clicked()), this, SLOT(browse()));
    //connect(ui->lbl_image, SIGNAL(ui->lbl_image.clicked()), this, SLOT(browse()));
    
    //ui->lbl_image->installEventFilter(this);
    //QApplication::focusChanged(this, ui->lbl_image)
    //connect(ui->lbl_image, ui->lbl_image->clicked(), this, SLOT(browse()));
    //connect(ui->lbl_image, SIGNAL(ui->lbl_image->clicked()),
            //this, SLOT(browse()));
    //connect(ui->lbl_image, &QPushButton::clicked, this, SLOT(browse()));
    //connect(ui->lbl_image, &QPushButton::clicked, this, &EmbedWidget::browse);
    //connect(ui->lbl_image, &QPushButton::clicked, this, &EmbedWidget::browse);
    //connect(ui->lbl_image, &FileChooser::clicked, this, &EmbedWidget::browse);
    //connect(ui->lbl_image, SIGNAL(&FileChooser::clicked()), this, SLOT(&EmbedWidget::browse));
    //connect(qobject_cast<FileChooser*>(ui->lbl_image), ui->lbl_image->clicked()), this, SLOT(&EmbedWidget::browse));
    //connect(ui->le_image, &FileChooser::clicked, this, &EmbedWidget::browse);
    //connect(ui->le_image, SIGNAL(&FileChooser::clicked), this, SLOT(&EmbedWidget::browse));
    //connect(ui->le_image, ui->le_image->clicked(true), this, &EmbedWidget::browse);


    // Signal Maps
    //auto sigmap = new QSignalMapper(this);

    //connect(ui->le_image, SIGNAL(clicked()), sigmap, SLOT(map()));
    ////connect(m_action_file_open, SIGNAL(triggered()), sigmap, SLOT(map()));

    //sigmap->setMapping(ui->le_image, true);
    ////sigmap->setMapping(m_action_file_open, "File->Open");

    //connect(sigmap, SIGNAL(mapped(QBool)), this, SLOT(clicked(bool)));

    //connect(ui->le_image, ui->le_image->clicked(true), this, browse("", ""));
    //connect(ui->le_image, &FileChooser::clicked, this, &EmbedWidget::browse);

    connect(ui->le_image, &FileChooser::clicked, this, [this]() {
    //connect(ui->le_image, &FileChooser::focus, this, [this]() {
            browse("Open Image", "Image Files (*.png *.jpg *.bmp)");
        });
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}

bool EmbedWidget::eventFilter(QObject* object, QEvent* event) {
    qInfo() << "Object" << object;
    //if(qobject_cast<QLabel*>(object) == ui->lbl_image && event->type() == QEvent::FocusIn) {
    qInfo() << "Event Type: " << event->type();
    //if ((event->type() == QEvent::FocusIn) || (event->type() == QEvent::MouseButtonPress)) {
    //if (object == ui->lbl_image && event->type() == QEvent::WindowActivate) {
    //if (object == ui->lbl_image && event->type() == QEvent::MouseButtonPress) {
    if ((object == ui->lbl_image) && (event->type() == QEvent::MouseButtonPress)) {
        // bring up your custom edit
        qInfo("Running browse()");
        //browse(ui->lbl_image->text(), "Image Files (*.png *.jpg *.bmp)");
        browse("Open Image", "Image Files (*.png *.jpg *.bmp)");
        return true;
        //return false; // lets the event continue to the edit
    }
    //qInfo("Ignoring Events");
    return false;
}

void EmbedWidget::browse(QString prompt, QString filetypes) {
    //QString directory = QFileDialog::getExistingDirectory(this, prompt, QDir::currentPath());
    //auto directory = QFileDialog::getExistingDirectory(this, prompt, QDir::currentPath());
    auto fileName = QFileDialog::getOpenFileName(this, prompt, "~", filetypes);
    qInfo("Selecting file");

    // We select a file
    //if (!directory.isEmpty()) {
    if (!fileName.isEmpty()) {
        qInfo() << "fileName: " << fileName;
        //ui->lbl_image->setText(directory);
        ui->lbl_image->setText(fileName);
        //if (directoryComboBox->findText(directory) == -1)
            //directoryComboBox->addItem(directory);
        //directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
    }
}
