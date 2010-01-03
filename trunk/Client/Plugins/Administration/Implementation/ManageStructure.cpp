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
#include				"ManageStructure.h"

#include				<QFrame>
#include				<QLabel>

#include				"ElementSchool.h"
#include				"ElementClass.h"
#include				"ElementSubject.h"
#include				"StructureForm.h"

ManageStructure::ManageStructure(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin) : QWidget(parent), _userDataPlugin(userDataPlugin)
{
	QBoxLayout			*mainLayout;
	QBoxLayout			*panelLayout;
	QFrame				*informationsFrame;
	QLabel				*informationsTitle;
	QLabel				*actionsTitle;
	StructureForm		*form;

	addSchoolButton = new QPushButton(QIcon(":/Icons/add-school.png"), tr("Add a school"), this);
	editSchoolButton = new QPushButton(QIcon(":/Icons/edit-school.png"), tr("Edit a school"), this);
	removeSchoolButton = new QPushButton(QIcon(":/Icons/remove-school.png"), tr("Delete a school"), this);
	addClassButton = new QPushButton(QIcon(":/Icons/add-desk.png"), tr("Add a class"), this);
	editClassButton = new QPushButton(QIcon(":/Icons/edit-desk.png"), tr("Edit a class"), this);
	removeClassButton = new QPushButton(QIcon(":/Icons/remove-desk.png"), tr("Delete a class"), this);
	addSubjectButton = new QPushButton(QIcon(":/Icons/add-subject.png"), tr("Add a subject"), this);
	editSubjectButton = new QPushButton(QIcon(":/Icons/edit-subject.png"), tr("Edit a subject"), this);
	removeSubjectButton = new QPushButton(QIcon(":/Icons/remove-subject.png"), tr("Delete a subject"), this);
	addSchoolButton->setDisabled(true);
	addClassButton->setDisabled(true);
	addSubjectButton->setDisabled(true);
	editSchoolButton->setDisabled(true);
	editClassButton->setDisabled(true);
	editSubjectButton->setDisabled(true);
	removeSchoolButton->setDisabled(true);
	removeClassButton->setDisabled(true);
	removeSubjectButton->setDisabled(true);
	mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
	mainLayout->setMargin(0);
	mainLayout->setSpacing(0);
	leftLayout = new QBoxLayout(QBoxLayout::BottomToTop);
	leftLayout->setMargin(0);
	leftLayout->setSpacing(0);
	mainLayout->addLayout(leftLayout, 1);
	form = new StructureForm(this, userDataPlugin);
	leftLayout->addWidget(form);
	form->hide();
	leftLayout->addWidget(new QWidget(this), 1);
	subjects = new ElementSubject(this, treeDataPlugin);
	connect(subjects, SIGNAL(enabled()), this, SLOT(subjectEnabled()));
	connect(subjects, SIGNAL(disabled()), this, SLOT(subjectDisabled()));
	subjects->update();
	subjects->setForm(form);
	leftLayout->addWidget(subjects);
	subjects->hide();
	classes = new ElementClass(this, treeDataPlugin);
	connect(classes, SIGNAL(enabled()), this, SLOT(classEnabled()));
	connect(classes, SIGNAL(disabled()), this, SLOT(classDisabled()));
	classes->update();
	classes->setForm(form);
	leftLayout->addWidget(classes);
	school = new ElementSchool(this, treeDataPlugin, userDataPlugin);
	connect(school, SIGNAL(enabled()), this, SLOT(schoolEnabled()));
	connect(school, SIGNAL(disabled()), this, SLOT(schoolDisabled()));
	school->update();
	school->setForm(form);
	leftLayout->addWidget(school);
	panelLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	mainLayout->addLayout(panelLayout);
        panelLayout->setMargin(0);
        panelLayout->setSpacing(2);
	informationsFrame = new QFrame(this);
	informationsLayout = new QBoxLayout(QBoxLayout::TopToBottom, informationsFrame);
        informationsLayout->setSpacing(0);
        informationsLayout->setMargin(0);
	informationsFrame->setMinimumWidth(200);
	informationsTitle = new QLabel(tr("Informations:"), informationsFrame);
        informationsTitle->setProperty("isTitle", true);
        informationsTitle->setProperty("isRound", true);
	informationsLayout->addWidget(informationsTitle);
	informations = new InformationsStructure(this, userDataPlugin);
	informationsLayout->addWidget(informations);
	panelLayout->addWidget(informationsFrame);
	actionsTitle = new QLabel(tr("Actions:"), this);
    actionsTitle->setProperty("isTitle", true);
    actionsTitle->setProperty("isRound", true);
	panelLayout->addWidget(actionsTitle);
	panelLayout->addWidget(addSchoolButton);
	panelLayout->addWidget(editSchoolButton);
	panelLayout->addWidget(removeSchoolButton);
	panelLayout->addWidget(addClassButton);
	panelLayout->addWidget(editClassButton);
	panelLayout->addWidget(removeClassButton);
	panelLayout->addWidget(addSubjectButton);
	panelLayout->addWidget(editSubjectButton);
	panelLayout->addWidget(removeSubjectButton);
	panelLayout->addWidget(new QWidget(this), 1);
	connect(addSchoolButton, SIGNAL(clicked()), school, SLOT(add()));
	connect(editSchoolButton, SIGNAL(clicked()), school, SLOT(edit()));
	connect(removeSchoolButton, SIGNAL(clicked()), school, SLOT(remove()));
	connect(addClassButton, SIGNAL(clicked()), classes, SLOT(add()));
	connect(editClassButton, SIGNAL(clicked()), classes, SLOT(edit()));
	connect(removeClassButton, SIGNAL(clicked()), classes, SLOT(remove()));
	connect(addSubjectButton, SIGNAL(clicked()), subjects, SLOT(add()));
	connect(editSubjectButton, SIGNAL(clicked()), subjects, SLOT(edit()));
	connect(removeSubjectButton, SIGNAL(clicked()), subjects, SLOT(remove()));
	connect(qobject_cast<ElementClass *>(classes)->classListView, SIGNAL(activated(const QModelIndex &)), classes, SLOT(edit()));
	connect(qobject_cast<ElementSubject *>(subjects)->subjectListView, SIGNAL(activated(const QModelIndex &)), subjects, SLOT(edit()));
}

void					ManageStructure::schoolEnabled()
{
	addSchoolButton->setDisabled(true);
	editSchoolButton->setDisabled(false);
	removeSchoolButton->setDisabled(false);
	addClassButton->setDisabled(false);
	classes->show();
}

void					ManageStructure::schoolDisabled()
{
	addSchoolButton->setDisabled(false);
	editSchoolButton->setDisabled(true);
	removeSchoolButton->setDisabled(true);
	addClassButton->setDisabled(true);
	classes->hide();
}

void					ManageStructure::classEnabled()
{
	editClassButton->setDisabled(false);
	removeClassButton->setDisabled(false);
	addSubjectButton->setDisabled(false);
	subjects->disable();
	subjects->show();
	qobject_cast<ElementSubject *>(subjects)->setClass(static_cast<TreeData *>(qobject_cast<ElementClass *>(classes)->classesFilter->mapToSource(qobject_cast<ElementClass *>(classes)->classListView->selectionModel()->currentIndex()).internalPointer()));
	informationsLayout->removeWidget(informations);
	delete informations;
	informations = new InformationsStructure(this, _userDataPlugin, static_cast<TreeData *>(qobject_cast<ElementClass *>(classes)->classesFilter->mapToSource(qobject_cast<ElementClass *>(classes)->classListView->selectionModel()->currentIndex()).internalPointer()));
	informationsLayout->addWidget(informations);
}

void					ManageStructure::classDisabled()
{
	editClassButton->setDisabled(true);
	removeClassButton->setDisabled(true);
	addSubjectButton->setDisabled(true);
	subjects->disable();
	subjects->hide();
	informationsLayout->removeWidget(informations);
	delete informations;
	informations = new InformationsStructure(this, _userDataPlugin);
	informationsLayout->addWidget(informations);
}

void					ManageStructure::subjectEnabled()
{
	editSubjectButton->setDisabled(false);
	removeSubjectButton->setDisabled(false);
}

void					ManageStructure::subjectDisabled()
{
	editSubjectButton->setDisabled(true);
	removeSubjectButton->setDisabled(true);
}
