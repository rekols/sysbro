#include "iconlabel.h"
#include <QVBoxLayout>

IconLabel::IconLabel(QWidget *parent)
    : QWidget(parent),
      m_iconLabel(new QLabel),
      m_titleLabel(new QLabel)
{
    QVBoxLayout *layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_iconLabel, 0, Qt::AlignBottom | Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addWidget(m_titleLabel, 0, Qt::AlignTop | Qt::AlignHCenter);

    setLayout(layout);
}

void IconLabel::setTitle(const QString text)
{
    m_titleLabel->setText(text);
}

void IconLabel::setIconPixmap(const QPixmap pixmap)
{
    m_iconLabel->setPixmap(pixmap);
}

void IconLabel::setIconSize(const QSize size)
{
    m_iconLabel->setFixedSize(size);
}
