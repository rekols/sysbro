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

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QWidget>

class ProgressBar : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressBar(QWidget *parent = nullptr);

public Q_SLOTS:
    float currentValue();
    void setValue(float percent);
    void setTitle(QString text);
    void setColor(QColor colour);

protected:
    void paintEvent(QPaintEvent *);

private:
    QString m_title;
    QColor m_color;

    float m_maxValue;
    float m_minValue;
    float m_value;

    int m_nullPosition;
    int m_borderWidth;
};

#endif // PROGRESS_BAR_H
