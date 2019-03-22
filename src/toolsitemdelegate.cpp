#include "toolsitemdelegate.h"
#include "toolslistmodel.h"
#include "utils.h"
#include <QPainter>
#include <QApplication>

ToolsItemDelegate::ToolsItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void ToolsItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid())
        return;

    QRect rect = option.rect;

    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing |
                            QPainter::SmoothPixmapTransform);
    painter->setPen(Qt::transparent);
    painter->setBrush(QColor(0, 0, 0, 10));

    bool isHover = index.data(ToolsListModel::CurrentIndexRole).toBool();
    if (isHover) {
        painter->drawRoundedRect(rect, 12, 12);
    }

    int iconSize = 70;
    int iconLeftMargin = (rect.width() - iconSize) / 2;
    double iconTopMargin = rect.height() * 0.2 - iconSize * 0.3;
    QString iconName = QString(":/resources/%1.svg").arg(index.data(ToolsListModel::AppKeyRole).toString());
    if (!QFile(iconName).exists()) {
        iconName = ":/resources/sysbro.svg";
    }
    QRect iconRect = QRect(rect.topLeft() + QPoint(iconLeftMargin, iconTopMargin), QSize(iconSize, iconSize));
    QPixmap iconPixmap = Utils::renderSVG(iconName, QSize(iconSize, iconSize));
    painter->drawPixmap(iconRect, iconPixmap);

    QTextOption appNameOption;
    appNameOption.setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    appNameOption.setWrapMode(QTextOption::WordWrap);

    painter->setBrush(Qt::transparent);
    painter->setPen(Qt::black);

    int textTopMargin = rect.width() * 0.6;
    QRect textRect = QRect(rect.x(),
                           rect.y() + textTopMargin,
                           rect.width(),
                           rect.height());
    QString appName = index.data(ToolsListModel::AppNameRole).toString();
    painter->drawText(textRect, Qt::TextWordWrap | Qt::AlignHCenter, appName);
}

QSize ToolsItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(150, 150);
}
