#include "MailList.h"
#include <QHeaderView>
#include <QList>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include "../../../../Common/DataImplementations/MailData/MailData.h"
MailList::MailList(MailDataPlugin *MailPlugin)
{
_MailPlugin = MailPlugin;

    MailData *md = _MailPlugin->createMail();



    //md->getMail();

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

    QStringList toto;
    QList<MailData*> list;

    list = _MailPlugin->getAllMail();

    foreach (MailData* data, list)
    toto.append(data->getSubject());

    QVBoxLayout *total = new QVBoxLayout();
    QListView *emailList = new QListView();


    QStringListModel *listmodel = new QStringListModel();

    listmodel->setStringList(toto);
emailList->setEditTriggers(0);
    emailList->setModel(listmodel);
    total->addWidget(emailList);


/*
  this->addColumn( "Mail id" );
  this->addColumn( "From" );
  this->addColumn( "Subject" );
  this->addColumn( "Date - Time" );

  this->setRootIsDecorated( true );

  QListViewItem *root = new QListViewItem(this, "root" );

  QListViewItem *a = new QListViewItem( root, "A" );
  QListViewItem *b = new QListViewItem( root, "B" );
  QListViewItem *c = new QListViewItem( root, "C" );

  new QListViewItem( a, "foo", "1", "2", "3" );
  new QListViewItem( a, "bar", "i", "ii", "iii" );
  new QListViewItem( a, "baz", "a", "b", "c" );

  new QListViewItem( b, "foo", "1", "2", "3" );
  new QListViewItem( b, "bar", "i", "ii", "iii" );
  new QListViewItem( b, "baz", "a", "b", "c" );

  new QListViewItem( c, "foo", "1", "2", "3" );
  new QListViewItem( c, "bar", "i", "ii", "iii" );
  new QListViewItem( c, "baz", "a", "b", "c" );
*/
    setLayout(total->layout());




}

MailList::~MailList()
{
}

