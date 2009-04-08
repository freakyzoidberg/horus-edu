#ifndef SQLQUERY_H
#define SQLQUERY_H

#include <QThread>
#include <QtSql>
class SqlQuery : public QThread
{
Q_OBJECT
 public:
    SqlQuery();
    SqlQuery( QObject* parent);
    void run();


};

#endif // SQLQUERY_H
