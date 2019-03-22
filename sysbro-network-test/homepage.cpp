#include "homepage.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QImageReader>
#include <QLabel>
#include "dlinkbutton.h"

DWIDGET_USE_NAMESPACE

static QPixmap renderSVG(const QString &path, const QSize &size)
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

HomePage::HomePage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *iconLabel = new QLabel;
    QPixmap iconPixmap = renderSVG(":/images/network.svg", QSize(128, 128));
    iconLabel->setPixmap(iconPixmap);

    QLabel *splitLine = new QLabel;
    QPixmap splitPixmap = renderSVG(":/images/split_line.svg", QSize(214, 2));
    splitLine->setPixmap(splitPixmap);

    DLinkButton *btn = new DLinkButton("立即测速");

    layout->addSpacing(50);
    layout->addWidget(iconLabel, 0, Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addWidget(splitLine, 0, Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addWidget(btn, 0, Qt::AlignHCenter);
    layout->addStretch();

    setLayout(layout);

    connect(btn, &DLinkButton::clicked, this, &HomePage::startButtonClicked);
}
