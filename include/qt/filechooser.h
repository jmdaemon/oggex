#pragma once
#ifndef QFILECHOOSER_H
#define QFILECHOOSER_H

// QT Widgets
#include <QWidget>
#include <QLineEdit>

// QTUI File
#include "ui_filechooser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FileChooser; }
QT_END_NAMESPACE

class FileChooser : public QLineEdit {
    Q_OBJECT

private:
    Ui::FileChooser *ui;

signals:
    void clicked();

public:
    explicit FileChooser(QWidget *parent = nullptr);
    ~FileChooser();
    void click();
    
};

#endif // QFILECHOOSER_H
