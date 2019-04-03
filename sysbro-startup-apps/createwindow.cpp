#include "createwindow.h"
#include <QFormLayout>
#include <QLabel>

CreateWindow::CreateWindow(QWidget *parent)
    : DDialog(parent),
      m_appNameEdit(new QLineEdit),
      m_appExecEdit(new QLineEdit)
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;

    QLabel *appNameLabel = new QLabel(tr("Application Name:"));
    QLabel *appExecLabel = new QLabel(tr("Application Exec:"));

    formLayout->addRow(appNameLabel, m_appNameEdit);
    formLayout->addRow(appExecLabel, m_appExecEdit);

    layout->addLayout(formLayout);
    widget->setLayout(layout);

    addButton(tr("Cancel"));
    addButton(tr("OK"), true, DDialog::ButtonRecommend);
    setOnButtonClickedClose(false);
    addContent(widget);
//    setFixedSize(300, 170);
    setFixedHeight(170);

    connect(this, &CreateWindow::buttonClicked, this, &CreateWindow::handleButtonClicked);
}

void CreateWindow::setAppName(const QString &text)
{
    m_appNameEdit->setText(text);
    m_appNameEdit->setCursorPosition(0);
}

void CreateWindow::setAppExec(const QString &text)
{
    m_appExecEdit->setText(text);
    m_appExecEdit->setCursorPosition(0);
}

void CreateWindow::handleButtonClicked(const int index, const QString &text)
{
    Q_UNUSED(text);

    if (index == 1) {
        if (m_appNameEdit->text().isEmpty() ||
            m_appExecEdit->text().isEmpty()) {
            return;
        }

        emit requestNewApp(m_appNameEdit->text(), m_appExecEdit->text());
    }

    close();
}
