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

#ifndef MARKSMANAGER_H
#define MARKSMANAGER_H

#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/ExamsDataPlugin.h"
#include "InfoPanel.h"
#include "ClassList.h"
#include <QTabWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>


class MarksMainView;
class MarksManager : public QWidget
{
	Q_OBJECT

public:
	MarksManager(PluginManager *, MarksMainView *);
	QListWidget				*StudentList;

public slots:
	void	subjectSelected(QListWidgetItem *);
	void	moveToExamList(QListWidgetItem *);
	void	addExam();
	void	move();

private:
	TreeDataPlugin          *td;
	QHBoxLayout				*MainLayout;
	ClassList *				_classList;
	//AdmListEdt				*_admEDTList;
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
	MarksMainView			*_parent;
	PluginManager			*_pm;
	QListWidgetItem			*_item;
};

#endif // MARKSMANAGER_H
