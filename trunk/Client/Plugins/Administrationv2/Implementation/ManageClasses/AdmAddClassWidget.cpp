#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

#include "../../../../../Common/Data.h"
#include "../../../../../Common/TreeData.h"
#include "AdmAddClassWidget.h"

AdmAddClassWidget::AdmAddClassWidget(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    _treeplugin = treeplugin;
    _userplugin = userplugin;

    _mainLayout = new QVBoxLayout(this);
    QHBoxLayout  *lineLayout;
    QWidget      *line;

    this->_table = new QTableWidget(0, 2);
    QStringList header;

    header.insert(0, QString("Class name"));
    header.insert(1, QString("Professeur principal"));
    _table->setHorizontalHeaderLabels(header);
    this->_mainLayout->addWidget(_table);

    line = new QWidget();
    lineLayout = new QHBoxLayout(line);
    _mainLayout->addWidget(line);
    this->_classNameLabel = new QLabel(tr("Nom de la classe:"));
    this->_className = new QLineEdit();
    lineLayout->addWidget(_classNameLabel);
    lineLayout->addWidget(_className);

    line = new QWidget();
    _mainLayout->addWidget(line);
    lineLayout = new QHBoxLayout(line);
    this->_userReferentLabel = new QLabel(tr("Professeur principal:"));
    this->_userReferent = new QComboBox();
    initUserReferent();
    lineLayout->addWidget(_userReferentLabel);
    lineLayout->addWidget(_userReferent);

    line = new QWidget();
    _mainLayout->addWidget(line);
    lineLayout = new QHBoxLayout(line);
    this->_save = new QPushButton(tr("Enregister."));
    this->_cancel = new QPushButton(tr("Abandonner."));
    lineLayout->addWidget(_save);
    lineLayout->addWidget(_cancel);

    connect(_save, SIGNAL(clicked()), this, SLOT(addClass()));
    connect(_cancel, SIGNAL(clicked()), this, SLOT(emptyField()));

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
        addClassInDatabase();
        _userReferent->currentText().clear();
        _className->setText("");
        errorMsg.setText(tr("The class was successfully saved."));
        errorMsg.exec();
    }
}

void    AdmAddClassWidget::emptyField()
{
    _className->setText("");
    _userReferent->setCurrentIndex(0);
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
        _table->setItem(_table->rowCount()-1, 1,
                        new QTableWidgetItem(user->name() + " " + user->surname()));
        newClass->setUser(user);
   }
   else
       _table->setItem(_table->rowCount()-1, 1, new QTableWidgetItem("Non renseigne."));

   _table->setItem(_table->rowCount() -1, 0, name);
   newClass->create();

   if (_userReferent->itemData(index).toInt() != 0)
   {
       connect(newClass, SIGNAL(created()), this, SLOT(modifUser()));
       save = user;
   }

   _table->showRow(_table->rowCount());
}

void    AdmAddClassWidget::modifUser()
{
    save->save();
}
