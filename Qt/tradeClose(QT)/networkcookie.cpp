#include "networkcookie.h"

NetworkCookie::NetworkCookie(QObject *parent)
    : QNetworkCookieJar(parent)
{

}

NetworkCookie::~NetworkCookie()
{

}

QList<QNetworkCookie> NetworkCookie::getCookies()
{
    return allCookies();
}

void NetworkCookie::setCookies(const QList<QNetworkCookie>& cookieList)
{
    if(this == NULL)
        return;
    this->setAllCookies(cookieList);
}
