#include "NotificationClient.h"
#include "ThreadNetwork.h"

NotificationClient::NotificationClient(QObject *parent) : QWidget()
{
    this->parent = parent;
}

bool    NotificationClient::event(QEvent *e)
{
    if(e->type() == ClientEvents::CServerEmptyEvent)
    {
        QMessageBox msgBox;
        msgBox.setText("Le Client n'arrive pas a se connecter au serveur, veuillez modifier la configuration dans settings");
        msgBox.exec();
    }
    if(e->type() == ClientEvents::OfflineModeEvent)
    {
        QMessageBox msgBox;
        msgBox.setText("Le Client n'arrive pas a se connecter au serveur, veuillez modifier la configuration dans settings");
        msgBox.exec();
    }
	return (true);
}
