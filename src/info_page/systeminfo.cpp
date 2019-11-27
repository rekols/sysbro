#include "systeminfo.h"
#include <QSettings>
#include <QProcess>
#include <QFile>
#include <QDebug>

SystemInfo::SystemInfo(QObject *parent)
    : QObject(parent)
{

}


QStringList SystemInfo::getProductInfo()
{
    QString productName = tr("Unknown");
    QString productFamily = tr("Unknown");
    QString productVersion = tr("Unknown");

    QFile file("/sys/devices/virtual/dmi/id/product_name");

    if (file.open(QIODevice::ReadOnly)) {
        productName = file.readAll().trimmed();
        file.close();
    }

    file.setFileName("/sys/devices/virtual/dmi/id/product_family");
    if (file.open(QIODevice::ReadOnly)) {
        productFamily = file.readAll().trimmed();
        file.close();
    }

    file.setFileName("/sys/devices/virtual/dmi/id/product_version");
    if (file.open(QIODevice::ReadOnly)) {
        productVersion = file.readAll().trimmed();
        file.close();
    }

    QStringList list { productName, productFamily, productVersion };

    return list;
}

QString SystemInfo::getHostName()
{
    QFile file("/proc/sys/kernel/hostname");
    QString hostName = tr("Unknown");

    if (file.open(QIODevice::ReadOnly)) {
        hostName = file.readAll().trimmed();
        file.close();
    }

    return hostName;
}

QString SystemInfo::getUserName()
{
    QString userName = qgetenv("USER");

    if (userName.isEmpty()) {
        userName = qgetenv("USERNAME");
    }

    return userName;
}

QString SystemInfo::getComputerType()
{
    // src: http://www.dmtf.org/sites/default/files/standards/documents/DSP0134_2.7.0.pdf
    // https://www.404techsupport.com/2012/03/pizza-box-lunch-box-and-other-pc-case-form-factors-identified-by-wmi/

    QFile file;
    QString deviceType = tr("Unknown");

    if (QFile::exists("/sys/class/dmi/id/chassis_type")) {
        file.setFileName("/sys/class/dmi/id/chassis_type");
    } else if (QFile::exists("/sys/devices/virtual/dmi/id/chassis_type")) {
        file.setFileName("/sys/devices/virtual/dmi/id/chassis_type");
    }

    if (file.open(QIODevice::ReadOnly)) {
        int chassisId = file.readAll().trimmed().toInt();

        switch (chassisId) {
        case 1:
            deviceType = tr("Virtual Machine");
            break;
        case 3: case 4: case 6: case 7: case 13: case 15: case 24:
            // note: 13 is all-in-one which we take as a mac type system
            deviceType = tr("Desktop");
            break;
        case 5:
            //  pizza box was a 1 U desktop enclosure, but some old laptops also id this way
            deviceType = "pizza-box";
            break;
        case 9: case 10: case 16:
            // lenovo T420 shows as 10, notebook,  but it's not a notebook
            deviceType = tr("Laptop");
            break;
        case 8: case 11:
            deviceType = tr("portable");
            break;
        case 17: case 23: case 25:
            deviceType = tr("Server");
            break;
        }

        file.close();
    }

    return deviceType;
}

QString SystemInfo::getKernel()
{
    getDistribution();

    QProcess *process = new QProcess;
    process->start("uname", QStringList() << "-sr");
    process->waitForFinished(-1);
    QString kernel = process->readAllStandardOutput().trimmed();
    return kernel;
}

QString SystemInfo::getDistribution()
{
    QSettings settings("/usr/lib/os-release", QSettings::IniFormat);
    QString prettyName(tr("Unknown"));

    if (settings.contains("NAME") && settings.contains("VERSION")) {
        prettyName = settings.value("NAME").toString() + " "
                   + settings.value("VERSION").toString();
    }

    return prettyName;
}
