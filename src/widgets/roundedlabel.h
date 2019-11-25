#ifndef ROUNDEDLABEL_H
#define ROUNDEDLABEL_H

#include "roundedwidget.h"
#include <QLabel>

class RoundedLabel : public RoundedWidget
{
    Q_OBJECT

public:
    explicit RoundedLabel(QWidget *parent = 0);
    explicit RoundedLabel(const QString &name, const QString &content, QWidget *parent = 0);

    void setName(const QString &text);
    void setText(const QString &text);

private:
    void initUI();

private:
    QLabel *m_nameLabel;
    QLabel *m_textLabel;
};

#endif // ROUNDEDLABEL_H
