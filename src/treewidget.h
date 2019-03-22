#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>

class TreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = nullptr);

    void mouseDoubleClickEvent(QMouseEvent *);
};

#endif // TREEWIDGET_H
