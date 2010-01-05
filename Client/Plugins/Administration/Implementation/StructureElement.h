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
#ifndef				__STRUCTUREELEMENT_H__
# define			__STRUCTUREELEMENT_H__

# include			<QWidget>

# include			"../../../../Common/TreeDataPlugin.h"
# include			"StructureForm.h"

class				StructureElement : public QWidget
{
	Q_OBJECT

public:
	StructureElement(QWidget *parent, TreeDataPlugin *treeDataPlugin);
	void			setForm(StructureForm *form);
	virtual void	update() = 0;

protected:
	virtual	void	addElement() = 0;
	virtual	void	editElement() = 0;
	virtual	void	removeElement() = 0;
	virtual void	validateElement() = 0;
	StructureForm	*_form;
	TreeDataPlugin	*_treeDataPlugin;

public slots:
	void			disable();
	void			enable();

private slots:
	void			add();
	void			edit();
	void			remove();
	void			validateForm();
	void			cancelForm();

signals:
	void			disabled();
	void			enabled();
};

Q_DECLARE_INTERFACE(StructureElement, "net.horus.StructureElement/1.0");

#endif //			__STRUCTUREELEMENT_H__
