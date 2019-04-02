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
      m_deleteBtn(new QPushButton("粉碎文件"))
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *topLayout = new QHBoxLayout;

    QVBoxLayout *tipsLayout = new QVBoxLayout;
    QLabel *topTipsLabel = new QLabel("粉碎无法删除的文件或文件夹");
    QLabel *bottomTipsLabel = new QLabel("您可以点击添加文件或直接拖拽到本窗口，请谨慎粉碎文件");

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
    DLinkButton *addButton = new DLinkButton("添加文件");
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
    setWindowTitle("文件粉碎机");
    setAcceptDrops(true);
    // setWindowRadius(16);
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
    msgDialog.setTitle("文件粉碎机");
    msgDialog.setTextFormat(Qt::AutoText);
    msgDialog.setMessage(QString("粉碎成功，%1个文件(文件夹)已成功粉碎").arg(count));
    msgDialog.insertButton(0, "确定", false, DDialog::ButtonRecommend);
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
