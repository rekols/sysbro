#include "filemodel.h"
#include <QFileInfo>
#include <QProcess>

FileModel::FileModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    return m_filePaths.size();
}

int FileModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QString filePath = m_filePaths.at(index.row());
    QFileInfo fileInfo(filePath);

    switch (role) {
    case FileName:
        return fileInfo.fileName();
    case FilePath:
        return filePath;
    case IsFile:
        return fileInfo.isFile();
    }

    return QVariant();
}

QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
    case 0:
        return tr("File Name");
    case 1:
        return tr("File Path");
    }

    return QVariant();
}

void FileModel::append(const QStringList &filePaths)
{
    // int row = m_filePaths.size();

    beginResetModel();
    for (const QString &filePath : filePaths) {
        if (!m_filePaths.contains(filePath)) {
            m_filePaths << filePath;
        }
    }
    endResetModel();
}

void FileModel::removeItem(QModelIndex idx)
{
    QString filePath = idx.data(FilePath).toString();

    beginResetModel();
    m_filePaths.removeOne(filePath);
    endResetModel();
}

void FileModel::removeAllItems()
{
    beginResetModel();
    m_filePaths.clear();
    endResetModel();
}

void FileModel::removeAllFiles()
{
    if (m_filePaths.isEmpty())
        return;

    int count = m_filePaths.count();

    QProcess *process = new QProcess;
    bool failed = false;
    process->start("pkexec", QStringList() << "sysbro-delete-files" << m_filePaths);
    process->waitForFinished(-1);
    failed |= process->exitCode();
    process->deleteLater();

    if (!failed) {
        removeAllItems();

        emit removeAllFilesFinished(count);
    }
}
