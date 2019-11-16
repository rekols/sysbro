#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <ddialog.h>

DWIDGET_USE_NAMESPACE

class EditDialog : public DDialog
{
    Q_OBJECT

public:
    explicit EditDialog(QWidget *parent = nullptr);
};

#endif // EDITDIALOG_H
