#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QAbstractItemDelegate>
#include <QModelIndex>
#include <QStyleOptionViewItem>
#include <QPainter>

class ItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT

public:
    explicit ItemDelegate(QObject *parent = 0);

signals:
    void removeBtnClicked();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ITEMDELEGATE_H
