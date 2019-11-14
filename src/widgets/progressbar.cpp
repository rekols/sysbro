/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2017 ~ 2019 Rekols
 *
 * Author:     Rekols <rekols@foxmail.com>
 * Maintainer: Rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "progressbar.h"
#include <QPainter>
#include <qmath.h>
#include <QDebug>

ProgressBar::ProgressBar(QWidget *parent)
    : QWidget(parent),
      m_title(""),
      m_color(QColor("#2CA7F8")),
      m_minValue(0),
      m_maxValue(100),
      m_value(0),
      m_nullPosition(0),
      m_borderWidth(5)
{

}

void ProgressBar::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    int radius = 99 - m_borderWidth / 2;

    QPen pen;
    pen.setWidthF(m_borderWidth);
    pen.setColor(QColor("#F3F3F3"));

    /* init painter */
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    /* draw background */
    painter.setPen(pen);
    painter.drawArc(QRect(-radius, -radius, radius * 2, radius * 2), m_nullPosition * 16, -(-360) * 16);

    /* draw value */
    pen.setColor(m_color);
    painter.setPen(pen);
    double length = 360.0 / (m_maxValue - m_minValue) * (m_value - m_minValue);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter.drawArc(rect, m_nullPosition * 16, -length * 16);

    /* draw title text */
    QFont font;
    font.setPointSize(20);
    painter.setFont(font);

    /* qreal left, qreal top, qreal width, qreal height */
    QRectF titleRect(-radius, (-radius), radius * 2, radius * 2);
    painter.setPen(QColor("#000000"));
    painter.drawText(titleRect, Qt::AlignCenter, m_title);

    /* draw percent text*/
    font.setPointSize(15);
    painter.setFont(font);
    painter.setPen(Qt::black);

    QRectF percentRect(-radius, (-radius) + 35, radius * 2, radius * 2);
    QString strPercent = QString::number(m_value, 'r', 1) + "%";
    painter.drawText(percentRect, Qt::AlignCenter, strPercent);
}

float ProgressBar::currentValue()
{
    return m_value;
}

void ProgressBar::setValue(float percent)
{
    m_value = percent;

    update();
}

void ProgressBar::setTitle(const QString &text)
{
    m_title = text;

    update();
}

void ProgressBar::setProgressColor(const QColor &colour)
{
    m_color = colour;

    update();
}

QSize ProgressBar::sizeHint() const
{
    return QSize(160, 160);
}
