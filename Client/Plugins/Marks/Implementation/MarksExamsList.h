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

#ifndef MARKSEXAMSLIST_H
#define MARKSEXAMSLIST_H

#include <QWidget>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QListWidget>
#include <QLabel>
#include "../../../../Common/PluginManager.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/ExamsData.h"
#include "../../../../Common/MarksData.h"
#include "../../../../Common/MarksDataPlugin.h"
#include "newexams.h"
#include "studentslist.h"
#include "examslist.h"
#include "formaddgrade.h"

class MarksExamsList : public QWidget
{
	Q_OBJECT
public:
							MarksExamsList(PluginManager *,
										   QTabWidget *);
	QListWidget				*StudentList;

	ExamsList				*examsList() { return _examsList; }
	QPushButton				*_add;
	TreeData				*_node;
	NewExams				*_formAdd;
	StudentsList			*_sList;
	QLabel					*_infosLabel;

public slots:
	void					addExam();
	void					saveExam();
	void					saveMark();
	void					fallback();
	void					removeMark();
	void					viewStudentList(QListWidgetItem *);
	void					studentSelection(QListWidgetItem *);
	void					examSelected(QListWidgetItem *);
	void					seeStudents();

private:
	TreeDataPlugin          *td;
	QListWidgetItem			*_item;
	QHBoxLayout				*MainLayout;
	ExamsList *				_examsList;
	ExamsData	*			_examData;
	MarksData*				_markData;
	quint32					_studentId;
	//AdmListEdt			*_admEDTList;
	QFrame					*informationsFrame;
	QVBoxLayout				*informationsLayout;
	//InfoPanel				*infos;
	QPushButton				*del;
	QPushButton				*edit;
	QPushButton				*ok;
	QPushButton				*save;
	QPushButton				*reset;
	QPushButton				*back;

private:
	QTabWidget				*_parent;
	PluginManager			*_pluginManager;
	FormAddGrade			*_formaddmark;
};

#endif // MARKSEXAMSLIST_H
