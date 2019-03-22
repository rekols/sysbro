#include "toolslistmodel.h"

static const QMap<QString, QString> nameMap {
    {"sysbro-startup-apps", "开机自启动管理"},
    {"sysbro-file-shredder", "文件粉碎机"},
    {"sysbro-network-test", "网速测试"},
    {"sysbro-express", "快递查询助手"}
};

ToolsListModel::ToolsListModel(QObject *parent)
    : QAbstractListModel(parent),
      m_currentIndex(QModelIndex())
{
    m_list << "sysbro-startup-apps" // << "sysbro-file-shredder"
           << "sysbro-network-test" << "sysbro-express";
}

int ToolsListModel::rowCount(const QModelIndex &parent) const
{
    return m_list.size();
}

QVariant ToolsListModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();

    switch (role) {
    case AppNameRole:
        return nameMap.value(m_list.at(row));
    case AppKeyRole:
        return m_list.at(row);
    case CurrentIndexRole:
        return index == m_currentIndex;
    }

    return QVariant();
}

void ToolsListModel::setCurrentIndex(QModelIndex idx)
{
    m_currentIndex = idx;

    emit dataChanged(m_currentIndex, m_currentIndex);
}
