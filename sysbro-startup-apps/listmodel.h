#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include "autostartmanager.h"

class ListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum AppRole {
        AppNameRole = Qt::UserRole + 1,
        AppIconRole,
        AppExecRole,
        AppPathRole,
        CurrentIndex
    };

    explicit ListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    void setCurrentIndex(QModelIndex idx);

private:
    QStringList m_list;
    AutoStartManager *m_autoStartManager;
    QModelIndex m_currentIndex;
};

#endif // LISTMODEL_H
