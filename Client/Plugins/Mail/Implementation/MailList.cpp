#include "MailList.h"
#include <QHeaderView>
#include <QList>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QModelIndex>
#include "../../../../Common/DataImplementations/MailData/MailData.h"
MailList::MailList(MailDataPlugin *MailPlugin)
{
_MailPlugin = MailPlugin;

    MailData *md = _MailPlugin->createMail();
    emailList = new QTableView();

connect(emailList, SIGNAL(clicked(QModelIndex)),  this, SLOT(myClicked(QModelIndex)));

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

    MailAbstractModel *listmodel = new MailAbstractModel();

emailList->horizontalHeader()->setStretchLastSection(true);
    int mailtotal = list.count();
    int i = 0;
    qDebug() << list.count();
    listmodel->setRow(list.count());
    foreach (MailData* data, list)
    {

        qDebug() << data->getSubject();
        qDebug() << data->getMDate();
        qDebug() << listmodel->setData(listmodel->index(i,0),mailtotal - i, Qt::EditRole);
        qDebug() << data->getFrom();
        qDebug() << listmodel->setData(listmodel->index(i,2),data->getFrom(), Qt::EditRole);
        qDebug() << listmodel->setData(listmodel->index(i,3),data->getSubject(), Qt::EditRole);
        //qDebug() << listmodel->setData(listmodel->index(i,2),data->getFrom(), Qt::EditRole);
        qDebug() << listmodel->setData(listmodel->index(i,1),data->getMDate(), Qt::EditRole);
    i++;
    //    toto.append(data->getSubject());
    }
    QVBoxLayout *total = new QVBoxLayout();
        emailList->verticalHeader()->hide();
        emailList->sortByColumn(0);
    emailList->setShowGrid(false);



    //listmodel->RefreshList();

    //listmodel->setRow(4);

    //listmodel->setStringList(toto);
    emailList->setEditTriggers(0);
    emailList->setModel(listmodel);
    total->addWidget(emailList);
    emailList->resizeColumnsToContents();

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


void MailList::myClicked(QModelIndex idx)
{
    emailList->selectRow(idx.row());
}

MailList::~MailList()
{
}

