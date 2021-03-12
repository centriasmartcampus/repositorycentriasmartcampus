#ifndef CENTRIAFASTCGIREQUEST_H
#define CENTRIAFASTCGIREQUEST_H

#include <QObject>

class CentriaFastCGIRequest {

public:
    QByteArray Request;
    QByteArray Response;
    QMap<QString, QString> Parameters;
    QByteArray Content;

};

#endif // CENTRIAFASTCGIREQUEST_H
