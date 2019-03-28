#include "listview.h"
#include <QMouseEvent>
#include <QDebug>

ListView::ListView(QWidget *parent)
    : QListView(parent)
{
    setVerticalScrollMode(ScrollPerPixel);
    setSelectionMode(NoSelection);
    setAlternatingRowColors(false);
    setMouseTracking(true);
    setAutoScroll(false);
}

void ListView::mousePressEvent(QMouseEvent *e)
{
    QListView::mousePressEvent(e);

    if (e->button() == Qt::RightButton) {
        emit rightClicked(indexAt(e->pos()));
    }
}

void ListView::mouseMoveEvent(QMouseEvent *e)
{
    QModelIndex idx = indexAt(e->pos());

    emit entered(idx);
}

void ListView::enterEvent(QEvent *e)
{
    e->ignore();
}

void ListView::leaveEvent(QEvent *e)
{
    QListView::leaveEvent(e);

    emit entered(QModelIndex());
}
