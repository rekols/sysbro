#ifndef TOOLSPAGE_H
#define TOOLSPAGE_H

#include <QWidget>
#include "toolsview.h"
#include "toolslistmodel.h"

class ToolsPage : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsPage(QWidget *parent = nullptr);

    void leaveEvent(QEvent *);

private:
    void handleViewClicked(QModelIndex idx);

private:
    ToolsView *m_toolsView;
    ToolsListModel *m_listModel;
};

#endif // TOOLSPAGE_H
