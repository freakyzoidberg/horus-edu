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
#ifndef						__MANAGESTRUCTURE_H__
# define					__MANAGESTRUCTURE_H__

# include					<QWidget>

# include					<QBoxLayout>
# include					<QPushButton>

# include					"../../../../Common/TreeDataPlugin.h"
# include					"../../../../Common/UserDataPlugin.h"
# include					"StructureElement.h"
# include					"InformationsStructure.h"

class						ManageStructure : public QWidget
{
	Q_OBJECT

public:
	ManageStructure(QWidget *parent, TreeDataPlugin *treeDataPlugin, UserDataPlugin *userDataPlugin);

private slots:
	void					schoolEnabled();
	void					schoolDisabled();
	void					classEnabled();
	void					classDisabled();
	void					subjectEnabled();
	void					subjectDisabled();

private:
	UserDataPlugin			*_userDataPlugin;
	StructureElement		*school;
	StructureElement		*classes;
	StructureElement		*subjects;
	QBoxLayout				*leftLayout;
	QBoxLayout				*informationsLayout;
	InformationsStructure	*informations;
	QPushButton				*addSchoolButton;
	QPushButton				*editSchoolButton;
	QPushButton				*addClassButton;
	QPushButton				*editClassButton;
	QPushButton				*removeClassButton;
	QPushButton				*addSubjectButton;
	QPushButton				*editSubjectButton;
	QPushButton				*removeSubjectButton;
};

#endif //					__MANAGESTRUCTURE_H__
