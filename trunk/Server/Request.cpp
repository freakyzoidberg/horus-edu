#include "Request.h"

Request::Request(ClientSocket* cs)
{
    client = cs;
}

void Request::run()
{
    CommRequest req;
//    client->stream >> req;
    client->stream << "recu";
//    qDebug() << "recu request dans un thread";
//    client->stream << msg; //envoi o lieu de recevoir pour test et voir cqui sort
}
