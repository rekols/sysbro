#include "treewidget.h"
#include "treeitemdelegate.h"
#include <QApplication>
#include <QScrollBar>
#include <QHeaderView>
#include <QDebug>

TreeWidget::TreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    // setRootIsDecorated(false);
    setItemDelegate(new TreeItemDelegate);
    setFrameShape(QFrame::NoFrame);
    setSelectionMode(NoSelection);
    setHeaderHidden(true);
    // setAnimated(false);

    setStyleSheet("QTreeView {"
                  "border: none;"
                  "border-radius: 5px;"
                  "}"
                  ""
                  "QTreeView::branch:!has-children {"
                  "border: none;"
                  "}"
                  "");
}

void TreeWidget::mouseDoubleClickEvent(QMouseEvent *)
{

}

