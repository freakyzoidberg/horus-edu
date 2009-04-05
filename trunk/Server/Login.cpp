#include "Login.h"

Login::Login(ClientSocket* cs)
{
    client = cs;
}

void Login::run()
{
    CommLogin msg("toto42");
    client->stream << msg; //envoi o lieu de recevoir pour test et voir cqui sort


    //CommLogin msg;
    //client->stream >> msg; READ
    //CHECK LOGIN PASS ...

    client->connect(client, SIGNAL(readyRead()), SLOT(onRecvRequest()));
}
