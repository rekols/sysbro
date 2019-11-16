#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QTableView>

class FileView : public QTableView
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model);

signals:
    void removeItem(QModelIndex idx);

protected:
    void mousePressEvent(QMouseEvent *);
};

#endif // FILEVIEW_H
