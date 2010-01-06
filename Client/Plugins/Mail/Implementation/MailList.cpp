/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "MailList.h"
#include <QHeaderView>
#include <QList>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QModelIndex>
#include "MailForm.h"
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





MailList::MailList(MailDataPlugin *MailPlugin, MailPanel *panel)
 {
    _panel = panel;
    _MailPlugin = MailPlugin;
    _mn = _MailPlugin->pluginManager->findPlugin<MailsNetwork*>();


    QHBoxLayout *ligne0 = new QHBoxLayout();
    QHBoxLayout *ligne1 = new QHBoxLayout();
    QHBoxLayout *ligne2 = new QHBoxLayout();
    QHBoxLayout *ligne3 = new QHBoxLayout();
    to_edit = new QLabel();
    cc_edit = new QLabel();
    sub_edit = new QLabel();
    lto_edit = new QLabel();
    lcc_edit = new QLabel();

    QSize size64(64,64);
    QSize size32(32,32);
    QSize size16(16,16);
    QSize size8(8,8);

    maxi = new QPushButton();
    maxi->setIcon(QIcon(":/expand.png"));
    maxi->setIconSize(size16);
    //maxi->setMaximumSize(32,32);
    maxi->setMaximumWidth(32);
    maxi->setToolTip(tr("expand"));
    ligne0->addWidget(maxi);

    connect(maxi, SIGNAL(clicked()), this, SLOT(expandshrink()));
ligne0->addStretch(20);


    rep = new QPushButton();
    rep->setIcon(QIcon(":/reply.png"));
    rep->setIconSize(size32);
    rep->setToolTip(tr("reply"));
    //rep->setMaximumSize(64,64);
connect(rep, SIGNAL(clicked()), this, SLOT(reply()));
    ligne0->addWidget(rep, 0, Qt::AlignRight);

    repall = new QPushButton();
    repall->setIcon(QIcon(":/replyall.png"));
    repall->setIconSize(size32);
    //repall->setMaximumSize(64,64);
    connect(repall, SIGNAL(clicked()), this, SLOT(reply()));
    repall->setToolTip(tr("reply to all"));

    ligne0->addWidget(repall,0, Qt::AlignRight);

    to_edit->setMinimumSize(500,10);
    cc_edit->setMinimumSize(500,10);


    lto_edit->setText(tr("From:"));
    lcc_edit->setText(tr("Cc:"));
    ligne1->addWidget(lto_edit,0, Qt::AlignLeft);
    ligne1->addWidget(to_edit,1);

    ligne2->addWidget(lcc_edit,0, Qt::AlignLeft);
    ligne2->addWidget(cc_edit, 1);

    ligne3->addWidget(sub_edit);


    QVBoxLayout *maildisplay = new QVBoxLayout();
    QGridLayout *proxyLayout = new QGridLayout();

     proxyModel = new QSortFilterProxyModel();
     proxyView = new QTreeView();
    mailview = new TextBrowser();
    mailview->setFontFamily("Serif");
    mailview->setReadOnly(true);
    mailview->setOpenExternalLinks(true);
    connect(proxyView, SIGNAL(doubleClicked(QModelIndex)),this, SLOT(rowDoubleClicked(QModelIndex)));

     proxyModel->setDynamicSortFilter(true);

     proxyView->setEditTriggers(QAbstractItemView::NoEditTriggers);
     proxyView->setRootIsDecorated(false);
     proxyView->setAlternatingRowColors(true);
     proxyView->setModel(proxyModel);
     proxyView->setSortingEnabled(false);
     maildisplay->addLayout(ligne0);
     maildisplay->addLayout(ligne1);
     maildisplay->addLayout(ligne2);
     maildisplay->addLayout(ligne3);
     maildisplay->addWidget(mailview);
    
    //proxyLayout->addWidget(new QPushButton("toto"), 0, 0, 1, 1);
     btn = new QPushButton(tr("refresh"));
     btn->setStyleSheet("QPushButton {text-align: center; background-color: lightblue; border:none; border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px} QPushButton:pressed { background-color: rgb(224, 0, 0); border-style: inset;}");

connect(btn, SIGNAL(clicked()),this,SLOT(update()));
proxyLayout->setColumnStretch(0,2);
proxyLayout->setColumnStretch(1,0);
proxyLayout->setColumnStretch(2,2);

     proxyLayout->addWidget(btn,0,1,1,1);
     proxyLayout->addWidget(proxyView, 1, 0, 1, 3);
     proxyLayout->addLayout(maildisplay,2,0, 1, 3);
expanded = false;
     setmailvisible(false);

     setLayout(proxyLayout);

     this->setSourceModel(createMailModel(this));

     proxyView->hideColumn(0);

	foreach (Data* d, _MailPlugin->allDatas())
	{
		MailData* data = (MailData*)d;
         if (data->getBox() == "INBOX")
        addMail(model,data->getSubject(),data->getFrom(),QDateTime(QDate()), data->getContent(), data->getId(), data);
	}

        connect(MailPlugin, SIGNAL(dataUpdated(Data*)),this,  SLOT(addMail(Data*)));
}

void MailList::setmailvisible(bool state)
{
    mailview->setVisible(state);
    lcc_edit->setVisible(state);
    lto_edit->setVisible(state);
    to_edit->setVisible(state);
    cc_edit->setVisible(state);
    sub_edit->setVisible(state);
    maxi->setVisible(state);
    rep->setVisible(state);
    repall->setVisible(state);

}
 void MailList::setSourceModel(QAbstractItemModel *model)
 {
     proxyModel->setSourceModel(model);
 }

 void MailList::addMail(QAbstractItemModel *model, const QString &subject,
               const QString &sender, const QDateTime &date, const QString &content, const QString &id, MailData *mail)
  {

      model->insertRow(0);
      model->setData(model->index(0, 0), id);
      model->setData(model->index(0, 1), subject);
      model->setData(model->index(0, 2), sender);
      model->setData(model->index(0, 3), date);

      mailpool.insert(id, content);

      if (mail!=0)
          mailpool2.insert(id, mail);

  }

 void MailList::addMail(Data *mail2)
  {
     MailData *mail = static_cast<MailData*>(mail2);
    if (mail!=0)
         {
          model->insertRow(0);
      model->setData(model->index(0, 0), mail->getId());
      model->setData(model->index(0, 1), mail->getSubject());
      model->setData(model->index(0, 2), mail->getFrom());
      model->setData(model->index(0, 3), QDateTime(QDate()));

      mailpool.insert(mail->getId(), mail->getContent());


          mailpool2.insert(mail->getId(), mail);
      }
  }


 QAbstractItemModel *MailList::createMailModel(QObject *parent)
  {
      model = new QStandardItemModel(0, 4, parent);
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("id") );
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Subject"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Sender"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));



      return model;
  }

 void MailList::rowDoubleClicked(QModelIndex indx)
 {
       setmailvisible(true);
       current = model->data(model->index(indx.row(),0),0).toString();


        mailview->setHtml(mailpool[model->data(model->index(indx.row(),0),0).toString()]);
        if (mailpool2[model->data(model->index(indx.row(),0),0).toString()] != 0)
        {
            if (mailpool2[model->data(model->index(indx.row(),0),0).toString()]->getCc().count() > 0)
            {
            cc_edit->setVisible(true);
            lcc_edit->setVisible(true);
            int i;
                    QString res = "";
            for (i =0; i < mailpool2[model->data(model->index(indx.row(),0),0).toString()]->getCc().count(); i++)
            {
                res += mailpool2[model->data(model->index(indx.row(),0),0).toString()]->getCc().at(i);
                if (i < mailpool2[model->data(model->index(indx.row(),0),0).toString()]->getCc().count())
                    res+=", ";
            }
            cc_edit->setText(res);
            }
            else
            {
                cc_edit->setVisible(false);
                lcc_edit->setVisible(false);
            }
        }
        else
        {
            cc_edit->setVisible(false);
            lcc_edit->setVisible(false);
        }
        to_edit->setText(model->data(model->index(indx.row(),2),0).toString());
        sub_edit->setText(model->data(model->index(indx.row(),1),0).toString());
//        mailview->setText(mailpool[model->i]);


        //qDebug() << indx.row() <<" " << indx.data();
     //QMessageBox::information(NULL, "here", QString("Row ")+QString("was double clicked"));
 }

 void MailList::linkclick(const QString &link)
 {
         QMessageBox::information(NULL, "here", QString("devrait ouvrir un browser sur le systeme avec ")+link);
 }

 void MailList::expandshrink()
 {
     if (!expanded)
     {
        proxyView->setVisible(false);
        expanded = true;
    }
     else
     {
         proxyView->setVisible(true);
         expanded = false;
     }
 }

 void MailList::update()
 {
     btn->clearFocus();
    //_mn->update();
    QMetaObject::invokeMethod(_mn,"update");
 }

 void MailList::reply()
 {
    _panel->getForm()->setto(to_edit->text());
    _panel->getForm()->setsub("RE:"+sub_edit->text());

    _panel->getForm()->setcontent(mailpool[current]);
     _panel->setCurrentWidget(_panel->getForm());
    //MailForm *mp = new MailForm(_MailPlugin);
 }

 void MailList::replyall()
 {
    _panel->getForm()->setto(to_edit->text());
    _panel->getForm()->setcc(cc_edit->text());
    _panel->getForm()->setsub("RE:"+sub_edit->text());
    _panel->getForm()->setcontent(mailpool[current]);
     _panel->setCurrentWidget(_panel->getForm());
    //MailForm *mp = new MailForm(_MailPlugin);
 }
