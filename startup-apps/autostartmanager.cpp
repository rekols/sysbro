#include "autostartmanager.h"
#include <QRegularExpression>
#include <QStandardPaths>
#include <QDirIterator>
#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QDir>

static AutoStartManager *INSTANCE = nullptr;

AutoStartManager *AutoStartManager::instance()
{
    if (INSTANCE == nullptr) {
        INSTANCE = new AutoStartManager;
    }

    return INSTANCE;
}

AutoStartManager::AutoStartManager(QObject *parent)
    : QObject(parent),
      m_autoStartPath(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).append("/autostart/")),
      m_fileSystemWatcher(new QFileSystemWatcher(this))
{
    if (!QDir(m_autoStartPath).exists()) {
        QDir().mkdir(m_autoStartPath);
    }

    m_fileSystemWatcher->addPath(m_autoStartPath);

    loadApps();

    connect(m_fileSystemWatcher, &QFileSystemWatcher::directoryChanged, this, &AutoStartManager::loadApps);
}

void AutoStartManager::loadApps()
{
    QDir files(m_autoStartPath);
    QList<DesktopInfo> allAppsInfo;

    for (const QFileInfo &file : files.entryInfoList(QDir::Files)) {
        QString filePath = file.absoluteFilePath();

        if (file.suffix() != "desktop") {
            continue;
        }

        DesktopProperties desktop(filePath, "Desktop Entry");
        QString appName = desktop.value(QString("Name[%1]").arg(QLocale::system().name())).toString();
        QString appExec = desktop.value("Exec").toString();
        QString appIcon = desktop.value("Icon").toString();

        if (appName.isEmpty()) {
            appName = desktop.value("Name").toString();
        }

        DesktopInfo appInfo;
        appInfo.name = appName;
        appInfo.iconName = appIcon;
        appInfo.exec = appExec;
        appInfo.filePath = filePath;
        allAppsInfo << appInfo;

        int index = m_appList.indexOf(appInfo);
        if (index == -1) {
            m_appList << appInfo;
        } else {
            m_appList[index].name = appName;
            m_appList[index].exec = appExec;
            m_appList[index].iconName = appIcon;
        }
    }

    // remove deleted items.
    for (auto iter = m_appList.begin(); iter != m_appList.end();) {
        if (!allAppsInfo.contains(*iter)) {
            iter = m_appList.erase(iter);
        } else {
            ++iter;
        }
    }

    emit dataChanged();
}

void AutoStartManager::addNewApp(const QString appName, const QString appExec)
{
    QString filePath = m_autoStartPath + appName + ".desktop";
    DesktopProperties desktop(filePath, "Desktop Entry");

    desktop.set("Name", appName);
    desktop.set("Exec", appExec);
    desktop.set("Icon", appExec);
    desktop.set("Type", "Application");
    desktop.save(filePath, "Desktop Entry");
}

void AutoStartManager::setValue(const QString &filePath, const QString &key, const QString &value)
{
    DesktopProperties desktop(filePath, "Desktop Entry");
    desktop.set(key, value);

    if (key == "Name") {
        QString localNameKey = QString("Name[%1]").arg(QLocale::system().name());
        if (desktop.contains(localNameKey)) {
            desktop.set(localNameKey, value);
        }
    }

    if (key == "Icon") {
        desktop.set("Icon", value);
    }

    desktop.save(filePath, "Desktop Entry");

    loadApps();
}
