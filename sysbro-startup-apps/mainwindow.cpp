#include "mainwindow.h"
#include "dtitlebar.h"
#include "itemdelegate.h"
#include "createwindow.h"
#include "autostartmanager.h"
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QMenu>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_tipsLabel(new QLabel),
      m_listModel(new ListModel),
      m_listView(new ListView),
      m_autoStartManager(AutoStartManager::instance())
{
    QWidget *centralWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    centralWidget->setLayout(layout);

    m_tipsLabel->setStyleSheet("QLabel { color: #666666; font-size: 25px; }");
    m_tipsLabel->setText("未发现开机启动应用");
    m_tipsLabel->setVisible(false);

    m_listView->setModel(m_listModel);
    m_listView->setItemDelegate(new ItemDelegate);

    layout->addWidget(m_listView);
    layout->addWidget(m_tipsLabel, 0, Qt::AlignCenter);

    if (titlebar()) {
        QMenu *menu = new QMenu;
        QAction *createAction = new QAction("新建应用");
        QAction *selectAction = new QAction("选择文件");

        menu->addAction(createAction);
        menu->addAction(selectAction);
        menu->addSeparator();

        titlebar()->setBackgroundTransparent(true);
        titlebar()->setIcon(QIcon(":/images/icon.svg"));
        titlebar()->setMenu(menu);
        titlebar()->setTitle("开机启动管理");

        connect(createAction, &QAction::triggered, this, &MainWindow::popupCreateWindow);
        connect(selectAction, &QAction::triggered, this, &MainWindow::popupFileDialog);
    }

    setWindowIcon(QIcon(":/images/icon.svg"));
    setCentralWidget(centralWidget);
    setWindowTitle("应用开机启动管理`");
    setMinimumSize(500, 450);
    setWindowRadius(16);
    checkAutoStartApp();

    connect(m_listView, &ListView::entered, m_listModel, &ListModel::setCurrentIndex);
    connect(m_listView, &ListView::rightClicked, this, &MainWindow::popupRightMenu);
    connect(m_autoStartManager, &AutoStartManager::dataChanged, this, &MainWindow::checkAutoStartApp);
}

MainWindow::~MainWindow()
{

}

void MainWindow::handleNewApp(const QString appName, const QString appExec)
{
    m_autoStartManager->addNewApp(appName, appExec);
}

void MainWindow::popupRightMenu(QModelIndex idx)
{
    QMenu *menu = new QMenu;

    if (idx.isValid()) {
        QAction *modifyAction = new QAction("修改");
        QAction *deleteAction = new QAction("删除");
        menu->addAction(modifyAction);
        menu->addAction(deleteAction);

        connect(modifyAction, &QAction::triggered, [=] {
            popupEditDialog(idx);
        });

        connect(deleteAction, &QAction::triggered, [=] {
            QFile file(idx.data(ListModel::AppPathRole).toString());
            file.remove();
            file.close();
        });
    }

    QAction *deleteAllAction = new QAction("删除所有");
    menu->addAction(deleteAllAction);

    connect(deleteAllAction, &QAction::triggered, this, &MainWindow::deleteAllApps);

    menu->move(QCursor::pos());
    menu->exec();
}

void MainWindow::popupCreateWindow()
{
    CreateWindow *dlg = new CreateWindow;
    connect(dlg, &CreateWindow::requestNewApp, this, &MainWindow::handleNewApp);
    dlg->exec();
}

void MainWindow::popupEditDialog(QModelIndex idx)
{
    CreateWindow *dlg = new CreateWindow;
    QString filePath = idx.data(ListModel::AppPathRole).toString();
    dlg->setAppExec(idx.data(ListModel::AppExecRole).toString());
    dlg->setAppName(idx.data(ListModel::AppNameRole).toString());

    connect(dlg, &CreateWindow::requestNewApp, this, [=] (QString appName, QString appExec) {
        m_autoStartManager->setValue(filePath, "Name", appName);
        m_autoStartManager->setValue(filePath, "Exec", appExec);
    });

    dlg->exec();
}

void MainWindow::popupFileDialog()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFiles);
//    dialog.setNameFilter("Desktop Files (*.desktop)");
    dialog.exec();

    QString autoStartPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).append("/autostart/");

    for (const QString &fileName : dialog.selectedFiles()) {
        QFileInfo fi(fileName);

        if (fi.completeSuffix() == "desktop") {
            QFile::copy(fileName, autoStartPath + fi.fileName());
        }
    }
}

void MainWindow::checkAutoStartApp()
{
    if (m_autoStartManager->appList().isEmpty()) {
        m_listView->setVisible(false);
        m_tipsLabel->setVisible(true);
    } else {
        m_listView->setVisible(true);
        m_tipsLabel->setVisible(false);
    }
}

void MainWindow::deleteAllApps()
{
    QString autoStartPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation).append("/autostart/");
    QDir files(autoStartPath);

    for (const QFileInfo &fileInfo : files.entryInfoList(QDir::Files)) {
        QFile file(fileInfo.absoluteFilePath());
        file.remove();
    }
}

