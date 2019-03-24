#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT

public:
    explicit Utils(QObject *parent = nullptr);

    static QPixmap renderSVG(const QString &path, const QSize &size);
};

#endif // UTILS_H
