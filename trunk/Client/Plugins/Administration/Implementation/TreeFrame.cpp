#include "TreeFrame.h"
#include <QDebug>
#include "../../../Common/PluginPacket.h"


TreeFrame::TreeFrame() : QTreeWidget()
{
    QTreeWidgetItem *hItem = this->headerItem();
    hItem->setText(0, "Groupes");
    requestFunctions["getTree"]         = &TreeFrame::getTreeResponse;
    requestFunctions["getNodeInfo"]     = &TreeFrame::getNodInfoResponse;
    requestFunctions["setNode"]         = &TreeFrame::editNodeResponse;
    this->connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
    getTree();
}

void TreeFrame::itemClicked(QTreeWidgetItem *item, int idx)
{
    qDebug() << item->text(0);
}

void    TreeFrame::readResponse(QVariantHash response)
{
    (this->*requestFunctions.value(response["Request"].toByteArray(),
                                   &TreeFrame::unknownResponse))
                                   (response);
}
/*
void    UserFrame::getTreeResponse(QVariantHash &response)
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
void    UserFrame::fillUiStudentTree()
{

}

void    UserFrame::fillStudentTree(QHash<QString, QVariant > &usertree, QHash<QString, QVariant > node, int nodeid)
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

void    TreeFrame::unknownResponse(QVariantHash &response)
{

}
void    TreeFrame::updateTree(QVariantHash tree)
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

void    TreeFrame::getTree()
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

void    TreeFrame::getNodInfo()
{
    QVariantHash request;

    request["Request"] = "getNodeInfo";
    request["idNode"] = "";
}

void            TreeFrame::deleteNode(QString idNode)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Delnode";
    request["Id"] = "";
}

void            TreeFrame::moveNode(QString from, QString to)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Mvnode";
    request["Id"] = from;
    request["Newfather"] = to;
}

void            TreeFrame::editNode(QString id, QString type, QString name, QString userId)
{
    QVariantHash request;

    request["Request"] = "setNode";
    request["Admntreeact"] = "Addnode";
    request["Newfather"] = id;
    request["Type"] = type;
    request["Name"] = name;
    request["UserRef"] = userId;
}

void    TreeFrame::getTreeResponse(QVariantHash &response)
{

}

void    TreeFrame::getNodInfoResponse(QVariantHash &response)
{

}

void    TreeFrame::editNodeResponse(QVariantHash &response)
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

