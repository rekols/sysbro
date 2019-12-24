#include "pciinfo.h"
#include <QDebug>
#include <QFile>
#include <QProcess>

//extern "C" is needed to proper linking with libpci
extern "C" {
#include <pci/pci.h>
}

static QMap<QString, QString> PCIClass_ZHCN = {
    {"Network controller", "网卡"},
    {"PCI bridge", "PCI桥"},
    {"Non-Volatile memory controller", "非易失性存储器控制器"},
    {"Memory controller", "内存"},
    {"SATA controller", "SATA控制器"},
    {"USB controller", "USB控制器"},
    {"VGA compatible controller", "VGA兼容控制器"},
    {"Audio device", "音频设备"}
};

PCIInfo::PCIInfo(QObject *parent)
    : QObject(parent)
{
    struct pci_access *pacc;
    struct pci_dev *dev;
    unsigned int c;
    char name_buffer[1024];

    // get the pci_access structure.
    pacc = pci_alloc();
    // initialize the PCI library.
    pci_init(pacc);
    // get the list of devices.
    pci_scan_bus(pacc);

    for (dev = pacc->devices; dev; dev = dev->next) {
        // fill in header info we need.
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
        // read config register directly.
        c = pci_read_byte(dev, PCI_INTERRUPT_PIN);

        DeviceInfo info;
        info.name = QString::fromUtf8(pci_lookup_name(pacc, name_buffer, sizeof(name_buffer), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id));
        info.vendor = QString::fromUtf8(pci_lookup_name(pacc, name_buffer, sizeof(name_buffer), PCI_LOOKUP_VENDOR, dev->vendor_id, dev->device_id));
        info.className = QString::fromUtf8(pci_lookup_name(pacc, name_buffer, sizeof(name_buffer), PCI_LOOKUP_CLASS, dev->device_class));
        m_devices << info;
    }

    pci_cleanup(pacc);
}

QList<PCIInfo::DeviceInfo> PCIInfo::devices() const
{
    return m_devices;
}
