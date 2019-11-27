#ifndef PCIINFO_H
#define PCIINFO_H

#include <QObject>

class PCIInfo : public QObject
{
    Q_OBJECT

public:
    struct DeviceInfo {
        QString name;
        QString vendor;
        QString className;
    };

    explicit PCIInfo(QObject *parent = 0);

    QList<DeviceInfo> devices() const;

private:
    QList<DeviceInfo> m_devices;
};

#endif // PCIINFO_H
