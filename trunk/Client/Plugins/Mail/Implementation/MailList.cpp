#include "MailList.h"
#include <QHeaderView>
#include <QList>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QModelIndex>

#include "../../../../Common/DataImplementations/MailData/MailData.h"
/*
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
//888/
    setLayout(total->layout());




}


void MailList::myClicked(QModelIndex idx)
{
    emailList->selectRow(idx.row());
}
*/
MailList::~MailList()
{
}





MailList::MailList(MailDataPlugin *MailPlugin)
 {
    _MailPlugin = MailPlugin;
    QList<MailData*> list;

    list = _MailPlugin->getAllMail();


     MailData *md = _MailPlugin->createMail();
     proxyModel = new QSortFilterProxyModel;
     proxyModel->setDynamicSortFilter(true);

     //sourceGroupBox = new QGroupBox(tr("Original Model"));
     proxyGroupBox = new QGroupBox(tr("Sorted/Filtered Model"));

     //sourceView = new QTreeView;
     //sourceView->setRootIsDecorated(false);
     //sourceView->setAlternatingRowColors(true);

     proxyView = new QTreeView;
     proxyView->setEditTriggers(QAbstractItemView::NoEditTriggers);

     proxyView->setRootIsDecorated(false);
     proxyView->setAlternatingRowColors(true);
     proxyView->setModel(proxyModel);
     proxyView->setSortingEnabled(true);

     sortCaseSensitivityCheckBox = new QCheckBox(tr("Case sensitive sorting"));
     filterCaseSensitivityCheckBox = new QCheckBox(tr("Case sensitive filter"));

     filterPatternLineEdit = new QLineEdit;
     filterPatternLabel = new QLabel(tr("&Filter pattern:"));
     filterPatternLabel->setBuddy(filterPatternLineEdit);

     filterSyntaxComboBox = new QComboBox;
     filterSyntaxComboBox->addItem(tr("Regular expression"), QRegExp::RegExp);
     filterSyntaxComboBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
     filterSyntaxComboBox->addItem(tr("Fixed string"), QRegExp::FixedString);
     filterSyntaxLabel = new QLabel(tr("Filter &syntax:"));
     filterSyntaxLabel->setBuddy(filterSyntaxComboBox);

     filterColumnComboBox = new QComboBox;
     filterColumnComboBox->addItem(tr("Subject"));
     filterColumnComboBox->addItem(tr("Sender"));
     filterColumnComboBox->addItem(tr("Date"));
     filterColumnLabel = new QLabel(tr("Filter &column:"));
     filterColumnLabel->setBuddy(filterColumnComboBox);

     mailview = new QTextEdit();

     connect(filterPatternLineEdit, SIGNAL(textChanged(const QString &)),
             this, SLOT(filterRegExpChanged()));
     connect(filterSyntaxComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(filterRegExpChanged()));
     connect(filterColumnComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(filterColumnChanged()));
     connect(filterCaseSensitivityCheckBox, SIGNAL(toggled(bool)),
             this, SLOT(filterRegExpChanged()));
     connect(sortCaseSensitivityCheckBox, SIGNAL(toggled(bool)),
             this, SLOT(sortChanged()));
     connect(proxyView, SIGNAL(doubleClicked(QModelIndex)),
                  this, SLOT(rowDoubleClicked(QModelIndex)));

     //QHBoxLayout *sourceLayout = new QHBoxLayout;
     //sourceLayout->addWidget(sourceView);
     //sourceGroupBox->setLayout(sourceLayout);

     QGridLayout *proxyLayout = new QGridLayout;
     proxyLayout->addWidget(proxyView, 0, 0, 1, 3);
     proxyLayout->addWidget(mailview,1,0,1,3);
     proxyLayout->addWidget(filterPatternLabel, 2, 0);
     proxyLayout->addWidget(filterPatternLineEdit, 2, 1, 1, 2);
     proxyLayout->addWidget(filterSyntaxLabel, 3, 0);
     proxyLayout->addWidget(filterSyntaxComboBox, 3, 1, 1, 2);
     proxyLayout->addWidget(filterColumnLabel, 4, 0);
     proxyLayout->addWidget(filterColumnComboBox, 4, 1, 1, 2);
     proxyLayout->addWidget(filterCaseSensitivityCheckBox, 5, 0, 1, 2);
     proxyLayout->addWidget(sortCaseSensitivityCheckBox, 5, 2);
     proxyGroupBox->setLayout(proxyLayout);


     mailview->setVisible(false);
     //QVBoxLayout *mainLayout = new QVBoxLayout;
   //  mainLayout->addWidget(sourceGroupBox);
     //mainLayout->addWidget(proxyGroupBox);


  //   setWindowTitle(tr("Basic Sort/Filter Model"));
  //   resize(500, 450);


     proxyView->sortByColumn(1, Qt::AscendingOrder);
     filterColumnComboBox->setCurrentIndex(1);

     filterPatternLineEdit->setText("Andy|Grace|pierre");
     filterCaseSensitivityCheckBox->setChecked(true);
     sortCaseSensitivityCheckBox->setChecked(true);
     setLayout(proxyLayout);




this->setSourceModel(createMailModel(this));
foreach (MailData* data, list)
{


    addMail(model,data->getSubject(),data->getFrom(),QDateTime(QDate()), data->getContent(), data->getId());

    //qDebug() << listmodel->setData(listmodel->index(i,2),data->getFrom(), Qt::EditRole);
    //qDebug() << listmodel->setData(listmodel->index(i,3),data->getSubject(), Qt::EditRole);
    //qDebug() << listmodel->setData(listmodel->index(i,1),data->getMDate(), Qt::EditRole);

}

 }

 void MailList::setSourceModel(QAbstractItemModel *model)
 {
     proxyModel->setSourceModel(model);
     //sourceView->setModel(model);
 }

 void MailList::filterRegExpChanged()
 {
     QRegExp::PatternSyntax syntax =
             QRegExp::PatternSyntax(filterSyntaxComboBox->itemData(
                     filterSyntaxComboBox->currentIndex()).toInt());
     Qt::CaseSensitivity caseSensitivity =
             filterCaseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive
                                                        : Qt::CaseInsensitive;

     QRegExp regExp(filterPatternLineEdit->text(), caseSensitivity, syntax);
     proxyModel->setFilterRegExp(regExp);
 }

 void MailList::filterColumnChanged()
 {
     proxyModel->setFilterKeyColumn(filterColumnComboBox->currentIndex());
 }

 void MailList::sortChanged()
 {
     proxyModel->setSortCaseSensitivity(
             sortCaseSensitivityCheckBox->isChecked() ? Qt::CaseSensitive
                                                      : Qt::CaseInsensitive);
 }

 void MailList::addMail(QAbstractItemModel *model, const QString &subject,
               const QString &sender, const QDateTime &date, const QString &content, const QString &id)
  {
     
      model->insertRow(0);
      model->setData(model->index(0, 0), subject);
      model->setData(model->index(0, 1), sender);
      model->setData(model->index(0, 2), date);
      model->setData(model->index(0, 3), id);
      mailpool.insert(id, content);

  }

 QAbstractItemModel *MailList::createMailModel(QObject *parent)
  {
      model = new QStandardItemModel(0, 3, parent);
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Subject"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sender"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));

      addMail(model, "Happy New Year!", "Grace K. <grace@software-inc.com>",
              QDateTime(QDate(2006, 12, 31), QTime(17, 03)), "test1", "1");
      addMail(model, "Radically new concept", "Grace K. <grace@software-inc.com>",
              QDateTime(QDate(2006, 12, 22), QTime(9, 44)), "test2", "2");
      addMail(model, "Accounts", "pascale@nospam.com",
              QDateTime(QDate(2006, 12, 31), QTime(12, 50)), "test3", "3");
      addMail(model, "Expenses", "Joe Bloggs <joe@bloggs.com>",
              QDateTime(QDate(2006, 12, 25), QTime(11, 39)),"test4", "4");
      addMail(model, "Re: Expenses", "Andy <andy@nospam.com>",
              QDateTime(QDate(2007, 01, 02), QTime(16, 05)), "test5", "5");
      addMail(model, "Re: Accounts", "Joe Bloggs <joe@bloggs.com>",
              QDateTime(QDate(2007, 01, 03), QTime(14, 18)), "test6", "6");
      addMail(model, "Re: Accounts", "Andy <andy@nospam.com>",
              QDateTime(QDate(2007, 01, 03), QTime(14, 26)), "test7", "7");
      addMail(model, "Sports", "Linda Smith <linda.smith@nospam.com>",
              QDateTime(QDate(2007, 01, 05), QTime(11, 33)), "test8", "8");
      addMail(model, "AW: Sports", "Rolf Newschweinstein <rolfn@nospam.com>",
              QDateTime(QDate(2007, 01, 05), QTime(12, 00)), "test9", "9");
      addMail(model, "RE: Sports", "Petra Schmidt <petras@nospam.com>",
              QDateTime(QDate(2007, 01, 05), QTime(12, 01)), "test10", "10");

      return model;
  }

 void MailList::rowDoubleClicked(QModelIndex indx)
 {
        mailview->setVisible(true);

//        mailview->setText(mailpool[model->i]);


        qDebug() << indx.row() <<" " << indx.data();
     //QMessageBox::information(NULL, "here", QString("Row ")+QString("was double clicked"));
 }
