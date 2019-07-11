#include "cpuinfo.h"
#include <QRegularExpression>
#include <QFile>
#include <QDebug>

CpuInfo::CpuInfo(QObject *parent)
    : QObject(parent)
{
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly);
    QString buffer = file.readAll();
    QStringList modelNameList = buffer.split("\n").filter(QRegularExpression("^model name"));

    QString modelName = modelNameList.first();
}
