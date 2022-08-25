#pragma once
#ifndef QFILECHOOSER_H
#define QFILECHOOSER_H

// QT Widgets
#include <QWidget>
#include <QLineEdit>
#include <QFileDialog>

// QTUI File
#include "ui_filechooser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FileChooser; }
QT_END_NAMESPACE

class FileChooser : public QLineEdit {
    Q_OBJECT

private:
    Ui::FileChooser *ui;

public:
    explicit FileChooser(QWidget *parent = nullptr);
    ~FileChooser();

signals:
    void clicked(bool wasClicked);
    void focus(bool hasFocus);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);

public slots:
    void browse(QString prompt, QString filetypes, QString dir, bool shortpaths);

};

#endif // QFILECHOOSER_H
