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
void FileChooser::browse(QString prompt, QString filetypes, QString dir) {
    qDebug("Opening File Chooser Dialog");
    auto fileName = QFileDialog::getOpenFileName(this, prompt, dir, filetypes);

    if (!fileName.isEmpty()) {
        qDebug() << "Selected: " << fileName;
        this->setText(fileName);
    }
}
