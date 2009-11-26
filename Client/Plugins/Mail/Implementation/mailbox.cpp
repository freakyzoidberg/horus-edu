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
#include "mailbox.h"
#include "ui_mailbox.h"
#include "email.h"

mailbox::mailbox(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::mailboxClass)
{
    from = "inconnu";
    to = "";
    subject = "aucun sujet";
    content = "";
    qDebug("lancement interface mail");
    ui->setupUi(this);
    hideall();
    QObject::connect( ui->new_message, SIGNAL(clicked()), this, SLOT(new_message()) );
    QObject::connect( ui->mailbox, SIGNAL(clicked()), this, SLOT(show_box()) );
    QObject::connect( ui->pushButton_send, SIGNAL(clicked()), this, SLOT(send_message()) );
}

mailbox::~mailbox()
{
    delete ui;
}

void mailbox::new_message()
{
    hideall();
    ui->widget_send_message->show();
}

void mailbox::show_box()
{
    hideall();
    ui->widget_mailbox->show();
    qDebug("nouveau message");


}

void mailbox::send_message()
{
    this->from = ui->lineEdit_from->text();
    this->to = ui->lineEdit_to->text();
    this->subject = ui->lineEdit_subject->text();
    this->content = ui->content_message->toPlainText();
    qDebug() <<"from : " << this->from;
    qDebug() <<"to : " << this->to;
   qDebug() <<"Subject : " << this->subject;
   qDebug() <<"conent : " << this->content;

    email *send_mail = new email();
}

void mailbox::hideall()
{
    ui->widget_send_message->hide();
    ui->widget_mailbox->hide();
}
