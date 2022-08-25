#include "extractwidget.h"

ExtractWidget::ExtractWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExtractWidget)
{
    ui->setupUi(this);
}

ExtractWidget::~ExtractWidget()
{
    delete ui;
}
