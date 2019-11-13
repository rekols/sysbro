#include "monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout),
      m_progress(new ProgressMeterWidget),
      m_tipsLabel(new QLabel)
{
    QFont font;
    font.setPointSize(15);
    m_tipsLabel->setFont(font);

    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addWidget(m_progress, 0, Qt::AlignHCenter);
    m_layout->addSpacing(10);
    m_layout->addWidget(m_tipsLabel, 0, Qt::AlignHCenter);
    m_layout->addStretch();

    setLayout(m_layout);
}

void MonitorWidget::setPercentValue(const float &value)
{    
    m_progress->setValue(value);
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
