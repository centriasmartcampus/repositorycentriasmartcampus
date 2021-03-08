#ifndef SCFASTCGIREQUEST_H
#define SCFASTCGIREQUEST_H

#include <QObject>

class SCFastCGIRequest {

public:
    QByteArray Request;
    QByteArray Response;
    QMap<QString, QString> Parameters;
    QByteArray Content;

};

#endif // SCFASTCGIREQUEST_H
