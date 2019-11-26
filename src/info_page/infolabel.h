#ifndef INFOLABEL_H
#define INFOLABEL_H

#include <QLabel>

class InfoLabel : public QLabel
{
    Q_OBJECT

public:
    explicit InfoLabel(const QString &text = "", QWidget *parent = 0);

signals:

public slots:
};

#endif // INFOLABEL_H
