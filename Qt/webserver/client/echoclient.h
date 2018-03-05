
#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // ECHOCLIENT_H