#include "roundedwidget.h"
#include <QPainter>
#include <QLabel>

RoundedWidget::RoundedWidget(QWidget *parent)
    : QWidget(parent),
      m_backgroundColor(QColor(230, 242, 255)),
      m_radius(12)
{
}

void RoundedWidget::setRadius(int radius)
{
    if (m_radius != radius) {
        m_radius = radius;
        update();
    }
}

void RoundedWidget::setBackgroundColor(const QColor &color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        update();
    }
}

void RoundedWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backgroundColor);
    painter.drawRoundedRect(rect(), m_radius, m_radius);
}
