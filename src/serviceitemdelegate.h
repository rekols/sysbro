#ifndef SPEEDUPITEMDELEGATE_H
#define SPEEDUPITEMDELEGATE_H

#include <QStyledItemDelegate>

class ServiceItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ServiceItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // SPEEDUPITEMDELEGATE_H
