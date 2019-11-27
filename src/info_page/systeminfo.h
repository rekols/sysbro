#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QObject>

class SystemInfo : public QObject
{
    Q_OBJECT

public:
    explicit SystemInfo(QObject *parent = 0);

    // order: productName, productFamily, productVersion
    static QStringList getProductInfo();
    static QString getHostName();
    static QString getUserName();
    static QString getComputerType();
    static QString getKernel();
    static QString getDistribution();
};

#endif // SYSTEMINFO_H
