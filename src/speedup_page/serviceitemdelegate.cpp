#include "serviceitemdelegate.h"
#include "servicemodel.h"
#include "../utils.h"
#include <QStandardItemModel>
#include <QStyleOptionViewItem>
#include <QStyleOptionButton>
#include <QPushButton>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>
#include <QDebug>

ServiceItemDelegate::ServiceItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void ServiceItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QRect rect(option.rect);
    const int column(index.column());

    painter->setRenderHint(QPainter::Antialiasing);

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, QColor("#E0E0E0"));
        painter->setPen(QColor("#000000"));
    } else {
        painter->setPen(QColor("#303030"));
    }

    // painting each column item.
    if (column == 0) {
        bool status = index.data(ServiceModel::Status).toBool();
        QString iconName;

        if (status) {
            iconName = ":/resources/settings.svg";
        } else {
            iconName = ":/resources/settings_disabled.svg";
        }

        QPixmap iconPixmap = Utils::renderSVG(iconName, QSize(48, 48));
        int iconY = rect.top() + (rect.height() - iconPixmap.height() / iconPixmap.devicePixelRatio()) / 2;
        painter->drawPixmap(5, iconY, iconPixmap);

        const QString name = painter->fontMetrics().elidedText(index.data(ServiceModel::Name).toString(),
                                                                       Qt::ElideRight, rect.width() - 10);
        QRect nameRect = rect;
        nameRect.setHeight(rect.height() / 2);
        nameRect.setLeft(iconPixmap.width() / iconPixmap.devicePixelRatio() + 20);
        painter->drawText(nameRect, Qt::AlignBottom | Qt::AlignLeft, name);

        QString descriptionStr = index.data(ServiceModel::Description).toString();
        QRect totalRect = rect;
        totalRect.setTop(nameRect.bottom() + 2);
        totalRect.setLeft(nameRect.left());
        painter->drawText(totalRect, Qt::AlignTop | Qt::AlignLeft, descriptionStr);
    } else if (column == 1) {
        bool status = index.data(ServiceModel::Status).toBool();
        painter->drawText(rect, Qt::AlignCenter, (status ? tr("Enabled") : tr("Disabled")));
    } /*else if (column == 2) {
        QStyleOptionButton button;
        button.rect = option.rect.marginsRemoved(QMargins(10, 10, 10, 10));
        button.text = "启用";
        button.state = QStyle::State_Enabled;
        QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
    }*/
}

QSize ServiceItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    return QSize(-1, 65);
}

