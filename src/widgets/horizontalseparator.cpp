#include "horizontalseparator.h"
#include <QPainter>

HorizontalSeparator::HorizontalSeparator(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(1);
}

void HorizontalSeparator::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#EFEFEF"));
    painter.drawRect(rect());
}
