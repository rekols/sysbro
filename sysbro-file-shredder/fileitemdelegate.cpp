#include "fileitemdelegate.h"
#include "filemodel.h"
#include "utils.h"
#include <QPainter>

FileItemDelegate::FileItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void FileItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QRect rect(option.rect);
    const int column(index.column());

    rect = rect.marginsRemoved(QMargins(5, 0, 5, 0));

    painter->setRenderHint(QPainter::Antialiasing);

    if (option.state & QStyle::State_Selected) {
        painter->fillRect(option.rect, QColor("#D0E8FA"));
        painter->setPen(QColor("#2CA7F8"));
    } else {
        painter->setPen(QColor("#303030"));
    }

    if (column == 0) {
        bool isFile = index.data(FileModel::IsFile).toBool();
        QString iconFileName = isFile ? ":/images/file.svg" : ":/images/folder.svg";
        QPixmap iconPixmap = Utils::renderSVG(iconFileName, QSize(22, 22));

        int iconY = rect.top() + (rect.height() - iconPixmap.height() / iconPixmap.devicePixelRatio()) / 2;
        painter->drawPixmap(5, iconY, iconPixmap);

        QString fileName = index.data(FileModel::FileName).toString();
        QRect nameRect = rect;
        nameRect.setLeft(iconPixmap.width() + 15);
        painter->drawText(nameRect, Qt::AlignVCenter | Qt::AlignLeft, fileName);

    } else if (column == 1) {
        QString filePath = index.data(FileModel::FilePath).toString();
        filePath = painter->fontMetrics().elidedText(filePath, Qt::ElideRight, rect.width() - 10);
        painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, filePath);
    }
}

QSize FileItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(-1, 30);
}
