#include "infolabel.h"

InfoLabel::InfoLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    setWordWrap(true);
}
