#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);

    void startTest();
    void realTest();

signals:
    void statusChanged(QString speed);
    void testSuccess(quint64 speed, QString speedStr);
    void testFailed();

private:
    void handleDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void handleFakeReplyFinished();

private:
    QNetworkAccessManager *m_networkManager;
    QNetworkReply *m_fakeReply;
    QNetworkReply *m_realReply;
    QList<qint64> m_speedList;
    QTime m_downloadTime;
    QString m_realUrl;
};

#endif // NETWORKMANAGER_H
