#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QHeaderView>
#include <QListWidget>
#include <iostream>

#include "../../../../../Common/Data.h"
#include "../../../../../Common/TreeData.h"
#include "AdmAddClassWidget.h"

AdmAddClassWidget::AdmAddClassWidget(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
	_treeplugin = treeplugin;
	_userplugin = userplugin;

	_classList = new ClassListClass;
	_mainLayout = new QHBoxLayout(this);
	_mainLayout->setMargin(0);
	_mainLayout->setSpacing(0);
	QVBoxLayout  *columnLayout;

	_mainLayout->addWidget(_classList);
	columnLayout = new QVBoxLayout();
	_mainLayout->addLayout(columnLayout);
	columnLayout->setSpacing(0);
	columnLayout->setMargin(0);

	infoTitle = new QLabel(tr("Informations"));
	infoTitle->setProperty("isTitle", true);
	infoTitle->setProperty("isRound", true);
	columnLayout->addWidget(infoTitle);

	actions = new QLabel(tr("Actions"));
	actions->setProperty("isTitle", true);
	actions->setProperty("isRound", true);
	columnLayout->addWidget(actions);

	this->_classNameLabel = new QLabel(tr("Nom de la classe:"));
	this->_className = new QLineEdit();
	columnLayout->addWidget(_classNameLabel);
	columnLayout->addWidget(_className);

	this->_userReferentLabel = new QLabel(tr("Professeur principal:"));
	this->_userReferent = new QComboBox();
	initUserReferent();

	columnLayout->addWidget(_userReferentLabel);
	columnLayout->addWidget(_userReferent);

	this->_save = new QPushButton(QIcon(":/Icons/save.png"), tr("Ajouter"));
	this->_cancel = new QPushButton(QIcon(":/Icons/reset.png"), tr("Abandonner"));
	del = new QPushButton(QIcon(":/Icons/remove-desk.png"), tr("Supprimer"));
	columnLayout->addWidget(_save);
	columnLayout->addWidget(_cancel);
	columnLayout->addWidget(del);

	del->hide();

	_mainLayout->setStretch(0, 1);
	columnLayout->addStretch(1);

	connect(_save, SIGNAL(clicked()), this, SLOT(addClass()));
	connect(_cancel, SIGNAL(clicked()), this, SLOT(emptyField()));
	connect(this->_classList->classList(), SIGNAL(itemClicked( QListWidgetItem * )),
			this, SLOT(choosenClass(QListWidgetItem *)));
	connect(del, SIGNAL(clicked()), this, SLOT(deleteClass()));
	displayClasses();
}

void    AdmAddClassWidget::displayClasses(int id)
{
	QList<Data*> datas = _treeplugin->allDatas();

	for (int i = 0, j = 0; i < datas.size(); ++i)
	{
		TreeData    *tmp = qobject_cast<TreeData *>(datas.at(i));
		if (tmp->type() == "GRADE")
		{
			if (id == -1 || id != tmp->id())
			{
				QListWidgetItem *item = new QListWidgetItem(QIcon(":/Icons/desk.png"), tmp->name());
				_classList->classList()->addItem(item);
				_classList->classList()->addItem(QVariant(tmp->id()).toString());
				//_classList->classList()->setRowHidden(this->_classList->classList()->count() - 1, true);
				j++;
			}
		}
	}

}

void    AdmAddClassWidget::initUserReferent()
{
	QList<Data*> datas = _userplugin->allDatas();
	_userReferent->addItem("", 0);
	for (int i = 0; i < datas.size(); ++i)
	{
		UserData    *tmp = qobject_cast<UserData *>(datas.at(i));
		if (tmp->level() == LEVEL_TEACHER)
			this->_userReferent->addItem(QIcon(":/Icons/teachers.png"), tmp->name() + " " + tmp->surname(),
										 QVariant(tmp->id()));
	}
}

void    AdmAddClassWidget::addClass()
{
	QMessageBox errorMsg;
	QString     error = "";

	if (_className->text().trimmed() == "")
		error += tr("This class must have a name.");
	if (error != "")
	{
		errorMsg.setText(error);
		errorMsg.exec();
	}
	else
	{
		if (_save->text() == tr("Ajouter"))
		{
			addClassInDatabase();
			_userReferent->currentText().clear();
			_className->setText("");
			errorMsg.setText(tr("The class was successfully added."));
			errorMsg.exec();
		}
		else
		{
			errorMsg.setText("Sorry the edition is not available for now.");
			errorMsg.exec();
		/*	editClassInDatabase();
			_userReferent->currentText().clear();
			_className->setText("");
			_save->setText(tr("Ajouter"));
			errorMsg.setText(tr("The class was successfully edited."));
			errorMsg.exec(); */
		}
	}
}

void    AdmAddClassWidget::editClassInDatabase()
{
	UserData *user = _userplugin->user(_userReferent->itemData(_userReferent->currentIndex()).toInt());
	selectedData->setName(_className->text());
	selectedData->setUser(user);
	selectedData->save();
}

void    AdmAddClassWidget::emptyField()
{
	_className->setText("");
	_userReferent->setCurrentIndex(0);
	del->hide();
	_save->setText(tr("Ajouter"));
}

void    AdmAddClassWidget::addClassInDatabase()
{
	TreeData    *newClass = this->_treeplugin->createNode();
	int index;

	newClass->setName(this->_className->text());
	newClass->setType("GRADE");
	newClass->setParent(this->_treeplugin->node(0));
	newClass->setUser(this->_userplugin->nobody());

	index = this->_userReferent->currentIndex();
	UserData *user;
	if (_userReferent->itemData(index).toInt() != 0)
	{
		user = _userplugin->user(_userReferent->itemData(index).toInt());
		user->setStudentClass(newClass);
		newClass->setUser(user);
	}
	else
	{
		user = NULL;
	//	QTableWidgetItem *n = new QTableWidgetItem(tr("Non renseigne."));
	//	n->setFlags(Qt::ItemIsEnabled);
	//_table->setItem(_table->rowCount() - 1, 1, n);
	//_table->setItem(_table->rowCount() - 1, 5,
	//new QTableWidgetItem(QVariant(0).toString()));
	}

	//_table->setItem(_table->rowCount() - 1, 0, name);

	// QTableWidgetItem *edit = new QTableWidgetItem(QIcon(":/Icons/remove-desk.png"), "");
	// edit->setFlags(Qt::ItemIsEnabled);
	//_table->setItem(_table->rowCount() - 1, 3, edit);

	// QTableWidgetItem *del = new QTableWidgetItem(QIcon(":/Icons/edit-desk.png"), "");
	// del->setFlags(Qt::ItemIsEnabled);
	//_table->setItem(_table->rowCount() - 1, 2, del);
	newClass->create();

	save = user;
	classSave = newClass;
	connect(newClass, SIGNAL(created()), this, SLOT(modifUser()));

	//_table->showRow(_table->rowCount());
}

void    AdmAddClassWidget::modifUser()
{
	if (save && save->id() != 0)
		save->save();
	_classList->classList()->addItem(new QListWidgetItem(QIcon(":/Icons/desk.png"), classSave->name()));
	_classList->classList()->addItem(QVariant(classSave->id()).toString());
	disconnect(classSave, SIGNAL(created()), this, SLOT(modifUser()));
}

void    AdmAddClassWidget::choosenClass(QListWidgetItem *item)
{
	this->_className->setText(_classList->classList()->item(this->_classList->classList()->currentRow())->text());
	_save->setText(tr("Editer"));
	del->show();
}

void	AdmAddClassWidget::deleteClass()
{
	QMessageBox msgBox;

	msgBox.setText(tr("Voulez-vous vraiment supprimer cette classe?"));

	QPushButton *connectButton = msgBox.addButton(tr("Confirmer."), QMessageBox::ActionRole);
	QPushButton *abortButton = msgBox.addButton(QMessageBox::Abort);

	msgBox.exec();

	if (msgBox.clickedButton() == connectButton)
	{
		int	id;
		id = _classList->classList()->item(_classList->classList()->currentRow() + 1)->text().toInt();
		TreeData *data = _treeplugin->node(id);
		connect(this->_treeplugin, SIGNAL(dataRemoved(Data *)), this, SLOT(refreshList(Data *)));
		del->hide();
		data->remove();
	}
	else if (msgBox.clickedButton() == abortButton)
		return ;
}

void	AdmAddClassWidget::refreshList(Data *data)
{
	TreeData	*tmp = qobject_cast<TreeData *>(data);
	disconnect(this->_treeplugin, SIGNAL(dataRemoved(Data *)), this, SLOT(refreshList(Data *)));
	_classList->classList()->clear();
	displayClasses(tmp->id());
}

