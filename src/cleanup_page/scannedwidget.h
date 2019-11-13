#ifndef SCANNEDWIDGET_H
#define SCANNEDWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include "treewidget.h"

class ScannedWidget : public QWidget
{
    Q_OBJECT

public:
    enum Categories {
        PACKAGE_CACHE,
        CRASH_REPORTS,
        APPLICATION_LOGS,
        APPLICATION_CACHES,
        BASHSHELL_HISTORY,
        TRASH
    };

    explicit ScannedWidget(QWidget *parent = nullptr);

    void addRoot(const Categories categories, const QString title,
                 const QFileInfoList infoList, bool noChild = false);
    void addChild(const QString data, const QString text,
                  const quint64 size, QTreeWidgetItem *parent);
    void addTreeChild(const Categories categories, const QString text, const quint64 size);

    void start();
    void scan();
    void clear();
    void systemClear();

signals:
    void scanFinished(quint64 totalSize);
    void clearFinished(quint64 totalSize);

private:
    void handleItemClicked(QTreeWidgetItem *item, const int column);
    void prepareMenu(const QPoint &pos);

private:
    TreeWidget *m_treeWidget;
    quint64 m_totalSize;
};

#endif // SCANNEDWIDGET_H
