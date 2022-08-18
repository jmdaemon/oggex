#include "filechooser.h"

FileChooser::FileChooser(QWidget *parent)
    : QLineEdit(parent), ui(new Ui::FileChooser) {

    ui->setupUi(this);
}

FileChooser::~FileChooser() {
    delete ui;
}

// Signals

// Focus
void FileChooser::focusInEvent(QFocusEvent *e) {
    QLineEdit::focusInEvent(e);
    emit(focus(true));
}

void FileChooser::focusOutEvent(QFocusEvent *e) {
    QLineEdit::focusOutEvent(e);
    emit(focus(false));
}

// Mouse Click
void FileChooser::mouseReleaseEvent(QMouseEvent *e) {
    QLineEdit::mouseReleaseEvent(e);
    emit(clicked(true));
}

// Slots

// TODO:
// - Add option to shorten file paths to just file names.
// - Add feature to remember/reopen session directories.
void FileChooser::browse(QString prompt, QString filetypes) {
    //QString directory = QFileDialog::getExistingDirectory(this, prompt, QDir::currentPath());
    //auto directory = QFileDialog::getExistingDirectory(this, prompt, QDir::currentPath());
    auto fileName = QFileDialog::getOpenFileName(this, prompt, "~", filetypes);
    qInfo("Selecting file");

    // We select a file
    //if (!directory.isEmpty()) {
    if (!fileName.isEmpty()) {
        qInfo() << "fileName: " << fileName;
        //ui->lbl_image->setText(directory);
        //ui->le_image->setText(fileName);
        this->setText(fileName);
        //if (directoryComboBox->findText(directory) == -1)
            //directoryComboBox->addItem(directory);
        //directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
    }
}
