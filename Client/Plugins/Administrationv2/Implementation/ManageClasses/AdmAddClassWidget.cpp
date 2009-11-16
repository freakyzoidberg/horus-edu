#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QHeaderView>

#include "../../../../../Common/Data.h"
#include "../../../../../Common/TreeData.h"
#include "AdmAddClassWidget.h"

AdmAddClassWidget::AdmAddClassWidget(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    _treeplugin = treeplugin;
    _userplugin = userplugin;

    _mainLayout = new QHBoxLayout(this);
    QVBoxLayout  *columnLayout;
    QWidget      *column;

	this->_table = new QTableWidget(0, 6);
    _table->setShowGrid(false);
    _table->horizontalHeader()->setStretchLastSection(true);

	QStringList header;
	header.insert(0, QString(tr("Class name")));
	header.insert(1, QString(tr("Professeur principal")));
	header.insert(2, QString(tr("Modifier")));
	header.insert(3, QString(tr("Supprimer")));
    _table->setHorizontalHeaderLabels(header);
    this->_mainLayout->addWidget(_table);

    column = new QWidget();
    columnLayout = new QVBoxLayout(column);
    _mainLayout->addWidget(column);
    this->_classNameLabel = new QLabel(tr("Nom de la classe:"));
    this->_className = new QLineEdit();
    columnLayout->addWidget(_classNameLabel);
    columnLayout->addWidget(_className);

    this->_userReferentLabel = new QLabel(tr("Professeur principal:"));
    this->_userReferent = new QComboBox();
    initUserReferent();
    columnLayout->addWidget(_userReferentLabel);
    columnLayout->addWidget(_userReferent);

    this->_save = new QPushButton(tr("Ajouter"));
    this->_cancel = new QPushButton(tr("Abandonner"));
    columnLayout->addWidget(_save);
    columnLayout->addWidget(_cancel);

    _mainLayout->setStretch(0, 1);
    columnLayout->addStretch(25);

    connect(_save, SIGNAL(clicked()), this, SLOT(addClass()));
    connect(_cancel, SIGNAL(clicked()), this, SLOT(emptyField()));
    connect(_table, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(choosenClass(QTableWidgetItem *)));
    connect(_table, SIGNAL(cellClicked(int, int)), this, SLOT(cellClicked(int, int)));
    displayClasses();
}

void    AdmAddClassWidget::displayClasses()
{
    QList<Data*> datas = _treeplugin->allDatas();

    for (int i = 0, j = 0; i < datas.size(); ++i)
    {
        TreeData    *tmp = qobject_cast<TreeData *>(datas.at(i));
        if (tmp->type() == "GROUP")
        {
            QTableWidgetItem *name = new QTableWidgetItem(tmp->name());
            name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

            _table->setRowCount(j + 1);
            this->_table->setItem(j, 0, name);
            this->_table->setItem(j, 1,
                                  new QTableWidgetItem(tmp->user()->name() == "" ?
                                                       "Non renseigne" :
                                                        tmp->user()->name() + " "
                                                        + tmp->user()->surname()));
			_table->setItem(j, 2, new QTableWidgetItem(QIcon(":/Icons/edit-desk.png"), ""));
			_table->setItem(j, 3, new QTableWidgetItem(QIcon(":/Icons/remove-desk.png"), ""));
			_table->setItem(j, 4, new QTableWidgetItem(QVariant(tmp->user()->id()).toString()));
			_table->setItem(j, 5, new QTableWidgetItem(QVariant(tmp->id()).toString()));
            j++;
        }
    }
	_table->setColumnHidden(4, true);
	_table->setColumnHidden(5, true);
}

void    AdmAddClassWidget::initUserReferent()
{
     QList<Data*> datas = _userplugin->allDatas();
     _userReferent->addItem("", 0);
     for (int i = 0; i < datas.size(); ++i)
     {
        UserData    *tmp = qobject_cast<UserData *>(datas.at(i));
        if (tmp->level() == LEVEL_TEACHER)
            this->_userReferent->addItem(tmp->name() + " " + tmp->surname(),
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

    selectedData->setName(_className->text());
    selectedData->setUser(user);
    selectedData->save();

}

void    AdmAddClassWidget::emptyField()
{
    _className->setText("");
    _userReferent->setCurrentIndex(0);
    _save->setText(tr("Ajouter"));
}

void    AdmAddClassWidget::addClassInDatabase()
{
    TreeData    *newClass = this->_treeplugin->createNode();
    int index;

    newClass->setName(this->_className->text());
    newClass->setType("GROUP");
    newClass->setParent(this->_treeplugin->node(0));
    newClass->setUser(this->_userplugin->nobody());

    _table->setRowCount(_table->rowCount() + 1);
    QTableWidgetItem *name = new QTableWidgetItem(this->_className->text());
    name->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

   index = this->_userReferent->currentIndex();
   UserData *user;
   if (_userReferent->itemData(index).toInt() != 0)
   {
        user = _userplugin->user(_userReferent->itemData(index).toInt());
        user->setStudentClass(newClass);
		_table->setItem(_table->rowCount() - 1, 1,
                        new QTableWidgetItem(user->name() + " " + user->surname()));
		_table->setItem(_table->rowCount() - 1, 4,
						new QTableWidgetItem(QVariant(user->id()).toString()));
        newClass->setUser(user);
   }
   else
   {
	   user = NULL;
	   _table->setItem(_table->rowCount() - 1, 1, new QTableWidgetItem("Non renseigne."));
	   _table->setItem(_table->rowCount() - 1, 4,
					   new QTableWidgetItem(QVariant(0).toString()));
   }

   _table->setItem(_table->rowCount() - 1, 0, name);
	_table->setItem(_table->rowCount() - 1, 3, new QTableWidgetItem(QIcon(":/Icons/remove-desk.png"), ""));
	_table->setItem(_table->rowCount() - 1, 2, new QTableWidgetItem(QIcon(":/Icons/edit-desk.png"), ""));

	newClass->create();

   //if (_userReferent->itemData(index).toInt() != 0)
   {
       save = user;
	   classSave = newClass;
	   connect(newClass, SIGNAL(created()), this, SLOT(modifUser()));
   }

   _table->showRow(_table->rowCount());
}

void    AdmAddClassWidget::modifUser()
{

	if (save && save->id() != 0)
	{
		_table->setItem(_table->rowCount() - 1, 4,
						new QTableWidgetItem(QVariant(save->id()).toString()));
		save->save();
	}

	_table->setItem(_table->rowCount() - 1, 5,
					   new QTableWidgetItem(QVariant(classSave->id()).toString()));
}

void    AdmAddClassWidget::choosenClass(QTableWidgetItem *item)
{


}

void	AdmAddClassWidget::cellClicked(int row, int col)
{
	if (col == 3)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Voulez-vous vraiment supprimer cette classe?"));
		QPushButton *connectButton = msgBox.addButton(tr("Confirmer."), QMessageBox::ActionRole);
		QPushButton *abortButton = msgBox.addButton(QMessageBox::Abort);

		msgBox.exec();

		if (msgBox.clickedButton() == connectButton)
		{
			TreeData *data = _treeplugin->node(QVariant(_table->item(row, 5)->text()).toInt());
			data->remove();
			_table->removeRow(row);
		}
		else if (msgBox.clickedButton() == abortButton)
		  return ;
	}
        else if (col == 2)
        {
                UserData *user = _userplugin->user(QVariant(_table->item(row, 4)->text()).toInt());
                TreeData *data = _treeplugin->node(QVariant(_table->item(row, 5)->text()).toInt());

                selectedData = data;

				_className->setText(data->name());
                for (int i = 0; i < _userReferent->count(); i++)
                {
                    if (_userReferent->itemData(i).toInt() == user->id())
                    {
                        _userReferent->setCurrentIndex(i);
                    }
                }
                _save->setText(tr("Editer"));
        }
}
