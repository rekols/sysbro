#include "leftsidebar.h"
#include <QPushButton>
#include <QPainter>
#include <QMap>

LeftSideBar::LeftSideBar(QWidget *parent)
    : QWidget(parent),
      m_layout(new QVBoxLayout),
      m_buttonGroup(new QButtonGroup)
{
    m_buttonNameList << tr("Home") << tr("Cleaner") << tr("Speed up")
                     << tr("Tools");
    m_layout->setMargin(10);

    setLayout(m_layout);
    setFixedWidth(160);
    initButtons();

    connect(m_buttonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), this, &LeftSideBar::buttonClicked);
}

void LeftSideBar::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#F5F5F5"));
    painter.drawRect(QRect(rect().width() - 1, 0, 1, rect().height()));
}

void LeftSideBar::initButtons()
{
    const QMap<int, QString> icons = {
        {0, ":/resources/home.svg"},
        {1, ":/resources/cleaning_brush.svg"},
        {2, ":/resources/statistics.svg"},
        {3, ":/resources/toolbox.svg"}
    };

    for (int i = 0; i < m_buttonNameList.size(); ++i) {
        QPushButton *btn = new QPushButton;
        btn->setText(m_buttonNameList.at(i));
        btn->setObjectName("SideButton");
        btn->setCheckable(true);
        btn->setFixedHeight(45);
        btn->setIcon(QIcon(icons.value(i)));
        btn->setIconSize(QSize(30, 30));

        m_buttonGroup->addButton(btn, i);
        m_layout->addWidget(btn);

    }

    m_buttonGroup->button(0)->setChecked(true);
    m_layout->addStretch();
}
