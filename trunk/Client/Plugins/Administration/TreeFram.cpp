#include "TreeFram.h"
#include <QDebug>
#include "../../../Common/PluginPacket.h"


TreeFram::TreeFram(INetwork *reseau) : QTreeWidget()
{
    res = reseau;
    QTreeWidgetItem *hItem = this->headerItem();
    hItem->setText(0, "Groupes");
    requestFunctions["getTree"]         = &TreeFram::getTreeResponse;
    requestFunctions["getNodeInfo"]     = &TreeFram::getNodInfoResponse;
    requestFunctions["setNode"]         = &TreeFram::editNodeResponse;
    this->connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
    getTree();
}

void TreeFram::itemClicked(QTreeWidgetItem *item, int idx)
{
    qDebug() << item->text(0);
}

void    TreeFram::readResponse(QVariantHash response)
{
    (this->*requestFunctions.value(response["Request"].toByteArray(),
                                   &TreeFram::unknownResponse))
                                   (response);
}
/*
void    UserFram::getTreeResponse(QVariantHash &response)
{
    QHash<QString, QVariant > usertree;
    sTree = response["AllTree"].toHash();

    for (QHash<QString, QVariant >::iterator it = sTree.begin(); it != sTree.end(); ++it)
    {
        if (it.value().toHash()["type"] == "CLASSES")
        {
            fillStudentTree(usertree, it.value().toHash(), it.key().toInt());
        }
    }
    sTree = usertree;
    fillUiStudentTree();
}
void    UserFram::fillUiStudentTree()
{

}

void    UserFram::fillStudentTree(QHash<QString, QVariant > &usertree, QHash<QString, QVariant > node, int nodeid)
{
    QHash<QString, QVariant > tmptree;
    tmptree.insert("type", node["type"]);
    tmptree.insert("name", node["name"]);
    tmptree.insert("userref", node["userref"]);
    tmptree.insert("parentid", node["parentid"]);
    if (node["type"] == "GRADE")
        tmptree.insert("numberofsons", 0);
    else
        tmptree.insert("numberofsons", node["numberofsons"]);
    tmptree.insert("userlist", node["userlist"]);
    if (node["type"] == "GRADE")
        tmptree.insert("sons", QList<QVariant>());
    else
        tmptree.insert("sons", QVariant(node["sons"]));
    usertree.insert(QVariant(nodeid).toString(), tmptree);
    if (node["type"] != "GRADE")
    {
        for (int i = 0; i < node["sons"].toList().size(); i++)
        {
            for (QHash<QString, QVariant >::iterator it = sTree.begin(); it != sTree.end(); ++it)
            {

                if ((it.key() == node["sons"].toList().at(i)))
                {
                    fillStudentTree(usertree, it.value().toHash(), it.key().toInt());
                }
            }
        }
    }
}*/

void    TreeFram::unknownResponse(QVariantHash &response)
{

}
void    TreeFram::updateTree(QVariantHash tree)
{
   /* for (QHash<QString, QVariant >::const_iterator it = usertree.begin(); it != usertree.end(); ++it)
    {
        qDebug() << "User Tree node :" << it.key();
        tmplist = it.value().toList();
       for (int i = 0; i < tmplist.size(); ++i)
        {
          qDebug() << " sons :" << (tmplist.value(i));
        }
    }*/
    //build index
    //this->show();
}

void    TreeFram::getTree()
{
    QVariantHash request;
    request["Request"]=  "getTree";
    /*QTreeWidgetItem *cours1 = new QTreeWidgetItem(this);
    cours1->setText(0,"cours 1");

    //build child
    QTreeWidgetItem *lesson1 = new QTreeWidgetItem(cours1);
    lesson1->setText(0,"lesson 1");

    QTreeWidgetItem *cours2 = new QTreeWidgetItem;
    cours2->setText(0,"cours 2");

    this->insertTopLevelItem(0, cours1);
    this->insertTopLevelItem(1, cours2);*/
    //this->show();
}

void    TreeFram::getNodInfo()
{
    QVariantHash request;

    request["Request"] = "getNodeInfo";
    request["idNode"] = "";
}

void            TreeFram::deleteNode(QString idNode)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Delnode";
    request["Id"] = "";
}

void            TreeFram::moveNode(QString from, QString to)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Mvnode";
    request["Id"] = from;
    request["Newfather"] = to;
}

void            TreeFram::editNode(QString id, QString type, QString name, QString userId)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Addnode";
    request["Newfather"] = id;
    request["Type"] = type;
    request["Name"] = name;
    request["UserRef"] = userId;
}

void    TreeFram::getTreeResponse(QVariantHash &response)
{

}

void    TreeFram::getNodInfoResponse(QVariantHash &response)
{

}

void    TreeFram::editNodeResponse(QVariantHash &response)
{
    if (response["Admntreeact"] == "Addnode")
    {

    }
    else if (response["Admntreeact"] == "Mvnode")
    {

    }
    else if (response["Admntreeact"] == "Delnode")
    {

    }
}

