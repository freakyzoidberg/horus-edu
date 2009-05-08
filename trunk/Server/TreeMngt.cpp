#include "TreeMngt.h"

TreeMngt::TreeMngt()
{
}

TreeMngt::~TreeMngt()
{
}

bool TreeMngt::DeleteNode(int idnode)
{
    qDebug() << "trying DELETE treemanagement id = "+ QVariant(idnode).toString();

    Sql con;
    QString idparent = "0";
    QSqlQuery query1("SELECT id_parent FROM treemanagement WHERE id = " + QVariant(idnode).toString() + " LIMIT 1", QSqlDatabase::database(con));

    while (query1.next())
    {
        idparent = query1.value(0).toString();
        qDebug() << "id parent = " + idparent;
    }
    if (query1.lastError().isValid())
    {
        qDebug() << "LastError" + query1.lastError().text();
        return false;
    }

    QSqlQuery query2("UPDATE treemanagement SET id_parent = " + idparent +" WHERE id_parent = " + QVariant(idnode).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "DeleteNode() -> Error in refathering new id_parent is weird";
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }

    QSqlQuery query3("DELETE FROM treemanagement WHERE id = " + QVariant(idnode).toString() + " LIMIT 1", QSqlDatabase::database(con));

    if (query3.lastError().isValid())
    {
        qDebug() << "LastError" + query3.lastError().text();
        return false;
    }
    else
        return true;
}

bool TreeMngt::MoveNode(int idmove, int idfather)
{
    qDebug() << "trying MOVE to id_parent = " + QVariant(idfather).toString() +" WHERE id = " + QVariant(idmove).toString();
    Sql con;

    QSqlQuery query2("UPDATE treemanagement SET id_parent = " + QVariant(idfather).toString() +" WHERE id = " + QVariant(idmove).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "MoveNode() -> Error in refathering new id_parent or id is weird";
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }
    return true;
}

int TreeMngt::InsertNode(QString name, int userref, int idfather)
{
    qDebug() << "trying INSERT treemanagement name = " + name + " userref = " + QVariant(userref).toString() + " idfather = " + QVariant(idfather).toString();
    Sql con;

    QSqlQuery query("INSERT INTO treemanagement (name, user_ref, id_parent) VALUES ('" + name + "', '" + QVariant(userref).toString() + "', '" + QVariant(idfather).toString() + "')", QSqlDatabase::database(con));

    if (query.lastError().isValid())
    {
        qDebug() << "LastError" + query.lastError().text();
        return false;
    }
    else
        return true;
}


bool TreeMngt::SetName(int idnode, QString name)
{
    qDebug() << "trying SetName to name = " + name +" WHERE id = " + QVariant(idnode).toString();
       Sql con;

    QSqlQuery query2("UPDATE treemanagement SET name = '" + name +"' WHERE id = " + QVariant(idnode).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }
    return true;
}

bool TreeMngt::SetUserRef(int idnode, int userref)
{
    qDebug() << "trying SetUserRef to user_ref = " + QVariant(userref).toString() +" WHERE id = " + QVariant(idnode).toString();
       Sql con;

    QSqlQuery query2("UPDATE treemanagement SET user_ref = '" + QVariant(userref).toString() +"' WHERE id = " + QVariant(idnode).toString(), QSqlDatabase::database(con));

    if (query2.lastError().isValid())
    {
        qDebug() << "LastError" + query2.lastError().text();
        return false;
    }
    return true;
}
