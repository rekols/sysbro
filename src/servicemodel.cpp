#include "servicemodel.h"
#include <QRegularExpression>
#include <QProcess>
#include <QtConcurrent>

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

    for (QString line : lines) {
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

    if (content.size() > 0) {
        QStringList desc = content.first().split('=');
        if (desc.size() > 0) {
            result = desc.last();
        }
    }

    return result;
}

void ServiceModel::switchStatus(QModelIndex idx)
{
    QString name = idx.data(ServiceModel::Name).toString();
    bool status = !idx.data(ServiceModel::Status).toBool();

    QProcess *process = new QProcess;
    bool failed = false;
    process->start("pkexec", QStringList() << "systemctl" << (status ? "enable" : "disable") << name);
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

    emit requestServicesNumber(num);
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
