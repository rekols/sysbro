#ifndef TOOLSLISTMODEL_H
#define TOOLSLISTMODEL_H

#include <QAbstractListModel>

class ToolsListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum DataRole {
        AppNameRole,
        AppKeyRole,
        CurrentIndexRole
    };

    explicit ToolsListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void setCurrentIndex(QModelIndex idx);

private:
    QStringList m_list;
    QModelIndex m_currentIndex;
    QMap<QString, QString> m_nameMap;
};

#endif // TOOLSLISTMODEL_H
