#include <QRegularExpression>
#include <QApplication>
#include <QProcess>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QProcess *process = new QProcess;
    process->start("systemd-analyze");
    process->waitForFinished(-1);

    QString output = process->readLine();
    QRegularExpression reg("\\s=.*s");
    QRegularExpressionMatch match = reg.match(output);
    QString bootTime = match.captured(0).remove(" = ");

    process->start("notify-send", QStringList() << "-i" << "sysbro" << "开机助手"
                                                << QString("本次开机时间为: %1").arg(bootTime));
    process->waitForFinished(-1);

    return 0;
}
