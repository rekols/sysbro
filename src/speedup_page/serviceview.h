#ifndef SPEEDUPVIEW_H
#define SPEEDUPVIEW_H

#include <QTreeView>

class ServiceView : public QTreeView
{
    Q_OBJECT

public:
    explicit ServiceView(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model);

signals:
    void switchActionTriggered(QModelIndex idx);

protected:
    void mousePressEvent(QMouseEvent *e);
};

#endif // SPEEDUPVIEW_H
