#ifndef MEMORYINFO_H
#define MEMORYINFO_H

#include <QObject>

class MemoryInfo : public QObject
{
    Q_OBJECT
public:
    explicit MemoryInfo(QObject *parent = 0);

signals:

public slots:
};

#endif // MEMORYINFO_H