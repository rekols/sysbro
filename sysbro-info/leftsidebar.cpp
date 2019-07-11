#include "leftsidebar.h"
#include <QPushButton>
#include <QPainter>

LeftSideBar::LeftSideBar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout),
      m_buttonGroup(new QButtonGroup)
{
    m_buttonNameList << tr("Overview") << tr("Processor") << tr("Memory")
                     << tr("Storage") << tr("Hardware");

    m_layout->setMargin(0);

    setLayout(m_layout);
    setFixedWidth(200);
    initButtons();

    connect(m_buttonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &LeftSideBar::buttonClicked);
}

void LeftSideBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.fillRect(rect(), QColor("#F7F7F7"));
}

void LeftSideBar::initButtons()
{
    for (int i = 0; i < m_buttonNameList.size(); ++i) {
        QPushButton *btn = new QPushButton;
        btn->setText(m_buttonNameList.at(i));
        btn->setObjectName("SideButton");
        btn->setCheckable(true);
        btn->setFixedHeight(40);

        m_buttonGroup->addButton(btn, i);
        m_layout->addWidget(btn);

    }

    m_buttonGroup->button(0)->setChecked(true);
    m_layout->addStretch();
}
