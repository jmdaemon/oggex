#include "filechooser.h"

FileChooser::FileChooser(QWidget *parent)
    : QLineEdit(parent), ui(new Ui::FileChooser) {

    ui->setupUi(this);
}

FileChooser::~FileChooser() {
    delete ui;
}

QString FileChooser::getPath() {
    return this->path;
}

void FileChooser::setPath(QString path) {
    this->path = path;
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
void FileChooser::browse(QString prompt, QString filetypes, QString dir, bool shortpaths) {
    qDebug("Opening File Chooser Dialog");
    auto fileName = QFileDialog::getOpenFileName(this, prompt, dir, filetypes);

    if (!fileName.isEmpty()) {
        qDebug() << "Selected: " << fileName;
        this->setPath(fileName); // Save the full path for later

        // Truncate and display just the file name
        if (shortpaths) {
            QFileInfo file(fileName);
            qDebug() << "File: " << file.fileName();
            this->setText(file.fileName());
        }
    }
}
