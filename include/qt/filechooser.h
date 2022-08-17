#pragma once
#ifndef QFILECHOOSER_H
#define QFILECHOOSER_H

//#include <QObject>
//#include <QPushButton>
//#include <QtDesigner/QDesignerCustomWidgetInterface>
//#include <QFileDialog>

//#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class FileChooser; }
QT_END_NAMESPACE

//class FileChooser : public QWidget, QLineEdit {
class FileChooser : public QLineEdit {
    Q_OBJECT

private:
    Ui::FileChooser *ui;

signals:
    void clicked();

public:
    explicit FileChooser(QWidget *parent = nullptr);
    //FileChooser(QObject *parent = nullptr);
    ~FileChooser();
    void click();
    
};



//class FileChooser : public QObject, public QDesignerCustomWidgetInterface {
    //Q_OBJECT
    //Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")
    //Q_INTERFACES(QDesignerCustomWidgetInterface)
//public:
    //explicit FileChooser(QObject *parent = nullptr);

    //bool isContainer() const override;
    //bool isInitialized() const override;
    //QIcon icon() const override;
    //QString domXml() const override;
    //QString group() const override;
    //QString includeFile() const override;
    //QString name() const override;
    //QString toolTip() const override;
    //QString whatsThis() const override;
    //QWidget *createWidget(QWidget *parent) override;
    //void initialize(QDesignerFormEditorInterface *core) override;

//private:
    //bool initialized = false;
//};

#endif // QFILECHOOSER_H
