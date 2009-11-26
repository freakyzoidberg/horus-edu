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
#ifndef MANAGESTUDENTS_H
#define MANAGESTUDENTS_H
#include <QWidget>
#include <QHBoxLayout>

#include <QPushButton>

#include "FormStudents.h"
#include "ListSelection.h"
#include "Infopanel.h"
#include "Scrollformstudent.h"
#include "../../../../../Common/TreeData.h"
#include "../../../../../Common/UserData.h"
#include "../../../../../Common/DataPlugin.h"
class ManageStudents : public QWidget
{
    Q_OBJECT

public:
    ManageStudents(TreeDataPlugin *treeplugin, UserDataPlugin *userplugin);



private:
    QHBoxLayout *MainLayout;

    QPushButton *addstudent;
    QPushButton *editstudent;
    QPushButton *back;
    QPushButton *edit;
    QPushButton *save;
    QPushButton *del;
    QPushButton *ok;
    QPushButton *reset;
    QPushButton *refresh;
    QFrame* sidebar;
    QScrollArea *scrollArea;
QFrame *informationsFrame;
QVBoxLayout *informationsLayout;
    QList<UserData*> getAllParents();
    FormStudents *StudentForm;
    ScrollFormStudent *scrollStudentForm;
    ListSelection *StudentList;
    InfoPanel *info;
    UserDataPlugin* UD;
    TreeDataPlugin* TD;
    UserData* newUSer;
    UserData* newPapa;
	UserData* newMomy;
private slots:
    void goadd();
    void goedit();
    void goback();
    void gook();
    void goreset();
    void gosave();
    void godel();
    void seteditfalse();
    void setedittrue();
    void userCreated();
    void refreshall();
    void checkedit();
};

#endif // MANAGESTUDENTS_H
