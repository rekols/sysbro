#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QWidget>
#include <QLabel>

class IconLabel : public QWidget
{
    Q_OBJECT

public:
    explicit IconLabel(QWidget *parent = nullptr);

    void setTitle(const QString text);
    void setIconPixmap(const QPixmap pixmap);
    void setIconSize(const QSize size);

private:
    QLabel *m_iconLabel;
    QLabel *m_titleLabel;
};

#endif // ICONLABEL_H
