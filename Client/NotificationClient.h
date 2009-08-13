#ifndef NOTIFICATIONCLIENT_H
# define NOTIFICATIONCLIENT_H

# include <QObject>
# include <QWidget>
# include <QString>

class NotificationClient : public QWidget
{
    Q_OBJECT

public:
        NotificationClient();

public slots:
        void notify(QString message);
};

#endif // NOTIFICATIONCLIENT_H
