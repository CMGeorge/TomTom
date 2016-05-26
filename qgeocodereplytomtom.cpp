#include "qgeocodereplytomtom.h"


#include <QtPositioning/QGeoCoordinate>
#include <QtPositioning/QGeoAddress>
#include <QtPositioning/QGeoLocation>
#include <QtPositioning/QGeoRectangle>

QGeoCodeReplyTomtom::QGeoCodeReplyTomtom(QNetworkReply *reply, QObject *parent)
:   QGeoCodeReply(parent), m_reply(reply)
{
    connect(m_reply, SIGNAL(finished()), this, SLOT(networkReplyFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(networkReplyError(QNetworkReply::NetworkError)));

    setLimit(1);
    setOffset(0);
}

QGeoCodeReplyTomtom::~QGeoCodeReplyTomtom()
{
    if (m_reply)
        m_reply->deleteLater();
}

void QGeoCodeReplyTomtom::abort()
{
    if (!m_reply)
        return;

    m_reply->abort();

    m_reply->deleteLater();
    m_reply = 0;
}


void QGeoCodeReplyTomtom::networkReplyFinished()
{
    if (!m_reply)
        return;

    if (m_reply->error() != QNetworkReply::NoError)
        return;

    QList<QGeoLocation> locations;
//        setError(QGeoCodeReply::ParseError, QStringLiteral("Error parsing OpenRouteService xml response:") + xml.errorString() + " at line: " + xml.lineNumber());
    setLocations(locations);
    setFinished(true);

    m_reply->deleteLater();
    m_reply = 0;
}

void QGeoCodeReplyTomtom::networkReplyError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error)

    if (!m_reply)
        return;

    setError(QGeoCodeReply::CommunicationError, m_reply->errorString());

    m_reply->deleteLater();
    m_reply = 0;
}
