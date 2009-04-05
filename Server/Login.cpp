#include "Login.h"

Login::Login(ClientSocket* cs)
{
    client = cs;
}

void Login::run()
{
    CommLogin msg("0.1.2", "toto42");
    client->stream << msg; //envoi o lieu de recevoir pour test et voir cqui sort

    //CommLogin msg;
    //client->stream >> msg; READ
    //CHECK LOGIN
    //Server::clients << client;  REGISTER CLIENT

}
