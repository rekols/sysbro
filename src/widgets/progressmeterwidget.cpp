#include "progressmeterwidget.h"

#include <qmath.h>
#include <QTimer>
#include <QPainter>

ProgressMeterWidget::ProgressMeterWidget(QWidget *parent)
    : QWidget(parent)
{
    m_minValue = 0;
    m_maxValue = 100;
    m_value = 0;

    m_precision = 1;
    m_startAngle = 40;
    m_endAngle = 40;

    m_bgColor = QColor(243, 243, 243);
    m_progressColor = QColor(7, 184, 13);
    m_progressBgColor = QColor(243, 243, 243);
    m_circleColor = QColor(255, 255, 255);
    m_textColor = QColor(0, 0, 0);

    m_showPointer = false;
    m_showValue = true;
    m_pointerStyle = PointerStyleCircle;

    m_reverse = false;
    m_currentValue = 0;

    m_timer = new QTimer(this);
    m_timer->setInterval(10);

    connect(m_timer, &QTimer::timeout, this, &ProgressMeterWidget::updateValue);
}

ProgressMeterWidget::~ProgressMeterWidget()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
}

void ProgressMeterWidget::setRange(double minValue, double maxValue)
{
    if (minValue >= maxValue) {
        return;
    }

    m_minValue = minValue;
    m_maxValue = maxValue;

    if (m_value < m_minValue || m_value > m_maxValue) {
        setValue(m_value);
    }

    update();
}

void ProgressMeterWidget::setMinValue(double minValue)
{
    setRange(minValue, m_maxValue);
}

void ProgressMeterWidget::setMaxValue(double maxValue)
{
    setRange(m_minValue, maxValue);
}

void ProgressMeterWidget::setValue(double value)
{
    if (value < m_minValue || value > m_maxValue) {
        return;
    }

    if (value > m_value) {
        m_reverse = false;
    } else if (value < m_value) {
        m_reverse = true;
    }

    m_value = value;
    m_timer->start();
}

void ProgressMeterWidget::setTitle(const QString &text)
{
    m_titleText = text;

    update();
}

void ProgressMeterWidget::setPrecision(int precision)
{
    if (precision <= 2 && m_precision != precision) {
        m_precision = precision;
        update();
    }
}

void ProgressMeterWidget::setStartAngle(int startAngle)
{
    if (m_startAngle != startAngle) {
        m_startAngle = startAngle;
        update();
    }
}

void ProgressMeterWidget::setEndAngle(int endAngle)
{
    if (m_endAngle != endAngle) {
        m_endAngle = endAngle;
        update();
    }
}

void ProgressMeterWidget::setBgColor(const QColor &bgColor)
{
    if (m_bgColor != bgColor) {
        m_bgColor = bgColor;
        update();
    }
}

void ProgressMeterWidget::setProgressColor(const QColor &progressColor)
{
    if (m_progressColor != progressColor) {
        m_progressColor = progressColor;
        update();
    }
}

void ProgressMeterWidget::setProgressBgColor(const QColor &progressBgColor)
{
    if (m_progressBgColor != progressBgColor) {
        m_progressBgColor = progressBgColor;
        update();
    }
}

void ProgressMeterWidget::setCircleColor(const QColor &circleColor)
{
    if (m_circleColor != circleColor) {
        m_circleColor = circleColor;
        update();
    }
}

void ProgressMeterWidget::setTextColor(const QColor &textColor)
{
    if (m_textColor != textColor) {
        m_textColor = textColor;
        update();
    }
}

void ProgressMeterWidget::setShowPointer(bool showPointer)
{
    if (m_showPointer != showPointer) {
        m_showPointer = showPointer;
        update();
    }
}

void ProgressMeterWidget::setShowValue(bool showValue)
{
    if (m_showValue != showValue) {
        m_showValue = showValue;
        update();
    }
}

void ProgressMeterWidget::setPointerStyle(const PointerStyle &pointerStyle)
{
    if (m_pointerStyle != pointerStyle) {
        m_pointerStyle = pointerStyle;
        update();
    }
}

QSize ProgressMeterWidget::sizeHint() const
{
    return QSize(180, 180);
}

void ProgressMeterWidget::updateValue()
{
    if (!m_reverse) {
        if (m_currentValue >= m_value) {
            m_currentValue = m_value;
            m_timer->stop();
        } else {
            m_currentValue += 0.5;
        }
    } else {
        if (m_currentValue <= m_value) {
            m_currentValue = m_value;
            m_timer->stop();
        } else {
            m_currentValue -= 0.5;
        }
    }

    update();
}

void ProgressMeterWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    const int w = width();
    const int h = height();
    const int side = qMin(w, h);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(w / 2, h / 2);
    painter.scale(side / 200.0, side / 200.0);

//    drawBg(&painter);
    drawColorPie(&painter);
//    drawCoverCircle(&painter);
    drawCircle(&painter);

//    if (m_pointerStyle == PointerStyleCircle) {
//        drawPointerCircle(&painter);
//    } else if (m_pointerStyle == PointerStyleIndicator) {
//        drawPointerIndicator(&painter);
//    } else if (m_pointerStyle == PointerStyleIndicatorR) {
//        drawPointerIndicatorR(&painter);
//    } else if (m_pointerStyle == PointerStyleTriangle) {
//        drawPointerTriangle(&painter);
//    }

    drawValue(&painter);
}

void ProgressMeterWidget::drawBg(QPainter *painter)
{
    const int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressMeterWidget::drawColorPie(QPainter *painter)
{
    const int radius = 93;
    painter->save();
    painter->setPen(Qt::NoPen);
    const QRectF rect(-radius, -radius, radius * 2, radius * 2);

    const double angleAll = 360.0 - m_startAngle - m_endAngle;
    const double angleCurrent = angleAll * ((m_currentValue - m_minValue) / (m_maxValue - m_minValue));
    const double angleOther = angleAll - angleCurrent;

    painter->setBrush(m_progressColor);
    painter->drawPie(rect, (270 - m_startAngle - angleCurrent) * 16, angleCurrent * 16);

    painter->setBrush(m_progressBgColor);
    painter->drawPie(rect, (270 - m_startAngle - angleCurrent - angleOther) * 16, angleOther * 16);
    painter->restore();
}

void ProgressMeterWidget::drawCoverCircle(QPainter *painter)
{
    const int radius = 85;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bgColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressMeterWidget::drawCircle(QPainter *painter)
{
    const int radius = 85;
    painter->save();
    painter->setPen(Qt::NoPen);

    // QLinearGradient bgGradient(0, -radius, 0, radius);
    // bgGradient.setColorAt(0.0, m_circleColorStart);
    // bgGradient.setColorAt(1.0, m_circleColorEnd);
    painter->setBrush(m_circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressMeterWidget::drawPointerCircle(QPainter *painter)
{
    if (!m_showPointer) {
        return;
    }

    const int radius = 15;
    const int offset = 20;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->rotate(m_startAngle);

    const double degRotate = (360.0 - m_startAngle - m_endAngle) / (m_maxValue - m_minValue) * (m_currentValue - m_minValue);
    painter->rotate(degRotate);
    painter->setBrush(m_progressColor);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
    painter->restore();
}

void ProgressMeterWidget::drawPointerIndicator(QPainter *painter)
{
    if (!m_showPointer) {
        return;
    }

    int radius = 65;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);
    painter->rotate(m_startAngle);

    const double degRotate = (360.0 - m_startAngle - m_endAngle) / (m_maxValue - m_minValue) * (m_currentValue - m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressMeterWidget::drawPointerIndicatorR(QPainter *painter)
{
    if (!m_showPointer) {
        return;
    }

    int radius = 65;
    painter->save();

    QPen pen;
    pen.setWidth(1);
    pen.setColor(m_progressColor);
    painter->setPen(pen);
    painter->setBrush(m_progressColor);

    QPolygon pts;
    pts.setPoints(3, -8, 0, 8, 0, 0, radius);
    painter->rotate(m_startAngle);

    const double degRotate = (360.0 - m_startAngle - m_endAngle) / (m_maxValue - m_minValue) * (m_currentValue - m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void ProgressMeterWidget::drawPointerTriangle(QPainter *painter)
{
    if (!m_showPointer) {
        return;
    }

    const int radius = 20;
    const int offset = 55;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_progressColor);

    QPolygon pts;
    pts.setPoints(3, -radius / 2, offset, radius / 2, offset, 0, radius + offset);
    painter->rotate(m_startAngle);

    const double degRotate = (360.0 - m_startAngle - m_endAngle) / (m_maxValue - m_minValue) * (m_currentValue - m_minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void ProgressMeterWidget::drawValue(QPainter *painter)
{
    if (!m_showValue) {
        return;
    }

    const int radius = 100;
    painter->save();
    painter->setPen(m_textColor);

    QFont font;
    // font.setPixelSize(m_showPointer ? radius - 50 : radius - 15);
    // font.setBold(true);
    font.setPointSize(20);
    painter->setFont(font);

    const QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    const QRectF valueRect(-radius, -radius + 35, radius * 2, radius * 2);
    QString valueText = QString("%1%").arg(m_currentValue, 0, 'f', m_precision);

    // draw title.
    painter->drawText(textRect, Qt::AlignCenter, m_titleText);

    // draw value.
    font.setPointSize(15);
    painter->setFont(font);
    painter->drawText(valueRect, Qt::AlignCenter, valueText);
    painter->restore();
}
