#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

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
    this->_userReferent->setEditable(true);
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
            _table->setRowCount(j + 1);
            this->_table->setItem(j, 0, new QTableWidgetItem(tmp->name()));
            this->_table->setItem(j, 1, new QTableWidgetItem(QVariant(tmp->user()->id()).toString()));
            j++;
        }
    }
}

void    AdmAddClassWidget::initUserReferent()
{

}

void    AdmAddClassWidget::addClass()
{
    QMessageBox errorMsg;
    QString     error = "";

    if (_className->text().trimmed() == "")
        error += tr("A class without name, you cock sucker??");

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
        errorMsg.setText(tr("Ok then what?"));
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
    newClass->setName(this->_className->text());
    newClass->setType("GROUP");
    newClass->setParent(this->_treeplugin->node(0));
    newClass->setUser(this->_userplugin->nobody());
    newClass->create();
}

/*  id
    nom
    userReferent == prof principal / adm
    salle referente (option)
*/
