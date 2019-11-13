#include "toolspage.h"
#include "toolsitemdelegate.h"
#include <QProcess>
#include <QVBoxLayout>
#include <QDebug>

ToolsPage::ToolsPage(QWidget *parent)
    : QWidget(parent),
      m_toolsView(new ToolsView),
      m_listModel(new ToolsListModel)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_toolsView);
    layout->setMargin(20);

    // m_toolsView->setViewMode(QListView::IconMode);
    m_toolsView->setItemDelegate(new ToolsItemDelegate);
    // m_toolsView->setMouseTracking(true);
    // m_toolsView->setDragEnabled(false);
    // m_toolsView->setAutoScroll(false);
    m_toolsView->setModel(m_listModel);
    // m_toolsView->setWrapping(true);

    setLayout(layout);

    connect(m_toolsView, &QListView::entered, m_listModel, &ToolsListModel::setCurrentIndex);
    connect(m_toolsView, &QListView::clicked, this, &ToolsPage::handleViewClicked);
}

void ToolsPage::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);

    m_listModel->setCurrentIndex(QModelIndex());
}

void ToolsPage::handleViewClicked(QModelIndex idx)
{
    // startup application.
    QString appExec = idx.data(ToolsListModel::AppKeyRole).toString();
    QProcess::startDetached(appExec);
}
