#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractTableModel>

class FileModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Role {
        FileName,
        FilePath,
        IsFile
    };

    explicit FileModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void append(const QStringList &filePaths);
    void removeItem(QModelIndex idx);
    void removeAllItems();
    void removeAllFiles();

signals:
    void removeAllFilesFinished(int count);

private:
    QStringList m_filePaths;
};

#endif // FILEMODEL_H
