#include "contentwidget.h"
#include <QDebug>

ContentWidget::ContentWidget(QWidget *parent)
    : QWidget(parent),
      m_layout(new QStackedLayout),
      m_overViewPage(new OverviewPage)
{
    m_layout->addWidget(m_overViewPage);

    setLayout(m_layout);
}

void ContentWidget::setCurrentIndex(int index)
{
    m_layout->setCurrentIndex(index);
}
