#include "monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout),
      m_progressAnimation(new QVariantAnimation),
      m_progress(new ProgressBar),
      m_tipsLabel(new QLabel)
{
    QFont font;
    font.setPointSize(15);
    m_tipsLabel->setFont(font);

    m_progressAnimation->setDuration(500);
    m_progressAnimation->setEasingCurve(QEasingCurve::OutCirc);

    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_progress, 0, Qt::AlignHCenter);
    m_layout->addSpacing(15);
    m_layout->addWidget(m_tipsLabel, 0, Qt::AlignHCenter);
    m_layout->addStretch();

    setLayout(m_layout);

    connect(m_progressAnimation, &QVariantAnimation::valueChanged, this, [=] (const QVariant &value) {
        m_progress->setValue(value.toFloat());
    });
}

void MonitorWidget::setPercentValue(const float &value)
{    
    m_progressAnimation->stop();
    m_progressAnimation->setStartValue(m_progress->currentValue());
    m_progressAnimation->setEndValue(value);
    m_progressAnimation->start();
}

void MonitorWidget::setTitle(const QString &text)
{
    m_progress->setTitle(text);
}

void MonitorWidget::setTips(const QString &text)
{
    m_tipsLabel->setText(text);
}

void MonitorWidget::setColor(const QColor &color)
{
    m_progress->setProgressColor(color);
}
