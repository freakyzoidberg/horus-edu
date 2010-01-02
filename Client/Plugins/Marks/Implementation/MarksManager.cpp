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
#include "MarksManager.h"
#include "../../../../Common/TreeData.h"
#include <QLabel>
#include "MarksMainView.h"
#include "MarksExamsList.h"

MarksManager::MarksManager(PluginManager *pm, MarksMainView *parent)
{
	_pm = pm;
	_parent = parent;

	infos = NULL;
	td = pm->findPlugin<TreeDataPlugin *>();

	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);

	_classList = new ClassList(pm);

	QLabel *infoTitle = new QLabel(tr("Informations:"));
	infoTitle->setProperty("isTitle", true);
	infoTitle->setProperty("isRound", true);
	informationsFrame = new QFrame(this);
	informationsFrame->setMinimumWidth(200);

	informationsLayout = new QVBoxLayout(informationsFrame);
	informationsLayout->setSpacing(0);
	informationsLayout->setMargin(0);
	informationsLayout->addWidget(infoTitle);
	RightLayout->addWidget(informationsFrame);
	QLabel *actionTitle = new QLabel(tr("Actions:"));
	actionTitle->setProperty("isTitle", true);
	actionTitle->setProperty("isRound", true);

	del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Delete this edt"));
	edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Edit this edt"));
	ok = new QPushButton(QIcon(":/ok.png"), tr("Ok"));
	save = new QPushButton(QIcon(":/save.png"), tr("Apply"));
	reset = new QPushButton(QIcon(":/reset.png"), tr("Reset"));
	back = new QPushButton(QIcon(":/back.png"), tr("Cancel"));
	add = new QPushButton(QIcon(":/AddTimeTable.png"), tr("Add"));

	RightLayout->addWidget(actionTitle);
	RightLayout->addWidget(edit);
	RightLayout->addWidget(del);
	RightLayout->addWidget(ok);
	RightLayout->addWidget(save);
	RightLayout->addWidget(reset);
	RightLayout->addWidget(back);
	RightLayout->addWidget(add);
	RightLayout->addWidget(new QWidget(this), 1);

	MainLayout->addWidget(_classList);

	MainLayout->addLayout(RightLayout);
	MainLayout->setStretch(0, 1);

	ok->setVisible(false);
	save->setVisible(false);
	add->setVisible(false);
	reset->setVisible(false);
	back->setVisible(false);
	edit->setVisible(false);
	del->setVisible(false);

	connect(_classList->Classlist, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(subjectSelected(QListWidgetItem *)));
	connect(_classList->Classlist, SIGNAL(itemDoubleClicked ( QListWidgetItem *)),
			this, SLOT(moveToExamList( QListWidgetItem *)));
	//connect(_add, SIGNAL(clicked()), this, SLOT(addExam()));


	this->setLayout(MainLayout);
}

void	MarksManager::moveToExamList(QListWidgetItem *item)
{
	qDebug() << item->data(Qt::UserRole).toInt();

	quint32	id = item->data(Qt::UserRole).toInt();
	TreeData *tmpsubject = td->node(id);

	qDebug() << "name:" << tmpsubject->name();

	_parent->setTabEnabled(1, 1);
	_parent->setCurrentIndex(1);
	_parent->examsList()->examsList()->Exams(tmpsubject);
	_parent->examsList()->_node = tmpsubject;
	_parent->examsList()->_add->setVisible(true);
}

void	MarksManager::subjectSelected(QListWidgetItem *item)
{
	if (infos)
		delete infos;
	quint32 subjectId = item->data(Qt::UserRole).toInt();

	infos = new InfoPanel(td->node(subjectId)->parent()->name());
	this->informationsLayout->addWidget(infos);
	infos->show();
	//add->setVisible(true);
}

void	MarksManager::addExam()
{

}
