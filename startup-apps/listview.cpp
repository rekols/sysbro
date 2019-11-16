#include "listview.h"
#include "listmodel.h"
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

    connect(this, &QListView::entered, this, &ListView::onItemEntered);
    connect(this, &ListView::currentHoverChanged, this, &ListView::onCurrentHoverChanged);
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

void ListView::onItemEntered(QModelIndex idx)
{
    m_currentIndex = idx;

    static_cast<ListModel *>(model())->setCurrentIndex(idx);

    if (m_currentIndex != m_previousIndex) {
        Q_EMIT currentHoverChanged(m_previousIndex, m_currentIndex);
        m_previousIndex = m_currentIndex;
    }
}

void ListView::onCurrentHoverChanged(const QModelIndex &previous, const QModelIndex &current)
{
    if (previous.isValid()) {
        closePersistentEditor(previous);
    }

    openPersistentEditor(current);
}
