#include <QCoreApplication>
#include <QCommandLineParser>
#include <iostream>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.process(app);

    const QStringList fileList = parser.positionalArguments();

    for (const QString file : fileList) {
        QFileInfo fileInfo(file);

        if (fileInfo.isDir()) {
            QDir(file).removeRecursively();
        } else {
            QFile openFile(file);

            if (openFile.remove()) {
                std::cout << "finished" << std::endl;
            } else {
                std::cout << "error" << std::endl;
            }
        }
    }

    return 0;
}
