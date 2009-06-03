#ifndef NOTIFICATIONCLIENT_H
#define NOTIFICATIONCLIENT_H

#include <QObject>
#include <QWidget>
#include "ClientEvents.h"

class NotificationClient : public QWidget
{
    Q_OBJECT
    public:
        NotificationClient(QObject *parent = 0);
    protected slots:
        //! event loop
        bool    event(QEvent *e);
    private:
        QObject *parent;
};

#endif // NOTIFICATIONCLIENT_H
