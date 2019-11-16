#include <QCoreApplication>
#include <QCommandLineParser>
#include <QProcess>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.process(app);

    QStringList arguments = parser.positionalArguments();

    QProcess process;
    process.start("systemctl", QStringList() << arguments.first() << arguments.last());
    process.waitForFinished(-1);

    return 0;
}
