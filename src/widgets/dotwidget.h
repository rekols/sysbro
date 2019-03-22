#ifndef DOTWIDGET_H
#define DOTWIDGET_H

#include <QWidget>

class DotWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DotWidget(QWidget *parent = nullptr);

    QColor color();
    void setColor(QColor color);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor m_backgroundColor;
};

#endif // DOTWIDGET_H
