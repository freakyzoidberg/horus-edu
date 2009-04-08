#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QStringList>
#include <QTcpServer>
#include <QThreadPool>

#include "../Common/Defines.h"
#include "../Common/CommInit.h"
#include "ClientSocket.h"
#include "Settings.h"
#include "Sql.h"


class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);
    void check();
};

#endif
