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
#ifndef MANAGEEDT_H
#define MANAGEEDT_H

#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QFrame>
#include <QListWidget>
#include <QMap>
#include <QString>
#include <QListWidgetItem>

# include "../../../../Common/PluginManager.h"
# include "../../../../Common/UserData.h"
#include "admclasslistselection.h"
#include "infopanel.h"

#include "AdmListEdt.h"

class ManageEdt : public QWidget
{
	Q_OBJECT

public:
							ManageEdt(PluginManager *pluginManager);
	QListWidget				*StudentList;

public slots:
		void				classSelected(QListWidgetItem *);

private:
	PluginManager			*_pluginManager;
	QHBoxLayout				*MainLayout;
	AdmListEdt				*_admEDTList;
	QFrame					*informationsFrame;
	QVBoxLayout				*informationsLayout;
	InfoPanel				*infos;

	QPushButton				*del;
	QPushButton				*edit;
	QPushButton				*ok;
	QPushButton				*save;
	QPushButton				*reset;
	QPushButton				*back;
	QPushButton				*add;

	AdmClassListSelection	*AdmClassList;
};

#endif // MANAGEEDT_H
