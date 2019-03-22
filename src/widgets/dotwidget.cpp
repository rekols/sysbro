#include "dotwidget.h"
#include <QPainter>

DotWidget::DotWidget(QWidget *parent) : QWidget(parent)
{
    m_backgroundColor = QColor("#2CA7F8");

    setFixedSize(8, 8);
}

QColor DotWidget::color()
{
    return m_backgroundColor;
}

void DotWidget::setColor(QColor color)
{
    m_backgroundColor = color;

    update();
}

void DotWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_backgroundColor);
    painter.drawRoundedRect(rect(), rect().width(), rect().height());
}
