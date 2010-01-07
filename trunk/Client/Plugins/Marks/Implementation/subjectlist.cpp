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
 * along with Horus. If not, see <http:/Marks//www.gnu.org/licenses/>.               *
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

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "subjectlist.h"
#include "../../../../Common/TreeData.h"
#include "../../../../Common/UserData.h"
#include "../../../../Common/ExamsDataPlugin.h"
#include "../../../../Common/ExamsData.h"

SubjectList::SubjectList(PluginManager *pluginManager)
{
	_pluginManager = pluginManager;
	this->treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
	QVBoxLayout *ListLayout = new QVBoxLayout();

	ListLayout->setMargin(0);
	ListLayout->setSpacing(0);

	SubjectsList = new QListWidget(this);
	SubjectsList->setSelectionRectVisible(false);

	QLabel *title = new QLabel(tr("Selectionner une matiere pour voir, editer ou ajouter un examen."));
	title->setProperty("isTitle", true);
	ListLayout->addWidget(title);

	ListLayout->addWidget(SubjectsList);

	connect(SubjectsList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(showExams(QListWidgetItem *)));
	//connect(this->treePlugin,SIGNAL(dataUpdated(Data*)),this,SLOT(fillSubjectList()));
	this->setLayout(ListLayout);

	examComment = new QLineEdit();
	QPushButton	*addExam = new QPushButton("Ajouter un examen");

	connect(addExam, SIGNAL(clicked()), this, SLOT(addAnExam()));

	ListLayout->addWidget(examComment);
	ListLayout->addWidget(addExam);
	fillSubjectList();
}

QMap<int, QString> SubjectList::getallsubject()
{
	QMap<int, QString> allclass, exams;

	for (int i = 0; i < treePlugin->allDatas().size(); ++i)
	{
		TreeData    *data = qobject_cast<TreeData *>(treePlugin->allDatas().at(i));
		if ((data->type() == "SUBJECT") && IS_VALID_DATA_STATUS(data->status()))
			allclass.insert(data->id(), data->name());
	}


	ExamsDataPlugin *e = _pluginManager->findPlugin<ExamsDataPlugin *>();

	for (int i = 0; i < e->allDatas().size(); ++i)
	{
		ExamsData    *data = qobject_cast<ExamsData *>(e->allDatas().at(i));
		QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/Marks/desk.png"), data->comment());
		tempitem->setData(Qt::UserRole, data->teacher());
		SubjectsList->addItem(tempitem);

		allclass.insert(data->id(), data->comment());
	}

	return allclass;
}

void	SubjectList::fillSubjectList()
{
	QMapIterator<int, QString> i(getallsubject());
	SubjectsList->clear();

	while (i.hasNext())
	{
		i.next();
		QListWidgetItem *tempitem = new QListWidgetItem(QIcon(":/Marks/desk.png"), i.value());
		tempitem->setData(Qt::UserRole, i.key());
		SubjectsList->addItem(tempitem);
	}
}

void SubjectList::showExams(QListWidgetItem *item)
{
	int subj;
	TreeData *mat;

	subj = item->data(Qt::UserRole).toInt();

	ExamsDataPlugin *test = this->_pluginManager->findPlugin<ExamsDataPlugin *>();

	mat = treePlugin->node(subj);

	 ExamsData *ex =
	test->newExams(_pluginManager->currentUser()->studentClass(),
								  this->examComment->text() , _pluginManager->currentUser());

	ex->setTeacher(2);
	ex->setDate(QDate().currentDate());
	ex->setComment(this->examComment->text());
	ex->setSubject(mat);
	ex->create();

}

void SubjectList::addAnExam()
{
	qDebug() << "added";


 }

