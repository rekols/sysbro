#ifndef CLEANERPAGE_H
#define CLEANERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QStackedLayout>
#include <QPushButton>
#include "dspinner.h"
#include "../widgets/loadingprogresswidget.h"
#include "scannedwidget.h"

DWIDGET_USE_NAMESPACE

class CleanerPage : public QWidget
{
    Q_OBJECT

public:
    explicit CleanerPage(QWidget *parent = nullptr);

    void init();

private:
    void handleScanBtnClicked();
    void handleClearBtnClicked();
    void handleScanFinished(quint64 totalSize);
    void handleClearFinished(quint64 totalSize);

private:
    QPushButton *m_scanButton;
    QPushButton *m_clearButton;
    ScannedWidget *m_scannedWidget;
    QStackedLayout *m_stackedLayout;
    LoadingProgressWidget *m_spinner;

    QLabel *m_tips2Label;
};

#endif // CLEANERPAGE_H
