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
#ifndef MAILLIST_H
#define MAILLIST_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include <QListView>
#include                        "../../../../Common/DataImplementations/MailData/MailDataPlugin.h"
#include "MailAbstractModel.h"
#include "TextBrowser.h"
#include "MailPanel.h"
#include "MailsNetwork.h"

class				MailPanel;
//class MailList;
class MailList : public QWidget
{
     Q_OBJECT
public:
    MailList(MailDataPlugin *MailPlugin, MailPanel *panel);
    ~MailList();

private:
    MailDataPlugin *_MailPlugin;
    void setmailvisible(bool state);
    void setSourceModel(QAbstractItemModel *model);
    void addMail(QAbstractItemModel *model, const QString &subject, const QString &sender, const QDateTime &date,           const QString &content, const QString &id, MailData *mail = 0);

private slots:
    void rowDoubleClicked(QModelIndex indx);
    void linkclick(const QString &link);
    void expandshrink();
    void reply();
    void replyall();
    void update();
    void addMail(Data *mail);
private:
    MailsNetwork *_mn;
    QPushButton *btn;
    bool expanded;
    QString current;
    MailPanel *_panel;
    TextBrowser *mailview;
    QLabel *to_edit;
    QLabel *cc_edit;
    QLabel *sub_edit;
    QPushButton *maxi;
    QPushButton *rep;
    QPushButton *repall;
    QLabel *lto_edit;
    QLabel *lcc_edit;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QTreeView *proxyView;
    QAbstractItemModel *createMailModel(QObject *parent);
    QMap<QString, QString> mailpool;
    QMap<QString, MailData*> mailpool2;
};

#endif // MAILPANEL_H
