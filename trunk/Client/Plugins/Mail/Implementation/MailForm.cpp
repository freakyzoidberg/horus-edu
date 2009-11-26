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
#include "MailForm.h"
#include "../../../../Common/DataImplementations/MailData/MailData.h"
MailForm::MailForm(MailDataPlugin *MailPlugin)
{
    ;
    _MailPlugin = MailPlugin;
    QVBoxLayout *total = new QVBoxLayout();
    QHBoxLayout *ligne1 = new QHBoxLayout();
    QHBoxLayout *ligne1_1 = new QHBoxLayout();
    QHBoxLayout *ligne1_2 = new QHBoxLayout();
    QHBoxLayout *ligne2 = new QHBoxLayout();
    QHBoxLayout *ligne3 = new QHBoxLayout();
    QHBoxLayout *ligne4 = new QHBoxLayout();


    QLabel *to = new QLabel(tr("To :"));
    to_value = new QLineEdit();
    to_value->setMinimumSize(500,1);
    ligne1->addWidget(to,0,Qt::AlignLeft);
    ligne1->addWidget(to_value,1);


    QLabel *cc = new QLabel(tr("cc :"));
    cc_value = new QLineEdit();
    cc_value->setMinimumSize(500,1);
    ligne1_1->addWidget(cc,0,Qt::AlignLeft);
    ligne1_1->addWidget(cc_value,1);


    QLabel *bcc = new QLabel(tr("bcc :"));
    bcc_value = new QLineEdit();
    bcc_value->setMinimumSize(500,1);
    ligne1_2->addWidget(bcc,0,Qt::AlignLeft);
    ligne1_2->addWidget(bcc_value,1);

    QLabel *subject = new QLabel(tr("Subject :"));
    subject_value = new QLineEdit();
    subject_value->setMinimumSize(500,10);
    ligne2->addWidget(subject,0,Qt::AlignLeft);
    ligne2->addWidget(subject_value,1);


    content_value = new QTextEdit();

    content_value->setFontFamily("Serif");
    ligne3->addWidget(content_value,1);


    sendbtn = new QPushButton(tr("Send"));
    ligne4->addWidget(sendbtn,1, Qt::AlignRight);

    total->addLayout(ligne1->layout(),0);
    total->addLayout(ligne1_1->layout(),0);
    total->addLayout(ligne1_2->layout(),0);
    total->addLayout(ligne2->layout(),0);
    total->addLayout(ligne3->layout(),1);
    total->addLayout(ligne4->layout(),0);

    total->setAlignment(ligne1->layout(), Qt::AlignTop);
    total->setAlignment(ligne1_1->layout(), Qt::AlignTop);
    total->setAlignment(ligne1_2->layout(), Qt::AlignTop);
    total->setAlignment(ligne2->layout(), Qt::AlignTop);
    total->setAlignment(ligne3->layout(), Qt::AlignTop);
    total->setAlignment(ligne4->layout(), Qt::AlignTop);

    this->setLayout(total->layout());
    connect(sendbtn, SIGNAL(clicked()), this, SLOT(mysendmail()));
    connect(to_value, SIGNAL(textChanged(const QString&)), this, SLOT(validate()));
    connect(cc_value, SIGNAL(textChanged(const QString&)), this, SLOT(validate()));
    connect(bcc_value, SIGNAL(textChanged(const QString&)), this, SLOT(validate()));
    validate();
}

MailForm::~MailForm()
{
}

void MailForm::mysendmail()
{
	QRegExp mailregexp("^([a-zA-Z0-9_(\\.)(\\-)(\\+)])+\\@(([a-zA-Z0-9\\-])+(\\.))+([a-zA-Z0-9]{2,4})+$");
	QRegExp exmailregexp("^\\s*(\\w*\\s*)*(<\\s*)([a-zA-Z0-9_(\\.)(\\-)(\\+)])+\\@(([a-zA-Z0-9\\-])+(\\.))+([a-zA-Z0-9]{2,4})+(\\s*>)\\s*$");
	QStringList lto;
	QString tmp;
      if (!to_value->text().isEmpty())
        lto = to_value->text().split(",");
/*
      for (i = 0; i <= lto.count(); i++)
        {
          if (lto.at(i).contains(exmailregexp))
          {
            mailregexp.indexIn(lto.at(i));
            lto.replace(i, mailregexp.capturedTexts().first());

            qDebug() << "Mail Search and replace to" << lto.at(i);
          }
      }
*/
   
    QStringList lcc;
      if (!cc_value->text().isEmpty())
        lcc = cc_value->text().split(",");
/*
      for (i = 0; i <= lcc.count(); i++)
        {
          if (lcc.at(i).contains(exmailregexp))
          {
            mailregexp.indexIn(lcc.at(i));

              lcc.replace(i, mailregexp.capturedTexts().first());
            qDebug() << "Mail Search and replace cc" << lto.at(i);
          }
      }
*/
    QStringList lbcc;
      if (!bcc_value->text().isEmpty())
        lbcc = bcc_value->text().split(",");

/*
      for (i = 0; i <= lbcc.count(); i++)
        {
          if (lbcc.at(i).contains(exmailregexp))
          {
            mailregexp.indexIn(lbcc.at(i));

              lbcc.replace(i, mailregexp.capturedTexts().first());
            qDebug() << "Mail Search and replace bcc :" << lto.at(i);
          }
      }
*/
    MailData *md = _MailPlugin->createMail();
    //MailData *md = new MailData(_MailPlugin);

    md->setTo(lto);
    md->setCc(lcc);
    md->setBcc(lbcc);
    md->setSubject(subject_value->text());
    md->setContent(content_value->toHtml());
    //qDebug() << ;

    QString nid = QTime::currentTime().toString("hh:mm:ss.zzz");


   qDebug() << "new id " << nid;
    md->setId(nid);


    md->sendMail();


    to_value->setText("");
    cc_value->setText("");
    bcc_value->setText("");
    subject_value->setText("");
    content_value->setText("");
    //}
}

void MailForm::validate()
{

    QStringList lto;
      if (!to_value->text().isEmpty())
        lto = to_value->text().split(",");
    QStringList lcc;
      if (!cc_value->text().isEmpty())
        lcc = cc_value->text().split(",");
    QStringList lbcc;
      if (!bcc_value->text().isEmpty())
        lbcc = bcc_value->text().split(",");
    QRegExp mailregexp("^\\s*([a-zA-Z0-9_(\\.)(\\-)(\\+)])+\\@(([a-zA-Z0-9\\-])+(\\.))+([a-zA-Z0-9]{2,4})+\\s*$");
    QRegExp exmailregexp("^\\s*(\\w*\\s*)*(<\\s*)([a-zA-Z0-9_(\\.)(\\-)(\\+)])+\\@(([a-zA-Z0-9\\-])+(\\.))+([a-zA-Z0-9]{2,4})+(\\s*>)\\s*$");
    int i = 0;
    bool cto = false;
    bool ccc = true;
    bool cbcc = true;

    if (lto.count() > 0)
    {
        foreach (QString mail, lto)
            if (mail.contains(mailregexp) || mail.contains(exmailregexp))
            i++;

        if (lto.count() == i)
            cto = true;
        else
            cto = false;
        if (lcc.count() > 0)
        {
            i = 0;
            foreach (QString mail, lcc)
            if (mail.contains(mailregexp)|| mail.contains(exmailregexp))
            i++;

            if (lcc.count() == i)
            ccc=true;
            else
            ccc=false;
        }
        else
            ccc = true;

        if (lbcc.count() > 0)
        {
            i = 0;
            foreach (QString mail, lbcc)
            if (mail.contains(mailregexp)|| mail.contains(exmailregexp))
            i++;

            if (lbcc.count() == i)
            cbcc=true;
            else
            cbcc=false;
        }
        else
            cbcc = true;
    }
    else
       cto = false;


    if ((cto == true) && (ccc == true) && (cbcc == true))
        sendbtn->setEnabled(true);
    else
        sendbtn->setEnabled(false);

if (cto == true)
to_value->setStyleSheet("background: lightgreen;");
else
to_value->setStyleSheet("background: salmon;");

if (ccc == true)
cc_value->setStyleSheet("background: lightgreen;");
else
cc_value->setStyleSheet("background: salmon;");

if (cbcc == true)
bcc_value->setStyleSheet("background: lightgreen;");
else
bcc_value->setStyleSheet("background: salmon;");
}
