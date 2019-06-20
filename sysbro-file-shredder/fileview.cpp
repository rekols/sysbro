#include "fileview.h"
#include <QHeaderView>
#include <QMouseEvent>
#include <QMenu>

FileView::FileView(QWidget *parent)
    : QTableView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setAlternatingRowColors(false);
    setSortingEnabled(false);
    setShowGrid(false);
    setAutoScroll(false);

    setStyleSheet("QTableView {"
                  "border: none;"
                  "border-bottom: 1px solid #F2F2F2;"
                  "}"
                  "QHeaderView::section {"
                  "background-color: rgb(255, 255, 255);"
                  "border: none;"
                  "height: 32px;"
                  "font-style: normal;"
                  "font-weight: normal;"
                  "font-size: 15px;"
                  "}"
                  "QHeaderView::section:horizontal {"
                  "border-top: 1px solid #F2F2F2;"
                  "border-bottom: 1px solid #F2F2F2;"
                  "border-right: 1px solid #F2F2F2;"
                  "padding-left: 15px;"
                  "}");
}

void FileView::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);

    QHeaderView *headerView = horizontalHeader();
    verticalHeader()->setDefaultSectionSize(30);
    headerView->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    headerView->setSectionResizeMode(0, QHeaderView::Fixed);
    headerView->setSectionResizeMode(1, QHeaderView::Stretch);
    headerView->setHighlightSections(false);

    // set row height.
    QHeaderView *vheaderView = verticalHeader();
    vheaderView->setDefaultSectionSize(42);
    setColumnWidth(0, 300);
    setColumnWidth(1, 170);
}

void FileView::mousePressEvent(QMouseEvent *e)
{
    QTableView::mousePressEvent(e);

    if (e->button() == Qt::RightButton) {
        QModelIndex idx = indexAt(e->pos());

        if (!idx.isValid())
            return;

        QMenu *menu = new QMenu;
        QAction *removeAction = new QAction(tr("Remove from list"));

        connect(removeAction, &QAction::triggered, this, [=] {
            emit removeItem(idx);
        });

        menu->addAction(removeAction);
        menu->move(QCursor::pos());
        menu->exec();

    }
}
