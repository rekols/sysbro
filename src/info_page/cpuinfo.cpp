#include "cpuinfo.h"
#include <QRegularExpression>
#include <QFile>
#include <QDebug>

/* /sys paths */
#define _PATH_SYS_SYSTEM	"/sys/devices/system"
#define _PATH_SYS_HYP_FEATURES	"/sys/hypervisor/properties/features"
#define _PATH_SYS_CPU		_PATH_SYS_SYSTEM "/cpu"
#define _PATH_SYS_NODE		_PATH_SYS_SYSTEM "/node"

static QString SYS_SYSTEM_PATH = "/sys/devices/system";

CpuInfo::CpuInfo(QObject *parent)
    : QObject(parent),
      m_cpuCoreCount(0)
{
    QFile file("/proc/cpuinfo");

    if (file.open(QIODevice::ReadOnly)) {
        m_lines = QString(file.readAll()).split('\n', QString::SkipEmptyParts);
    }
    file.close();
}

int CpuInfo::getCpuCoreCount()
{
    if (m_cpuCoreCount != 0) {
        return m_cpuCoreCount;
    }

    QRegularExpression regExp("^processor");
    int count = 0;

    for (const QString &line : m_lines) {
        if (regExp.match(line).hasMatch()) {
            ++count;
        }
    }

    return count;
}

QString CpuInfo::getCpuModel(int processorNumber)
{
    QString cpuModel = getCpuInfoLine(processorNumber, "model name\\s+:\\s+(\\S.+)");

    if (cpuModel.isEmpty()) {
        cpuModel = getInfoLine("Processor\\s+:\\s+(\\S.+)");
    }

    return cpuModel;
}

float CpuInfo::getCurrentCpuSpeed(int processorNumber)
{
    // cpu MHz\\s+:\\s+(\\d+).*"
    float speed = getCpuInfoLine(processorNumber, "cpu MHz\\s+:\\s+(\\S.+)").toFloat();

    return speed;
}

QString CpuInfo::getCpuVendor(int processorNumber)
{
    QString vendor = getCpuInfoLine(processorNumber, "vendor_id\\s+:\\s+(\\S.+)");

    if (vendor.isEmpty()) {
        vendor = getInfoLine("Hardware\\s+:\\s+(\\S.+)");
    }

    if (vendor == "GenuineIntel") {
        vendor = "Intel Corp.";
    } else if (vendor == "AuthenticAMD") {
        vendor = "Advanced Micro Devices [AMD]";
    } else if (vendor == "HygonGenuine") {
        vendor = "Hygon";
    }

    return vendor;
}

QString CpuInfo::getCpuInfoLine(int processorNumber, const QString &regExpStr)
{
    const QRegularExpression processorRegExp("processor\\s+:\\s+(\\d+)");
    const QRegularExpression regExp(regExpStr);

    int line = 0;
    while (line < m_lines.size()) {
        if (processorRegExp.match(m_lines.at(line)).hasMatch()) {
            int recordProcNum = processorRegExp.match(m_lines.at(line)).capturedTexts()[1].toInt();
            if (recordProcNum == processorNumber) {
                ++line;
                while (line < m_lines.size()) {
                    if (regExp.match(m_lines.at(line)).hasMatch()) {
                        return regExp.match(m_lines.at(line)).capturedTexts()[1];
                    }
                    ++line;
                }
            }
        }
        ++line;
    }

    return QString();
}

QString CpuInfo::getInfoLine(const QString &regExpStr)
{
    const QRegularExpression regExp(regExpStr);

    for (const QString &line : m_lines) {
        if (regExp.match(line).isValid()) {
            return regExp.match(line).capturedTexts()[1];
        };
    }

    return QString();
}

long CpuInfo::getCpuMaxMHz()
{
    int num = getCpuCoreCount();
    long mhz = 0;

    QFile file(SYS_SYSTEM_PATH + "/cpu/cpu0/cpufreq/cpuinfo_max_freq");

    if (file.open(QIODevice::ReadOnly)) {
        mhz = file.readAll().simplified().toLong() / 1000;
    }

    return mhz;
}

long CpuInfo::getCpuMinMHz()
{
    int num = getCpuCoreCount();
    long mhz = 0;

    QFile file(SYS_SYSTEM_PATH + "/cpu/cpu0/cpufreq/cpuinfo_min_freq");

    if (file.open(QIODevice::ReadOnly)) {
        mhz = file.readAll().simplified().toLong() / 1000;
    }

    return mhz;
}
