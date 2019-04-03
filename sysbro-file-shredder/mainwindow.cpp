#include "mainwindow.h"
#include "dtitlebar.h"
#include "utils.h"
#include "fileview.h"
#include "fileitemdelegate.h"
#include "dlinkbutton.h"
#include "ddialog.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_fileModel(new FileModel),
      m_deleteBtn(new QPushButton(tr("Shredding files")))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *topLayout = new QHBoxLayout;

    QVBoxLayout *tipsLayout = new QVBoxLayout;
    QLabel *topTipsLabel = new QLabel(tr("Shred files or folders that cannot be deleted"));
    QLabel *bottomTipsLabel = new QLabel(tr("You can click to add a file or drag and drop directly to this window"));

    QLabel *tipsLabel = new QLabel;
    QPixmap tipsPixmap = Utils::renderSVG(":/images/sysbro-file-shredder.svg", QSize(64, 64));
    tipsLabel->setPixmap(tipsPixmap);

    tipsLayout->addWidget(topTipsLabel);
    tipsLayout->addWidget(bottomTipsLabel);

    topLayout->addWidget(tipsLabel);
    topLayout->addSpacing(10);
    topLayout->addLayout(tipsLayout);
    topLayout->addStretch();

    FileView *fileView = new FileView;
    fileView->setItemDelegate(new FileItemDelegate);
    fileView->setModel(m_fileModel);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    DLinkButton *addButton = new DLinkButton(tr("Add file"));
    bottomLayout->addWidget(addButton, 0, Qt::AlignLeft);
    bottomLayout->addWidget(m_deleteBtn, 0, Qt::AlignRight);

    mainLayout->setContentsMargins(20, 10, 20, 10);
    mainLayout->addLayout(topLayout);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(fileView);
    mainLayout->addSpacing(5);
    mainLayout->addLayout(bottomLayout);
    centralWidget->setLayout(mainLayout);

    if (titlebar()) {
        titlebar()->setBackgroundTransparent(true);
        titlebar()->setIcon(QIcon(":/images/icon.svg"));
        titlebar()->setTitle("");
    }

    setWindowIcon(QIcon(":/images/sysbro-file-shredder.svg"));
    setCentralWidget(centralWidget);
    setBorderColor(QColor("#BFBFBF"));
    setWindowTitle(tr("File Shredder"));
    setAcceptDrops(true);
    setWindowRadius(16);
    resize(700, 500);

    connect(m_fileModel, &FileModel::removeAllFilesFinished, this, &MainWindow::popupSuccessDialog);
    connect(m_deleteBtn, &QPushButton::clicked, m_fileModel, &FileModel::removeAllFiles);
    connect(fileView, &FileView::removeItem, m_fileModel, &FileModel::removeItem);
    connect(addButton, &DLinkButton::clicked, this, &MainWindow::popupFileDialog);
}

MainWindow::~MainWindow()
{

}

void MainWindow::popupFileDialog()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    m_fileModel->append(dialog.selectedFiles());
}

void MainWindow::popupSuccessDialog(int count)
{
    DDialog msgDialog(this);
    msgDialog.setFixedWidth(400);
    msgDialog.setIcon(QIcon(":/images/sysbro-file-shredder.svg"), QSize(64, 64));
    msgDialog.setTitle(tr("File Shredder"));
    msgDialog.setTextFormat(Qt::AutoText);
    msgDialog.setMessage(QString(tr("Success, %1 file(s) have been successfully deleted")).arg(count));
    msgDialog.insertButton(0, tr("OK"), false, DDialog::ButtonRecommend);
    msgDialog.exec();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    const auto *mime = e->mimeData();

    // not has urls.
    if (!mime->hasUrls()) {
        return e->ignore();
    }

    e->accept();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    auto *const mime = e->mimeData();

    if (!mime->hasUrls()) {
        return e->ignore();
    }

    e->accept();

    QStringList fileList;
    for (const QUrl &url : mime->urls()) {
        if (!url.isLocalFile()) {
            continue;
        }

        fileList << url.toLocalFile();
    }

    m_fileModel->append(fileList);
}
