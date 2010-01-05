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
	connect(_form, SIGNAL(canceled()), this, SLOT(cancelForm()));
}

void			StructureElement::edit()
{
	_form->show();
	editElement();
	connect(_form, SIGNAL(validated()), this, SLOT(validateForm()));
	connect(_form, SIGNAL(canceled()), this, SLOT(cancelForm()));
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
	disconnect(_form, SIGNAL(canceled()), this, SLOT(cancelForm()));
}

void			StructureElement::cancelForm()
{
	disconnect(_form, SIGNAL(validated()), this, SLOT(validateForm()));
	disconnect(_form, SIGNAL(canceled()), this, SLOT(cancelForm()));
}