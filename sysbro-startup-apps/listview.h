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

protected:
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // LISTVIEW_H
