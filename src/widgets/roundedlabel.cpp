#include "roundedlabel.h"
#include <QHBoxLayout>
#include <QFormLayout>

RoundedLabel::RoundedLabel(QWidget *parent)
    : RoundedWidget(parent),
      m_nameLabel(new QLabel),
      m_textLabel(new QLabel)
{
    initUI();
}

RoundedLabel::RoundedLabel(const QString &name, const QString &content, QWidget *parent)
    : RoundedWidget(parent),
      m_nameLabel(new QLabel(name)),
      m_textLabel(new QLabel)
{
    initUI();

    setText(content);
}

void RoundedLabel::setName(const QString &text)
{
    m_nameLabel->setText(text);
}

void RoundedLabel::setText(const QString &text)
{
    m_textLabel->setText(text);

    setFixedHeight(m_textLabel->sizeHint().height() + 20);
}

void RoundedLabel::initUI()
{
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(m_nameLabel, 0, Qt::AlignLeft);
    layout->addWidget(m_textLabel, 0, Qt::AlignRight);

    m_nameLabel->setWordWrap(true);
    m_textLabel->setWordWrap(true);

    setBackgroundColor(QColor("#F8F8F8"));
    setRadius(10);
    setLayout(layout);
    setFixedHeight(45);
}
