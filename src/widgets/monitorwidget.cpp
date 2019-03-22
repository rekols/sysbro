#include "monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_progress = new ProgressBar;
    m_tips2 = new QLabel;
    m_animation = new QVariantAnimation;

    m_animation->setDuration(500);
    m_animation->setEasingCurve(QEasingCurve::OutCirc);

    QFont font;
    font.setPointSize(15);
    m_tips2->setFont(font);

    m_layout->addWidget(m_progress, 0, Qt::AlignHCenter);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_tips2, 0, Qt::AlignHCenter);

    connect(m_animation, &QVariantAnimation::valueChanged, this,
            [=] (const QVariant &value){
               m_progress->setValue(value.toFloat());
            });
}

void MonitorWidget::setPercentValue(const float &value)
{    
    m_animation->stop();
    m_animation->setStartValue(m_progress->currentValue());
    m_animation->setEndValue(value);
    m_animation->start();
}

void MonitorWidget::setTitle(const QString &text)
{
    m_progress->setTitle(text);
}

void MonitorWidget::setTips(const QString &text)
{
    m_tips2->setText(text);
}

void MonitorWidget::setColor(const QColor &color)
{
    m_progress->setColor(color);
}
