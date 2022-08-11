#pragma once
#ifndef OGGEX_DATAMODEL_H
#define OGGEX_DATAMODEL_H

#include <QAbstractTableModel>

class DataModel : public QAbstractTableModel {
    Q_OBJECT
public:
    DataModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // OGGEX_DATAMODEL_H
