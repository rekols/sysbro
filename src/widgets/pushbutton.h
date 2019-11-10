#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QLabel>

class PushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit PushButton(QWidget *parent = nullptr);

    void setText(const QString &text);
    void setIcon(const QString &icon, const QSize &size);

    void paintEvent(QPaintEvent *);

private:
    QString m_text;
    QPixmap m_iconPixmap;
    QSize m_iconSize;
};

#endif
