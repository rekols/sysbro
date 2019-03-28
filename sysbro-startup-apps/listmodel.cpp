#include "listmodel.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QDebug>

ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent),
      m_autoStartManager(AutoStartManager::instance()),
      m_currentIndex(QModelIndex())
{
    connect(m_autoStartManager, &AutoStartManager::dataChanged, this, [=] {
        emit layoutChanged();
    });
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_autoStartManager->appList().size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    DesktopInfo appInfo = m_autoStartManager->appList().at(row);

    switch (role) {
    case AppNameRole:
        return appInfo.name;
    case AppIconRole:
        return appInfo.iconName;
    case AppExecRole:
        return appInfo.exec;
    case AppPathRole:
        return appInfo.filePath;
    case CurrentIndex:
        return index == m_currentIndex;
    }

    return QVariant();
}

void ListModel::setCurrentIndex(QModelIndex idx)
{
    m_currentIndex = idx;

    emit dataChanged(m_currentIndex, m_currentIndex);
}

void ListModel::removeCurrentIndex()
{
    if (m_currentIndex.isValid()) {
        QFile file(m_currentIndex.data(ListModel::AppPathRole).toString());
        file.remove();
        file.close();
    }
}
