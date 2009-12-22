#include		"StructureElement.h"

#include		<QMessageBox>

StructureElement::StructureElement(QWidget *parent, TreeDataPlugin *treeDataPlugin) : QWidget(parent), _treeDataPlugin(treeDataPlugin)
{
}

void			StructureElement::setForm(StructureForm *form)
{
	_form = form;
}

void			StructureElement::enable()
{
	emit enabled();
}

void			StructureElement::disable()
{
	emit disabled();
}

void			StructureElement::add()
{
	_form->show();
	addElement();
	connect(_form, SIGNAL(validated()), this, SLOT(validateForm()));
}

void			StructureElement::edit()
{
	_form->show();
	editElement();
	connect(_form, SIGNAL(validated()), this, SLOT(validateForm()));
}

void			StructureElement::remove()
{
	QMessageBox	*confirm;
	int			ret;

	confirm = new QMessageBox(QMessageBox::Question, tr("Confirmation"), tr("Do you really want to delete ?"), QMessageBox::Yes | QMessageBox::No, this);
	ret = confirm->exec();
	if (ret == QMessageBox::Yes)
		removeElement();
}

void			StructureElement::validateForm()
{
	validateElement();
	_form->hide();
	disconnect(_form, SIGNAL(validated()), this, SLOT(validateForm()));
}