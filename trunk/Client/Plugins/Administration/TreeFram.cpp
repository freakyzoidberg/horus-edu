#include "TreeFram.h"
#include <QDebug>

TreeFram::TreeFram(INetwork *reseau) : QFrame()
{
    setupUi(this);
    requestFunctions["getTree"]         = &TreeFram::getTreeResponse;
    requestFunctions["getNodeInfo"]     = &TreeFram::getNodInfoResponse;
    requestFunctions["setNode"]         = &TreeFram::editNodeResponse;
    this->connect(this->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(itemClicked(QTreeWidgetItem*, int)));
    getTree();
}

void TreeFram::itemClicked(QTreeWidgetItem *item, int idx)
{
    qDebug() << item->text(0);
}

void TreeFram::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void    TreeFram::readResponse(QVariantHash response)
{
    (this->*requestFunctions.value(response["Request"].toByteArray(),
                                   &TreeFram::unknownResponse))
                                   (response);
}

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
    QTreeWidgetItem *cours1 = new QTreeWidgetItem(this->treeWidget);
    cours1->setText(0,"cours 1");

    //build child
    QTreeWidgetItem *lesson1 = new QTreeWidgetItem(cours1);
    lesson1->setText(0,"lesson 1");

    QTreeWidgetItem *cours2 = new QTreeWidgetItem;
    cours2->setText(0,"cours 2");

    this->treeWidget->insertTopLevelItem(0, cours1);
    this->treeWidget->insertTopLevelItem(1, cours2);
    this->treeWidget->show();
}

void    TreeFram::getTree()
{
    QVariantHash request;
    request["Request"]=  "getTree";
        QTreeWidgetItem *cours1 = new QTreeWidgetItem(this->treeWidget);
    cours1->setText(0,"Promos");

    //build child
    QTreeWidgetItem *lesson1 = new QTreeWidgetItem(cours1);
    lesson1->setText(0,"Class");

    QTreeWidgetItem *cours2 = new QTreeWidgetItem;
    cours2->setText(0,"Profs");

    this->treeWidget->insertTopLevelItem(0, cours1);
    this->treeWidget->insertTopLevelItem(1, cours2);
    this->treeWidget->show();
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

