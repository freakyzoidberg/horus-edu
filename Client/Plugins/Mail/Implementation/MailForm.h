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
#ifndef MAILFORM_H
#define MAILFORM_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include                        "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
//class MailForm;
class MailForm : public QWidget
{
Q_OBJECT
public:
    MailForm(MailDataPlugin *MailPlugin);
    ~MailForm();
    void setto(QString to) {to_value->setText(to);}
    void setcc(QString cc) {cc_value->setText(cc);}
    void setbcc(QString bcc) {bcc_value->setText(bcc);}
    void setsub(QString sub) {subject_value->setText(sub);}
    void setcontent(QString cont) {content_value->setText(cont);}
private :
    QLineEdit *to_value;
    QLineEdit *cc_value;
    QLineEdit *bcc_value;
    QLineEdit *subject_value;
    QTextEdit *content_value;
    QPushButton *sendbtn;
    QLabel *res_value;
    MailDataPlugin *_MailPlugin;

private slots:
        void mysendmail();
        void validate();

};

#endif // MAILPANEL_H
