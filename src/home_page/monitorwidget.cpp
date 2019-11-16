#include "monitorwidget.h"
#include "../utils.h"

MonitorWidget::MonitorWidget(QWidget *parent)
    : RoundedWidget(parent),
      m_layout(new QVBoxLayout),
      // m_progressAnimation(new QVariantAnimation),
      // m_progress(new ProgressBar),
      m_iconLabel(new QLabel),
      m_titleLabel(new QLabel),
      m_percentLabel(new QLabel("0.0%")),
      m_tipsLabel(new QLabel)
{
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    m_percentLabel->setFont(font);

    // m_progressAnimation->setDuration(500);
    // m_progressAnimation->setEasingCurve(QEasingCurve::OutCirc);

    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    m_layout->addStretch();
    m_layout->addWidget(m_iconLabel, 0, Qt::AlignHCenter);
    m_layout->addSpacing(15);
    m_layout->addWidget(m_percentLabel, 0, Qt::AlignHCenter);
    m_layout->addSpacing(5);
    m_layout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    m_layout->addSpacing(15);
    m_layout->addWidget(m_tipsLabel, 0, Qt::AlignHCenter);
    m_layout->addStretch();

    setLayout(m_layout);
    setFixedSize(176, 183);
    setBackgroundColor(Qt::white);

    // connect(m_progressAnimation, &QVariantAnimation::valueChanged, this, [=] (const QVariant &value) {
    //     m_progress->setValue(value.toFloat());
    // });
}

void MonitorWidget::setPercentValue(const float &value)
{
    m_percentLabel->setText(QString::number(value, 'r', 1) + "%");
//    m_progressAnimation->stop();
//    m_progressAnimation->setStartValue(m_progress->currentValue());
//    m_progressAnimation->setEndValue(value);
//    m_progressAnimation->start();
}

void MonitorWidget::setTitle(const QString &text)
{
    m_titleLabel->setText(text);
}

void MonitorWidget::setTips(const QString &text)
{
    m_tipsLabel->setText(text);
}

void MonitorWidget::setColor(const QColor &color)
{
    // m_progress->setProgressColor(color);
}

void MonitorWidget::setIcon(const QString &iconPath, const QSize &size)
{
    QPixmap pixmap  = Utils::renderSVG(iconPath, size);
    m_iconLabel->setFixedSize(size);
    m_iconLabel->setPixmap(pixmap);
}
