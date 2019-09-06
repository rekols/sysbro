#include "scannedwidget.h"
#include "utils.h"
#include <QDir>
#include <QVBoxLayout>
#include <QTreeWidgetItem>
#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QtConcurrent>

ScannedWidget::ScannedWidget(QWidget *parent)
    : QWidget(parent),
      m_treeWidget(new TreeWidget)
{
    QVBoxLayout *layout = new QVBoxLayout;

    m_treeWidget->setColumnCount(2);
    m_treeWidget->setColumnWidth(0, 600);
    m_treeWidget->setHeaderLabels({tr("File Name"), tr("File Size")});

    layout->addWidget(m_treeWidget);
    layout->setContentsMargins(30, 0, 30, 0);
    setLayout(layout);

    connect(m_treeWidget, &QTreeWidget::itemClicked, this, &ScannedWidget::handleItemClicked);
}

void ScannedWidget::addRoot(const ScannedWidget::Categories categories, const QString title,
                            const QFileInfoList infoList, bool noChild)
{
    QTreeWidgetItem *rootItem = new QTreeWidgetItem;
    rootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
    rootItem->setData(2, 0, categories);
    rootItem->setData(2, 1, title);

    m_treeWidget->addTopLevelItem(rootItem);

    if (!infoList.isEmpty()) {
        rootItem->setData(3, 0, infoList.at(0).absoluteDir().path());
    }
    rootItem->setCheckState(0, Qt::Unchecked);

    quint64 totalSize = 0;

    if (!noChild) {
        int itemCount = 0;

        for (const QFileInfo &info : infoList) {
            const QString path = info.absoluteFilePath();
            quint64 fileSize = Utils::getFileSize(path);

            if (fileSize == 0) {
                continue;
            }

            addChild(path, info.fileName(), fileSize, rootItem);

            totalSize += fileSize;
            ++itemCount;
        }

        rootItem->setText(0, QString("%1 (%2)").arg(title).arg(itemCount));
    } else {
        if (!infoList.isEmpty()) {
            totalSize += Utils::getFileSize(infoList.first().absoluteFilePath());
        }

        rootItem->setText(0, QString("%1").arg(title));
    }

    m_totalSize += totalSize;

    rootItem->setText(1, QString("%1").arg(Utils::formatBytes(totalSize)));
}

void ScannedWidget::addChild(const QString data, const QString text,
                             const quint64 size, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setIcon(0, QIcon::fromTheme(text, QIcon::fromTheme("application-x-executable")));
    item->setText(0, text);
    item->setText(1, Utils::formatBytes(size));
    item->setData(2, 0, data);
    item->setCheckState(0, Qt::Unchecked);
}

void ScannedWidget::addTreeChild(const ScannedWidget::Categories categories, const QString text, const quint64 size)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(m_treeWidget);
    item->setText(0, text);
    item->setText(1, Utils::formatBytes(size));
    item->setData(2, 0, categories);
    item->setCheckState(0, Qt::Unchecked);
}

void ScannedWidget::start()
{
    QtConcurrent::run(this, &ScannedWidget::scan);
}

void ScannedWidget::scan()
{
    m_totalSize = 0;
    m_treeWidget->clear();

    // addRoot(TRASH, "Trash", { QFileInfo(QString("%1/.local/share/Trash/").arg(Utils::getHomePath())) }, true);
    addRoot(APPLICATION_CACHES, tr("Application Caches"), Utils::getAppCaches());
    addRoot(APPLICATION_LOGS, tr("Application Log"), Utils::getAppLogs());
    addRoot(CRASH_REPORTS, tr("Crash Reports"), Utils::getCrashReports());
    addRoot(PACKAGE_CACHE, tr("Package Caches"), Utils::getDpkgPackages());

    QFileInfo bashShellHistory(QDir::homePath() + "/.bash_history");
    if (bashShellHistory.exists()) {
        addRoot(BASHSHELL_HISTORY, tr("Shell Terminal History"), { bashShellHistory });
    }

    m_treeWidget->update();

    emit scanFinished(m_totalSize);
}

void ScannedWidget::clear()
{
    QtConcurrent::run(this, &ScannedWidget::systemClear);
}

void ScannedWidget::systemClear()
{
    m_treeWidget->setEnabled(false);

    quint64 totalCleanedSize = 0;
    QStringList fileToDeleteList;
    QList<QTreeWidgetItem *> childrens;

    for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *it = m_treeWidget->topLevelItem(i);
        Categories cat = (Categories) it->data(2, 0).toInt();

        if (cat != Categories::TRASH) {
            for (int j = 0; j < it->childCount(); ++j) {
                if (it->child(j)->checkState(0) == Qt::Checked) {
                    const QString filePath = it->child(j)->data(2, 0).toString();
                    fileToDeleteList << filePath;
                    childrens.append(it->child(j));
                }
            }
        } else if (cat == Categories::TRASH) {
            if (it->checkState(0) == Qt::Checked) {
                QString homePath = Utils::getHomePath();
                QDir(homePath + "/.local/share/Trash/files").removeRecursively();
                QDir(homePath + "/.local/share/Trash/info").removeRecursively();
            }
        }
    }

    // get removed files total size.
    for (const QString &filePath : fileToDeleteList) {
        totalCleanedSize += Utils::getFileSize(filePath);
    }

    // remove selected files.
    if (!fileToDeleteList.isEmpty()) {
        QProcess *process = new QProcess;
        bool failed = false;
        process->start("pkexec", QStringList() << "sysbro-delete-files" << fileToDeleteList);
        process->waitForFinished(-1);
        failed |= process->exitCode();
        process->deleteLater();

        if (!failed) {
            // remove all children.
            for (int i = 0; i < m_treeWidget->topLevelItemCount(); ++i) {
                qDeleteAll(m_treeWidget->topLevelItem(i)->takeChildren());
            }

            emit clearFinished(totalCleanedSize);
        }
    }

    m_treeWidget->setEnabled(true);
}

void ScannedWidget::handleItemClicked(QTreeWidgetItem *item, const int column)
{
    if (column != 0) {
        return;
    }

//    Qt::CheckState state = item->checkState(column) == Qt::Checked ? Qt::Unchecked : Qt::Checked;

//    item->setCheckState(column, state);

    for (int i = 0; i < item->childCount(); ++i) {
        item->child(i)->setCheckState(column, item->checkState(column) == Qt::Checked ? Qt::Checked : Qt::Unchecked);
    }
}
