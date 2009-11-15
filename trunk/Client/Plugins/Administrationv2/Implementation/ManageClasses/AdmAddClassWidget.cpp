#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

#include "AdmAddClassWidget.h"

AdmAddClassWidget::AdmAddClassWidget(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin)
{
    _treeplugin = treeplugin;
    _userplugin = userplugin;

    _mainLayout = new QVBoxLayout(this);
    QHBoxLayout  *lineLayout;
    QWidget      *line;

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

}

/*  id
    nom
    userReferent == prof principal / adm
    salle referente (option)
*/
