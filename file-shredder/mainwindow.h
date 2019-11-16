#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QPushButton>
#include "filemodel.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void popupFileDialog();
    void popupSuccessDialog(int count);

protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);

private:
    FileModel *m_fileModel;
    QPushButton *m_deleteBtn;
};

#endif // MAINWINDOW_H
