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

#include "MarksExamsList.h"

MarksExamsList::MarksExamsList(PluginManager *pluginManager, QTabWidget *mainView)
{
	_parent = mainView;
	_markData = NULL;
	_pluginManager = pluginManager;
	_infosLabel = new QLabel();
	_formaddmark = NULL;

	td = pluginManager->findPlugin<TreeDataPlugin *>();

	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);
	_sList = new StudentsList(_node, pluginManager, RightLayout);
	_examsList = new ExamsList(pluginManager, RightLayout);
	_formAdd = new NewExams(RightLayout);

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
	RightLayout->addWidget(_infosLabel);
	QLabel *actionTitle = new QLabel(tr("Actions:"));
	actionTitle->setProperty("isTitle", true);
	actionTitle->setProperty("isRound", true);

	del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Supprimer la note"));
	edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Voir les etudiants."));
	ok = new QPushButton(QIcon(":/ok.png"), tr("Ok"));
	save = new QPushButton(QIcon(":/save.png"), tr("Enregistrer"));
	reset = new QPushButton(QIcon(":/reset.png"), tr("Reset"));
	back = new QPushButton(QIcon(":/back.png"), tr("Annuler"));
	_add = new QPushButton(QIcon(":/AddTimeTable.png"), tr("Ajouter un examen"));

	RightLayout->addWidget(actionTitle);
	RightLayout->addWidget(edit);
	RightLayout->addWidget(del);
	RightLayout->addWidget(ok);
	RightLayout->addWidget(save);
	RightLayout->addWidget(reset);
	RightLayout->addWidget(back);
	RightLayout->addWidget(_add);
	RightLayout->addWidget(new QWidget(), 1);

	MainLayout->addWidget(_examsList);
	MainLayout->addWidget(new QWidget());
	MainLayout->addLayout(RightLayout);
	MainLayout->setStretch(0, 1);

	ok->setVisible(false);
	save->setVisible(false);
	_add->setVisible(false);
	_formAdd->setVisible(false);
	reset->setVisible(false);
	back->setVisible(false);
	edit->setVisible(false);
	del->setVisible(false);

	connect(_add, SIGNAL(clicked()), this, SLOT(addExam()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
	connect(back, SIGNAL(clicked()), this, SLOT(fallback()));

	connect(_examsList->_examsList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(examSelected(QListWidgetItem *)));
	connect(_examsList->_examsList, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
			this, SLOT(viewStudentList(QListWidgetItem *)));
	connect(_sList->_sList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(studentSelection(QListWidgetItem *)));
	connect(del, SIGNAL(clicked()), this, SLOT(removeMark()));
	connect(edit, SIGNAL(clicked()), this, SLOT(seeStudents()));

	this->setLayout(MainLayout);
}

void MarksExamsList::addExam()
{
	this->MainLayout->removeWidget(_examsList);
	this->MainLayout->removeWidget(this->_sList);
	_examsList->setVisible(false);
	_sList->hide();
	this->MainLayout->insertWidget(0, _formAdd);
	_formAdd->show();
	edit->setVisible(false);
	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name());
	back->setVisible(true);
	save->setVisible(true);
	_add->setVisible(false);
	del->setVisible(false);
	MainLayout->setStretch(0, 1);
	if (_formaddmark)
	{
		disconnect(save, SIGNAL(clicked()), this, SLOT(saveMark()));
		connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}
}

void	MarksExamsList::saveExam()
{

	ExamsDataPlugin	*examsPlugin = this->_pluginManager->findPlugin<ExamsDataPlugin *>();
	ExamsData *data = examsPlugin->newExams(_examsList->_node,
											this->_formAdd->examComment->text(),
											_pluginManager->currentUser());
	data->setDate(_formAdd->thedate->date());
	_newData = data;
	data->create();
	connect(data, SIGNAL(updated()), this, SLOT(refresh()));
	edit->setVisible(false);
	this->MainLayout->removeWidget(_formAdd);
	_formAdd->setVisible(false);
	this->MainLayout->insertWidget(0, _examsList);
	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name());
	_examsList->show();
	back->setVisible(false);
	save->setVisible(false);
	_add->setVisible(true);
	del->setVisible(false);
	MainLayout->setStretch(0, 1);
	_examsList->Exams(_examsList->_node);
	if (_formaddmark)
	{
		disconnect(save, SIGNAL(clicked()), this, SLOT(saveMark()));
		connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}
}

void	MarksExamsList::fallback()
{
	edit->setVisible(false);
	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name());
	this->MainLayout->removeWidget(_formAdd);;
	_formAdd->setVisible(false);
	this->MainLayout->insertWidget(0, _examsList);
	_examsList->show();
	this->MainLayout->removeWidget(_sList);
	_sList->hide();
	back->setVisible(false);
	save->setVisible(false);
	_add->setVisible(true);
	del->setVisible(false);
	MainLayout->setStretch(0, 1);
	if (_formaddmark)
	{
		disconnect(save, SIGNAL(clicked()), this, SLOT(saveMark()));
		connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}
}

void MarksExamsList::viewStudentList(QListWidgetItem *item)
{
	edit->setVisible(false);
	quint32 exId = item->data(Qt::UserRole).toInt();
	ExamsDataPlugin	*examsPlugin = this->_pluginManager->findPlugin<ExamsDataPlugin *>();
	ExamsData *tmp = examsPlugin->exam(exId);
	_examData = tmp;
	_infosLabel->setText("Subject: " + _node->name() + "\nCLass: " + _node->parent()->name()
						 + "\nExamination: " + tmp->comment());
	this->MainLayout->removeWidget(_examsList);
	_examsList->setVisible(false);
	this->MainLayout->insertWidget(0, _sList);
	_sList->setNode(_node);
	_sList->setItem(item);
	_sList->fillStudentList();
	_sList->show();
	_add->setVisible(false);
	back->setVisible(true);
	del->setVisible(false);
	MainLayout->setStretch(0, 1);
	if (_formaddmark)
	{
		disconnect(save, SIGNAL(clicked()), this, SLOT(saveMark()));
		connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
		this->MainLayout->removeWidget(_formaddmark);
		delete _formaddmark;
		_formaddmark = NULL;
		MainLayout->setStretch(0, 1);
	}
}

void	MarksExamsList::studentSelection(QListWidgetItem *item)
{
	edit->setVisible(false);
	_markData = NULL;
	del->setVisible(false);
	if (!_formaddmark)
	{
		this->MainLayout->insertWidget(1, _formaddmark = new FormAddGrade());
		disconnect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
		connect(save, SIGNAL(clicked()), this, SLOT(saveMark()));
		save->show();
	}
	_studentId = item->data(Qt::UserRole).toInt();
	_formaddmark->markEdit()->setText("");
	_formaddmark->commentEdit()->setText("");
	MarksDataPlugin	*ep = _pluginManager->findPlugin<MarksDataPlugin *>();

	for (int i = 0; i < ep->allDatas().size(); ++i)
	{
		MarksData	*tmp = qobject_cast<MarksData *>(ep->allDatas().at(i));
		if ((tmp->student() == _studentId)
			&& (_examData->id() == tmp->exam()->id()))
			{
			_markData = tmp;
			_formaddmark->commentEdit()->setText(tmp->comment());
			_formaddmark->markEdit()->setText(tmp->result());
			del->setVisible(true);
			qDebug() << "tmp->comment()" << tmp->comment()
					<< "\ttmp->result():" << tmp->result()
					<< "\ttmp->id():" << tmp->id();
			break ;
		}
	}
}

void	MarksExamsList::saveMark()
{
	edit->setVisible(false);
	if (!_markData)
	{
		UserDataPlugin	*up	  = _pluginManager->findPlugin<UserDataPlugin *>();
		UserData		*user = up->user(this->_studentId);
		MarksDataPlugin	*ep	  = _pluginManager->findPlugin<MarksDataPlugin *>();
		MarksData *newMarksData = ep->newMarks(_examData, user);
		newMarksData->setResult(_formaddmark->markEdit()->text());
		newMarksData->setComment(_formaddmark->commentEdit()->toPlainText());
		newMarksData->create();
	}
	else
	{
		_markData->setResult(_formaddmark->markEdit()->text());
		_markData->setComment(_formaddmark->commentEdit()->toPlainText());
		_markData->save();
	}
	del->setVisible(false);
	_markData = NULL;
	fallback();
}

void	MarksExamsList::removeMark()
{
	if (!_markData)
		return ;
	_markData->remove();
	_markData = NULL;
	fallback();
}

void	MarksExamsList::examSelected(QListWidgetItem *item)
{
	edit->show();
	_item = item;
}

void	MarksExamsList::seeStudents()
{
	edit->setVisible(false);
	viewStudentList(_item);
}

void	MarksExamsList::refresh()
{
	QListWidgetItem *temp = new QListWidgetItem(QIcon(":/desk.png"),
												this->_formAdd->examComment->text());
	temp->setData(Qt::UserRole, _newData->id());
	this->examsList()->_examsList->addItem(temp);
	disconnect(_newData, SIGNAL(updated()), this, SLOT(refresh()));
}
