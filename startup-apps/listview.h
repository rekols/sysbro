#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>

class ListView : public QListView
{
    Q_OBJECT

public:
    explicit ListView(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *);

signals:
    void rightClicked(QModelIndex idx);
    void currentHoverChanged(const QModelIndex &previous, const QModelIndex &current);

protected:
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    void onItemEntered(QModelIndex idx);
    void onCurrentHoverChanged(const QModelIndex &previous, const QModelIndex &current);

private:
    QModelIndex m_currentIndex;
    QModelIndex m_previousIndex;
};

#endif // LISTVIEW_H
