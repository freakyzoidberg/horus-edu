#include "FileServer.h"

FileServer::FileServer(QObject* p) : QTcpServer(p)
{
}

void FileServer::incomingConnection (int socket)
{
}
