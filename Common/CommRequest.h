#ifndef COMMREQUEST_H
#define COMMREQUEST_H

#include <QDataStream>
#include <QObject>

#include "CommMiniString.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
class CommRequest
{
  Q_ENUMS(msgType)
public:
    enum            msgType { ALIVE, FILE_DOWNLOAD, FILE_UPLOAD, CONFIG_GET, CONFIG_SET, MODULE_COMM };

    CommMiniString  versionContent;
    quint32         idPacket;
    msgType         type;
};

QDataStream& operator<<(QDataStream&, CommRequest&);
QDataStream& operator>>(QDataStream&, CommRequest&);

#endif // COMMREQUEST_H
