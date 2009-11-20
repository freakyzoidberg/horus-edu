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

	_classList = new ClassList();
	_mainLayout = new QHBoxLayout(this);
	_mainLayout->setMargin(0);
	_mainLayout->setSpacing(0);
	QVBoxLayout  *columnLayout;
	//QWidget      *column;

	// QVBoxLayout *RightLayout = new QVBoxLayout();

	//StudentList = new ListSelection(treeplugin, userplugin);
	addstudent = new QPushButton(QIcon(":/Icons/add-students.png"), tr("Add a student"));
	del = new QPushButton(QIcon(":/Icons/remove-students.png"), tr("Delete class"));
	edit = new QPushButton(QIcon(":/Icons/edit-students.png"), tr("Edit this student"));
	ok = new QPushButton(QIcon(":/Icons/ok.png"), tr("Ok"));
//	save = new QPushButton(QIcon(":/Icons/save.png"), tr("Apply"));
	reset = new QPushButton(QIcon(":/Icons/reset.png"), tr("Reset"));
	back = new QPushButton(QIcon(":/Icons/back.png"), tr("Cancel"));
	back = new QPushButton(QIcon(":/Icons/back.png"), tr("Cancel"));

	_mainLayout->addWidget(_classList);

//	column = new QWidget();
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

	//_mainLayout->addWidget(column);
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

void    AdmAddClassWidget::displayClasses()
{
	QList<Data*> datas = _treeplugin->allDatas();

	for (int i = 0, j = 0; i < datas.size(); ++i)
	{
		TreeData    *tmp = qobject_cast<TreeData *>(datas.at(i));
		if (tmp->type() == "GRADE")
		{
			QListWidgetItem *item = new QListWidgetItem(QIcon(":/Icons/desk.png"), tmp->name());
			_classList->classList()->addItem(item);
			_classList->classList()->addItem(QVariant(tmp->id()).toString());
			//_classList->classList()->setRowHidden(this->_classList->classList()->count() - 1, true);
			j++;
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
			editClassInDatabase();
			_userReferent->currentText().clear();
			_className->setText("");
			_save->setText(tr("Ajouter"));
			errorMsg.setText(tr("The class was successfully edited."));
			errorMsg.exec();
		}
	}
}

void    AdmAddClassWidget::editClassInDatabase()
{
	UserData *user = _userplugin->user(_userReferent->itemData(_userReferent->currentIndex()).toInt());

	//_table->item(this->currentrow, 0)->setText(_className->text());
	//_table->item(this->currentrow, 1)->setText(this->_userReferent->currentText());
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

	//_table->setRowCount(_table->rowCount() + 1);
//	QTableWidgetItem *name = new QTableWidgetItem(this->_className->text());
//	name->setFlags(Qt::ItemIsEnabled);

	index = this->_userReferent->currentIndex();
	UserData *user;
	if (_userReferent->itemData(index).toInt() != 0)
	{
		user = _userplugin->user(_userReferent->itemData(index).toInt());
		user->setStudentClass(newClass);

	//	QTableWidgetItem *n = new QTableWidgetItem(user->name() + " " + user->surname());
	//	n->setFlags(Qt::ItemIsEnabled);
		//_table->setItem(_table->rowCount() - 1, 1, n);
		//_table->setItem(_table->rowCount() - 1, 5,
			//			new QTableWidgetItem(QVariant(user->id()).toString()));
		newClass->setUser(user);
	}
	else
	{
		user = NULL;
	//	QTableWidgetItem *n = new QTableWidgetItem(tr("Non renseigne."));
	//	n->setFlags(Qt::ItemIsEnabled);
		//_table->setItem(_table->rowCount() - 1, 1, n);
		//_table->setItem(_table->rowCount() - 1, 5,
		//				new QTableWidgetItem(QVariant(0).toString()));
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
	{
		//_table->setItem(_table->rowCount() - 1, 5,
			//				new QTableWidgetItem(QVariant(save->id()).toString()));
		save->save();
	}
	_classList->classList()->addItem(new QListWidgetItem(QIcon(":/Icons/desk.png"), classSave->name()));
	_classList->classList()->addItem(QVariant(classSave->id()).toString());
	//_classList->classList()->setRowHidden(_classList->classList()->count() - 1, true);
	//_table->setItem(_table->rowCount() - 1, 6,
		//			new QTableWidgetItem(QVariant(classSave->id()).toString()));
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
		data->remove();
		_classList->classList()->clear();
		/*_classList->classList()->removeItemWidget(_classList->classList()->item);
		_classList->classList()->removeItemWidget(_classList->classList()->item(_classList->classList()->currentRow())); */
	}
	else if (msgBox.clickedButton() == abortButton)
		return ;
}

