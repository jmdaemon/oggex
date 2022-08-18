#pragma once
#ifndef QFILECHOOSER_H
#define QFILECHOOSER_H

// QT Widgets
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

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
    //void mouseReleaseEvent(QMouseEvent *e) override {
        ////setText("I have been clicked!");//you can change the text here directly on click
        ////QLabel::mouseReleaseEvent(ev);
      //QLineEdit::mouseReleaseEvent(e);
        //emit clicked();//or you can emit a signal, and use it elsewhere
    //}

signals:
    void clicked(bool wasClicked);
    void focus(bool hasFocus);

protected:
  //virtual void click(QMouseEvent *e);
  virtual void mouseReleaseEvent(QMouseEvent *e);
  virtual void focusInEvent(QFocusEvent *e);
  virtual void focusOutEvent(QFocusEvent *e);

//public slots:
    //void clicked();

};

#endif // QFILECHOOSER_H
