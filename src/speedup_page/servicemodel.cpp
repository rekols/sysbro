#include "servicemodel.h"
#include <QRegularExpression>
#include <QProcess>
#include <QtConcurrent>
#include <QDebug>

const QMap<QString, QString> descriptions = {
    {"accounts-daemon", "账户服务"},
    {"acpid", "ACPI 事件守护进程"},
    {"binfmt-support", "启用对其他可执行二进制格式的支持"},
    {"bluetooth", "蓝牙服务"},
    {"console-getty", "控制台 getty 服务"},
    {"cron", "常规后台程序处理守护进程"},
    {"cups", "CUPS 打印系统调度"},
    {"dbus-org.bluez", "蓝牙服务"},
    {"dbus-org.freedesktop.miracle.wfd", "Miraclecast WIFI 显示服务"},
    {"dbus-org.freedesktop.miracle.wifi", "Miraclecast WIFI 守护进程"},
    {"dbus-org.freedesktop.ModemManager1", "调制解调器管理器"},
    {"dbus-org.freedesktop.network1", "网络服务"},
    {"dbus-org.freedesktop.resolve1", "网络名称解析"},
    {"dde-filemanager-daemon", "深度文件管理器守护进程"},
    {"deepin-accounts-daemon", "深度系统账户服务"},
    {"deepin-anything-monitor", "深度 anything 服务"},
    {"deepin-anything-tool", "深度 anything 工具服务"},
    {"deepin-login-sound", "深度系统登录声音"},
    {"deepin-shutdown-sound", "深度系统关机声音"},
    {"display-manager", "显示管理器"},
    {"dm-event", "设备映射事件守护进程"},
    {"driver-installer", "深度显卡驱动管理器安装程序"},
    {"laptop-mode", "笔记本模式工具"},
    {"lightdm", "lightdm 显示管理器"},
    {"lmt-poll", "笔记本模式工具 - 电池服务"},
    {"lvm2-lvmetad", "LVM2 元数据守护进程"},
    {"lvm2-lvmpolld", "LVM2 调查守护进程"},
    {"lvm2-monitor", "监视 LVM2 镜像, 快照等"},
    {"miracle-dispd", "Miraclecast WIFI 显示服务"},
    {"miracle-wifid", "Miraclecast WIFI 守护进程"},
    {"ModemManager", "调制解调管理器"},
    {"network-manager", "网络管理器"},
    {"networking", "提升网络接口"},
    {"nmbd", "Samba NMB 守护进程"},
    {"openvpn", "OpenVPN 服务"},
    {"smbd", "Samba SMB 守护进程"},
    {"sudo", "为特定用户提供有限的超级用户权限"},
    {"udisks2", "磁盘管理"},
    {"upower", "电源管理守护进程"}
};

ServiceModel::ServiceModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    QtConcurrent::run(this, &ServiceModel::loadServices);
}

void ServiceModel::loadServices()
{
    QProcess *process = new QProcess;
    process->start("systemctl", QStringList() << "list-unit-files" << "-t"
                                              << "service" << "-a"
                                              << "--state=enabled,disabled");
    process->waitForFinished(-1);

    QString output = process->readAllStandardOutput();
    QStringList lines = output.split('\n').filter(QRegularExpression("[^@].service"));;

    for (const QString &line : lines) {
        QStringList l = line.trimmed().split(QRegularExpression("\\s+"));

        QString name = l.first().trimmed().replace(".service", "");
        QString description = getDescription(name);
        bool status = !l.last().trimmed().compare("enabled");

        ServiceItem *item = new ServiceItem;
        item->name = name;
        item->description = description;
        item->status = status;
        m_serviceList << item;
    }

    int row = m_serviceList.size();
    beginInsertRows(QModelIndex(), 0, row);
    endInsertRows();
    checkEnableItem();
}

QString ServiceModel::getDescription(const QString &name)
{
    QString result("Unknown");
    QProcess *process = new QProcess;
    process->start("systemctl", QStringList() << "cat" << name);
    process->waitForFinished(-1);
    QString output = process->readAllStandardOutput();
    process->deleteLater();

    QStringList content = output.split('\n').filter(QRegularExpression("^Description"));
    bool isChinese = QLocale::system().name() == "zh_CN";

    if (content.size() > 0) {
        QStringList desc = content.first().split('=');
        if (desc.size() > 0) {
            result = desc.last();
        }
    }

    if (isChinese && descriptions.contains(name)) {
        result = descriptions[name];
    }

    return result;
}

void ServiceModel::switchStatus(QModelIndex idx)
{
    QString name = idx.data(ServiceModel::Name).toString();
    bool status = !idx.data(ServiceModel::Status).toBool();

    QProcess *process = new QProcess;
    bool failed = false;
    process->start("pkexec", QStringList() << "sysbro-service-mgr" << (status ? "enable" : "disable") << name);
    process->waitForFinished(-1);
    failed |= process->exitCode();

    if (!failed) {
        for (ServiceItem *item : m_serviceList) {
            if (item->name == name) {
                item->status = status;
            }
        }
    }

    checkEnableItem();
    emit layoutChanged();
}

void ServiceModel::checkEnableItem()
{
    int num = 0;
    for (ServiceItem *item : m_serviceList) {
        if (item->status) {
            ++num;
        }
    }

    emit requestServicesNumber(num + 1);
}

int ServiceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_serviceList.size();
}

int ServiceModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 2;
}

QVariant ServiceModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    ServiceItem *item = m_serviceList.at(row);

    switch (role) {
    case ServiceModel::Name:
        return item->name;
    case ServiceModel::Description:
        return item->description;
    case ServiceModel::Status:
        return item->status;
    }

    return QVariant();
}

QVariant ServiceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
    case 0:
        return tr("Service Name");
    case 1:
        return tr("Status");
//    case 2:
//        return "设置状态";
    }

    return QVariant();
}
