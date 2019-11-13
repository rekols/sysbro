#include "treeitemdelegate.h"

TreeItemDelegate::TreeItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void TreeItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}

QSize TreeItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(-1, 40);
}
