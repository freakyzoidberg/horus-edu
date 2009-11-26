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
#include	"AdminMainFrame.h"

#include	"AdminTree.h"
#include	"UserPage.h"
#include	"RoomPage.h"
#include	"AbsenceFrame.h"
#include	"NoteFrame.h"
#include	"BulletinFrame.h"

AdminMainFrame::AdminMainFrame(TreeDataPlugin *tree, UserDataPlugin *user, EventDataPlugin *event) : QTabWidget()
{
	this->addTab(new UserPage(tree, user), QIcon(":/images/User Group.png"), tr("Users"));
	this->addTab(new RoomPage(tree), QIcon(":/images/Clipboard.png"), tr("Manage Files"));
	this->addTab(new AbsenceFrame(tree, user, event), QIcon(":/images/pasla.png"), tr(" Absences "));
	this->addTab(new NoteFrame(tree, user, event), QIcon(":/images/notes.png"), tr(" Notes "));
	this->addTab(new BulletinFrame(tree, user, event), QIcon(":/images/bull.png"), tr(" Bulletins "));
}
