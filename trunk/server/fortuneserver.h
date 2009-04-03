#ifndef FORTUNESERVER_H
#define FORTUNESERVER_H

#include <QStringList>
#include <QTcpServer>


class FortuneServer : public QTcpServer
{
    Q_OBJECT

public:
    FortuneServer(QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);
    void OptionalFill();
    void check();

private:
    QStringList fortunes;
};

#endif
