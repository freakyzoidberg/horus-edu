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
#ifndef			__LESSONMANAGERMODULE_H__
# define		__LESSONMANAGERMODULE_H__

# include		<QObject>
# include		<QXmlStreamWriter>
# include		<QList>
# include		<QWidget>

# include		"../../../../Common/Plugin.h"
# include		"../../../../Common/FileDataPlugin.h"
# include		"../../../../Common/FileData.h"

# include               "../ILessonManager.h"
# include               "../LessonModel.h"

//! LessonManager plugin
/*!

*/
class			LessonManager : public Plugin, public ILessonManager
{
//! The Q_OBJECT and Q_INTERFACES macros
/*! This two macros must be called to compile the plugin properly.
 * The second one take the name of the interface ICLientPlugin
 * in parameters.
 */
Q_OBJECT
Q_INTERFACES(Plugin)
Q_INTERFACES(ILessonManager);

public:
        bool canLoad() const;
        void load();
        void unload();

public:
	const QString	pluginName() const ;
	const QString	pluginVersion() const ;

public:
        LessonModel     *getLessonModel();

private:
        LessonModel     *lessonModel;
};

#endif // __LESSONMANAGERTESTMODULE_H__
