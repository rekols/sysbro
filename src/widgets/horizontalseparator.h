#ifndef HORIZONTALSEPARATOR_H
#define HORIZONTALSEPARATOR_H

#include <QObject>
#include <QWidget>

class HorizontalSeparator : public QWidget
{
    Q_OBJECT

public:
    explicit HorizontalSeparator(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // HORIZONTALSEPARATOR_H
