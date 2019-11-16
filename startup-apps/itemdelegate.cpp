#include "itemdelegate.h"
#include "listmodel.h"
#include "dimagebutton.h"
#include <QApplication>
#include <QImageReader>

DWIDGET_USE_NAMESPACE

const QPixmap renderSVG(const QString &path, const QSize &size)
{
    QImageReader reader;
    QPixmap pixmap;
    reader.setFileName(path);

    if (reader.canRead()) {
        const qreal ratio = qApp->devicePixelRatio();
        reader.setScaledSize(size * ratio);
        pixmap = QPixmap::fromImage(reader.read());
        pixmap.setDevicePixelRatio(ratio);
    } else {
        pixmap.load(path);
    }

    return pixmap;
}

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
    m_defaultIconPixmap = renderSVG(":/images/application-x-executable.svg", QSize(32, 32));
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

    if (iconPixmap.isNull()) {
        iconPixmap = m_defaultIconPixmap;
    }

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
    Q_UNUSED(option);
    Q_UNUSED(index);

    return QSize(-1, 55);
}

QWidget *ItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    DImageButton *removeBtn = new DImageButton(":/images/close_normal.svg",
                                               ":/images/close_hover.svg",
                                               ":/images/close_press.svg", parent);
    connect(removeBtn, &DImageButton::clicked, this, &ItemDelegate::removeBtnClicked);
    return removeBtn;
}

void ItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);

    DImageButton *btn = static_cast<DImageButton *>(editor);
    btn->setFixedSize(QPixmap(btn->getNormalPic()).size());
    QRect rect = option.rect;
    btn->setGeometry(rect.x() + rect.width() - btn->width() * 2,
                     rect.y() + (rect.height() - btn->height()) / 2,
                     btn->width(),
                     btn->height());
}
