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
#include "FormStudents.h"

#include	<QLabel>

FormStudents::FormStudents(QList<UserData*> list)
{

    QVBoxLayout *FormLayout = new QVBoxLayout(this);
    QLabel	*label;
    FormLayout->setSpacing(0);
    FormLayout->setMargin(0);

	label = new QLabel(tr("Basic informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    BaseInfos = new BasicInfos();
    FormLayout->addWidget(BaseInfos);




	//label = new QLabel(tr("Parent informations"), this);
	//label->setProperty("isFormTitle", true);
	//FormLayout->addWidget(label);
//    ParInfos = new ParentInfos();
//    ParInfos->getParent()->addItem(tr("none"), 0);
//    foreach (UserData* mud, list)
//    {
//
//        ParInfos->getParent()->addItem(mud->surname()+" "+mud->name(), mud->id());
//    }
//
//
//    FormLayout->addWidget(ParInfos);

	label = new QLabel(tr("Scholar informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    SocInfos = new SocialInfos();
    FormLayout->addWidget(SocInfos);


        //label = new QLabel(tr("Scholar informations"), this);
//	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    SchoInfos = new SchoolInfos();
    FormLayout->addWidget(SchoInfos);

	//label = new QLabel(tr("Follow up"), this);
	//label->setProperty("isFormTitle", true);
	//FormLayout->addWidget(label);
    SuiInfos = new SuiviInfos();
    FormLayout->addWidget(SuiInfos);

    ParInfos = new EditParent(0, 0);
     FormLayout->addWidget(ParInfos);

    this->setLayout(FormLayout);

    id = 0;


}

FormStudents::FormStudents(QList<UserData*> list, QList<UserData*> parentlist,UserData *d)
{
	QLabel	*label;

    QVBoxLayout *FormLayout = new QVBoxLayout(this);
    FormLayout->setSpacing(0);
    FormLayout->setMargin(0);
    id = d->id();


    qDebug() << d;
	label = new QLabel(tr("Basic informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    BaseInfos = new BasicInfos(d);
    FormLayout->addWidget(BaseInfos);
//    ParInfos = new ParentInfos(d);
//    ParInfos->getParent()->addItem(tr("none"), 0);
//    foreach (UserData* mud, list)
//    {
//        ParInfos->getParent()->addItem(mud->surname()+" "+mud->name(), mud->id());
//    }
//
//
//if (parentlist.count() > 0)
//    ParInfos->getParent()->setCurrentIndex(ParInfos->getParent()->findData(parentlist.first()->id(), Qt::UserRole, Qt::MatchCaseSensitive));
//    FormLayout->addWidget(ParInfos);

	label = new QLabel(tr("Social informations"), this);
	label->setProperty("isFormTitle", true);
	FormLayout->addWidget(label);
    SocInfos = new SocialInfos(d);
    FormLayout->addWidget(SocInfos);


        //label = new QLabel(tr("Scholar informations"), this);
        //label->setProperty("isFormTitle", true);
        //FormLayout->addWidget(label);
    SchoInfos = new SchoolInfos(d);
    FormLayout->addWidget(SchoInfos);

    SuiInfos = new SuiviInfos(d);
    FormLayout->addWidget(SuiInfos);


    if (parentlist.size() > 1)
    {
        if (parentlist[0]->gender() == GENDER_MALE)
            ParInfos = new EditParent(parentlist[0], parentlist[1]);
        else
            ParInfos = new EditParent(parentlist[1], parentlist[0]);
    }
    else if (parentlist.size() > 0)
    {
        if (parentlist[0]->gender() == GENDER_MALE)
            ParInfos = new EditParent(parentlist[0], 0);
        else
           ParInfos = new EditParent(0, parentlist[0]);
    }
    else
        ParInfos = new EditParent(0, 0);

    FormLayout->addWidget(ParInfos);

    this->setLayout(FormLayout);
}
