#ifndef COMMREQUEST_H
#define COMMREQUEST_H

#include <QDataStream>

#include "Defines.h"

/*!
 * After authentification, each packets are transmited inside this container
 */
class CommRequest
{

public:
    enum     msgType {ALIVE, FILE_DOWNLOAD, FILE_UPLOAD, CONFIG_GET, CONFIG_SET, MODULE_COMM};
    char     verCont [VERSION_SIZE];
    quint32  idPacket;
    quint32  sizeCont;
};

QDataStream& operator<<(QDataStream& ds, CommRequest& lc);
QDataStream& operator>>(QDataStream& ds, CommRequest& lc);

#endif // COMMREQUEST_H
