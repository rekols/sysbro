#ifndef ROUNDEDWIDGET_H
#define ROUNDEDWIDGET_H

#include <QWidget>

class RoundedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoundedWidget(QWidget *parent = nullptr);

    void setRadius(int radius);
    void setBackgroundColor(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor m_backgroundColor;
    int m_radius;
};

#endif // ROUNDEDWIDGET_H
