#include "echoclient.h"
#include <QtCore/QDebug>
#include <string>
#include <iostream>

QT_USE_NAMESPACE

EchoClient::EchoClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
   // if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl(url));
}

void EchoClient::onConnected()
{
    //if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &EchoClient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void EchoClient::onTextMessageReceived(QString message)
{
    //if (m_debug)
        qDebug() << "Message received:" << message;
    std::string s;
    std::cin>>s;
    m_webSocket.sendTextMessage(QString::fromStdString(s));
    //m_webSocket.close();
}
