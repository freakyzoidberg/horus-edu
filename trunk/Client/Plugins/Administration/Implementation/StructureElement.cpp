#include		"StructureElement.h"

#include		<QMessageBox>

StructureElement::StructureElement(QWidget *parent, TreeDataPlugin *treeDataPlugin) : QWidget(parent), _treeDataPlugin(treeDataPlugin)
{
}

void			StructureElement::setForm(StructureForm *form)
{
	_form = form;
	connect(form, SIGNAL(validated()), this, SLOT(validateForm()));
}

void			StructureElement::disable()
{
	emit disabled();
}

void			StructureElement::edit()
{
	_form->show();
	editElement();
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
}