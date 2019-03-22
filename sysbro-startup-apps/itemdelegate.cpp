#include "itemdelegate.h"
#include "listmodel.h"
#include <QApplication>

const QPixmap getThemeIcon(const QString &iconName, const int size)
{
    const auto ratio = qApp->devicePixelRatio();
    QPixmap pixmap;

    const QIcon icon = QIcon::fromTheme(iconName, QIcon::fromTheme("application-x-desktop"));
    pixmap = icon.pixmap(QSize(size, size));

    if (qFuzzyCompare(pixmap.devicePixelRatioF(), 1.0)) {
        pixmap = pixmap.scaled(QSize(size, size) * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        pixmap.setDevicePixelRatio(ratio);
    }

    return pixmap;
}

ItemDelegate::ItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect = option.rect;

    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing |
                            QPainter::SmoothPixmapTransform);

    painter->setPen(Qt::transparent);
    painter->setBrush(QColor(0, 0, 0, 10));

    if (index.data(ListModel::CurrentIndex).toBool()) {
        painter->drawRoundedRect(rect, 12, 12);;
    }

//    if (index.row()) {
//        const QPoint start(20, rect.top());
//        const QPoint end(rect.right() - 40, rect.top());

//        painter->setPen(QColor(0, 0, 0, 255 * 0.05));
//        painter->drawLine(start, end);
//    }

    QString appName = index.data(ListModel::AppNameRole).toString();
    QString appIcon = index.data(ListModel::AppIconRole).toString();

    int iconSize = 32;
    QPixmap iconPixmap = getThemeIcon(appIcon, iconSize);
    int iconY = rect.top() + (rect.height() - iconPixmap.height() / iconPixmap.devicePixelRatio()) / 2;
    painter->drawPixmap(QRect(10, iconY,
                              iconPixmap.width() / iconPixmap.devicePixelRatio(),
                              iconPixmap.height() / iconPixmap.devicePixelRatio()), iconPixmap);

    QRect nameRect = rect;
    nameRect.setLeft(iconSize + 30);
    painter->setPen(Qt::black);
    painter->drawText(nameRect, Qt::TextWordWrap | Qt::AlignVCenter, appName);
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(-1, 55);
}
