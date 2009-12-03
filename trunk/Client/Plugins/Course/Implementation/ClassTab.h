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
#ifndef CLASSTAB_H
#define CLASSTAB_H

#include <QWidget>
#include <QGridLayout>
#include <QListView>
#include <QPushButton>
#include <QLabel>

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/UserData.h"
#include "WhiteBoardListModel.h"

class ClassTab : public QWidget
{
	Q_OBJECT

public:
	ClassTab(PluginManager *pluginManager, UserData* user);

public slots:
        void	wbSelectionChanged(QItemSelection current, QItemSelection previous);
        void	createNewWhiteboard();

        void    leaveWhiteboard();
        void    deleteWhiteboard();
        void    joinWhiteboard();
        void    updateWbList(Data*);

private:
        void    doJoinWhiteboard(WhiteBoardData*);

private:
	PluginManager*	_pluginManager;
	UserData*		_user;
	QGridLayout*	_layout;
	QWidget*		_selectWbWidget;
        QWidget*                _wbWidget;
	QListView*		_wbList;
	QPushButton*	_joinButton;
	QPushButton*	_createButton;
	QPushButton*	_deleteButton;
	QLabel*			_info;
	QWidget*		_createWbWidget;

	WhiteBoardListModel*	_wbListModel;
};

#endif // CLASSTAB_H
