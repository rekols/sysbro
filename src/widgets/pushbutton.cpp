#include "pushbutton.h"
#include "../utils.h"
#include <QHBoxLayout>
#include <QPainter>

PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
}

void PushButton::setText(const QString &text)
{
    m_text = text;

    update();
}

void PushButton::setIcon(const QString &icon, const QSize &size)
{
    m_iconPixmap = Utils::renderSVG(icon, size);
    m_iconSize = size;

    update();
}

void PushButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter painter(this);

    // draw icon.
    painter.drawPixmap(10, (rect().height() - m_iconSize.height()) / 2, m_iconPixmap);

    // draw text.
    if (isChecked()) {
        painter.setPen(Qt::white);
    } else {
        painter.setPen(Qt::black);
    }

    QRect textRect = rect();
    textRect.setX(m_iconSize.width() + 20);
    painter.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, m_text);
}
