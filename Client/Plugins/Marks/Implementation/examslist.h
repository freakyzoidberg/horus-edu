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

#ifndef EXAMSLIST_H
#define EXAMSLIST_H

#include <QWidget>
#include <QListWidget>
#include <QMap>
#include <QLineEdit>
#include <QVBoxLayout>

#include "../../../../Common/UserData.h"
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeDataPlugin.h"
#include "../../../../Common/ExamsDataPlugin.h"

class ExamsList : public QWidget
{

	Q_OBJECT
public:
	ExamsList(PluginManager *pluginManager, QVBoxLayout *RightLayout);
	void	fillExamsList();
	QMap<int, QString>	getallexams();
	QMap<int, QString>  Exams(quint32 userId);
	QMap<int, QString>  Exams(TreeData *node);
	TreeData *_node;
QListWidget		*_examsList;


private slots:
	//void showExams(QListWidgetItem *);
	void addAnExam();
	void selectStudents(QListWidgetItem *item);

private:

	TreeDataPlugin	*treePlugin;
	ExamsDataPlugin	*examsPlugin;
	PluginManager	*_pluginManager;
	QLineEdit		*examComment;
};

#endif // EXAMSLIST_H
