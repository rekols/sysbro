#ifndef FILEITEMDELEGATE_H
#define FILEITEMDELEGATE_H

#include <QStyledItemDelegate>

class FileItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit FileItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // FILEITEMDELEGATE_H
