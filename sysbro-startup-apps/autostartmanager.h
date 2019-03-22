#ifndef AUTOSTARTMANAGER_H
#define AUTOSTARTMANAGER_H

#include <QObject>
#include <QFileSystemWatcher>
#include "desktopproperties.h"

class DesktopInfo
{
public:
    QString name;
    QString genericName;
    QString iconName;
    QString exec;
    QString filePath;

    inline bool operator==(const DesktopInfo &other) {
        return filePath == other.filePath;
    }
};

class AutoStartManager : public QObject
{
    Q_OBJECT

public:
    static AutoStartManager *instance();
    explicit AutoStartManager(QObject *parent = nullptr);

    const QList<DesktopInfo> &appList() const { return m_appList; }

    void loadApps();
    void addNewApp(const QString appName, const QString appExec);
    void setValue(const QString &filePath, const QString &key, const QString &value);

signals:
    void dataChanged();

private:
    QString m_autoStartPath;
    QFileSystemWatcher *m_fileSystemWatcher;
    QList<DesktopInfo> m_appList;
};

#endif // AUTOSTARTMANAGER_H
