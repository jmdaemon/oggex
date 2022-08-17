#include "filechooser.h"

//#include "filechooser.h"
#include "ui_qfilechooser.h"

FileChooser::FileChooser(QWidget *parent)
    //: QWidget(parent), ui(new Ui::FileChooser) {
    : QLineEdit(parent), ui(new Ui::FileChooser) {

    ui->setupUi(this);
}

FileChooser::~FileChooser() {
    delete ui;
}

void FileChooser::click() {
    emit clicked();
}
