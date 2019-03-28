#include "toolsview.h"
#include <QMouseEvent>
#include <QEvent>

ToolsView::ToolsView(QWidget *parent)
    : QListView(parent),
      m_currentIndex(QModelIndex())
{
    // viewport()->installEventFilter(this);

    setFlow(QListView::LeftToRight);
    setLayoutMode(QListView::Batched);
    setResizeMode(QListView::Adjust);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setFrameStyle(QFrame::NoFrame);
    setMouseTracking(true);
    setWrapping(true);
}

ToolsView::~ToolsView()
{
}

void ToolsView::mouseMoveEvent(QMouseEvent *e)
{
    QModelIndex idx = indexAt(e->pos());

    if (m_currentIndex != idx) {
        m_currentIndex = idx;

        emit entered(m_currentIndex);
    }
}

// bool ToolsView::eventFilter(QObject *object, QEvent *e)
// {
//     if (object == viewport() && e->type() == QEvent::Paint) {
//         // fitToContent();
//     }

//     return false;
// }

// void ToolsView::fitToContent()
// {
//     if (width() == contentsRect().width() &&
//         height() == contentsSize().height()) {
//         return;
//     }

//     const int h = contentsSize().height();

//     setFixedHeight(h < 0 ? 0 : h);
//     setFixedWidth(contentsRect().width());
// }
