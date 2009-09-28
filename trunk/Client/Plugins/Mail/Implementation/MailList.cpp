#include "MailList.h"
#include <QHeaderView>
#include <QList>
#include <QListView>
MailList::MailList(MailDataPlugin *MailPlugin)
{
    //QList<QString> list;
    //list<<"Read"<<"From"<<"Subject"<<"date";
    //this->setHorizontalHeaderLabels(list);


    //QStringList sl;
// The following seems like a non-intuitive operator
// overload but that is how they do it...
    //sl << "First Column" << "Next Column" << "Last Column";
    //this->setHorizontalHeaderLabels(sl);
      //  this->horizontalHeader()->show();

    //this->setColumnCount(4);
    //QHeaderView *header = new QHeaderView(Qt::Horizontal,this);
    //header->setResizeMode(QHeaderView::ResizeToContents);

    //sthis->setHorizontalHeader(header);


    //QHeaderView *header = new QHeaderView(Qt::Horizontal);

    //this->setHorizontalHeader(header);
}

MailList::~MailList()
{
}

