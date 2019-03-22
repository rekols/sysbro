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

    QLabel *appNameLabel = new QLabel("应用名称: ");
    QLabel *appExecLabel = new QLabel("应用命令: ");

    m_appNameEdit->setPlaceholderText("必填");
    m_appExecEdit->setPlaceholderText("必填");

    formLayout->addRow(appNameLabel, m_appNameEdit);
    formLayout->addRow(appExecLabel, m_appExecEdit);

    layout->addLayout(formLayout);
    widget->setLayout(layout);

    addButton("取消");
    addButton("确定", true, DDialog::ButtonRecommend);
    setOnButtonClickedClose(false);
    addContent(widget);
    setFixedSize(300, 170);

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
