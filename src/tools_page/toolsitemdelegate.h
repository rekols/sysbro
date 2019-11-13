#ifndef TOOLSITEMDELEGATE_H
#define TOOLSITEMDELEGATE_H

#include <QStyledItemDelegate>

class ToolsItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ToolsItemDelegate(QObject *parent = nullptr);

    void paint(QPainter * painter,const QStyleOptionViewItem & option,const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TOOLSITEMDELEGATE_H
