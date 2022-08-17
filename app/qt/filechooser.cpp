#include "filechooser.h"

FileChooser::FileChooser(QWidget *parent)
    : QLineEdit(parent), ui(new Ui::FileChooser) {

    ui->setupUi(this);
}

FileChooser::~FileChooser() {
    delete ui;
}

void FileChooser::click() {
    emit clicked();
}
