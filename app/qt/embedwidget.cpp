#include "embedwidget.h"
//#include "filechooser.h"

//#include "ui_filechooser.h"
#include "ui_embedwidget.h"
//#include "ui_qfilechooser.h"
//#include "ui_filechooser.h"

#include <QFileDialog>

EmbedWidget::EmbedWidget(QWidget *parent)
    //: QWidget(parent), ui(new Ui::EmbedWidget), model(new DataModel()) {
    : QWidget(parent), ui(new Ui::EmbedWidget) {

    ui->setupUi(this);

    // Set the current model
    //ui->treeView->setModel(model);
}

EmbedWidget::~EmbedWidget() {
    delete ui;
}
