#include "infolabel.h"

InfoLabel::InfoLabel(const QString &text, bool selectable, QWidget *parent)
    : QLabel(text, parent)
{
    if (selectable) {
        setTextInteractionFlags(Qt::TextSelectableByMouse);
        setCursor(QCursor(Qt::IBeamCursor));
    }

    setWordWrap(true);
}
