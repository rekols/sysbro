#include "serviceview.h"
#include "servicemodel.h"
#include <QHeaderView>
#include <QMouseEvent>
#include <QMenu>

ServiceView::ServiceView(QWidget *parent)
    : QTreeView(parent)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setAlternatingRowColors(false);
    setRootIsDecorated(false);
    setSortingEnabled(false);
    setAutoScroll(true);
}

void ServiceView::setModel(QAbstractItemModel *model)
{
    QTreeView::setModel(model);

    QHeaderView *header = this->header();
    header->setSectionsMovable(false);
    header->setStretchLastSection(false);
    header->setSectionResizeMode(0, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Fixed);
//    header->setSectionResizeMode(2, QHeaderView::Fixed);

    header->resizeSection(1, 100);
//    header->resizeSection(2, 100);
}

void ServiceView::mousePressEvent(QMouseEvent *e)
{
    QTreeView::mousePressEvent(e);

    if (e->button() == Qt::RightButton) {
        QModelIndex index = indexAt(e->pos());

        if (!index.isValid())
            return;

        bool status = index.data(ServiceModel::Status).toBool();

        QMenu *menu = new QMenu;
        QAction *switchAction = new QAction((status ? tr("Disable") : tr("Enable")), this);

        connect(switchAction, &QAction::triggered, this, [=] {
            emit switchActionTriggered(index);
        });

        menu->addAction(switchAction);
        menu->move(QCursor::pos());
        menu->exec();
    }
}
