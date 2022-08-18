#include "filechooser.h"

FileChooser::FileChooser(QWidget *parent)
    : QLineEdit(parent), ui(new Ui::FileChooser) {

    ui->setupUi(this);
}

FileChooser::~FileChooser() {
    delete ui;
}

// Signals
void FileChooser::focusInEvent(QFocusEvent *e) {
    QLineEdit::focusInEvent(e);
    emit(focus(true));
}

void FileChooser::focusOutEvent(QFocusEvent *e) {
    QLineEdit::focusOutEvent(e);
    emit(focus(false));
}

//void FileChooser::click(QMouseEvent *e) {
void FileChooser::mouseReleaseEvent(QMouseEvent *e) {
    //QPushButton::mouseDoubleClickEvent(e);
    //QPushButton::(e);
    //QPushButton::clicked(e);
    //QWidget::mouseDoubleClickEvent(e);
    QLineEdit::mouseReleaseEvent(e);
    emit(clicked(true));
}
