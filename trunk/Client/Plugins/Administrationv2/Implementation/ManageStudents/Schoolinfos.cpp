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
#include "Schoolinfos.h"

SchoolInfos::SchoolInfos()
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);


    nb_redoublement = new QSpinBox();
    nb_redoublement->setMaximumWidth(100);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    QLabel* label = new QLabel(tr("Redoublement"));
    label->setProperty("isFormLabel", true);

    label->setMaximumWidth(150);
    label->setMinimumWidth(150);
    BasicLayout->addWidget(label, 0, 0,Qt::AlignLeft);
    BasicLayout->addWidget(nb_redoublement, 0, 1);

    annee_entree = new QSpinBox();
    annee_entree->setMinimum(1980);

    annee_entree->setMaximum(3000);
    annee_entree->setValue(2009);
    annee_entree->setMaximumWidth(100);
    label->setMinimumWidth(150);
            label = new QLabel(tr("Entry year"));
            label->setProperty("isFormLabel", true);
            label->setMaximumWidth(150);
            label->setMinimumWidth(150);
            BasicLayout->addWidget(label, 1, 0, Qt::AlignLeft);
            BasicLayout->addWidget(annee_entree, 1, 1);


            annee_quitte = new QSpinBox();
            annee_quitte->setMinimum(1980);
            annee_quitte->setMaximum(2080);
            annee_quitte->setValue(2009);
            label = new QLabel(tr("Annee quitte"));
            label->setMaximumWidth(150);
            label->setMinimumWidth(150);
            label->setProperty("isFormLabel", true);
            BasicLayout->addWidget(label, 1, 2);
            BasicLayout->addWidget(annee_quitte, 1, 3);









            BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}



SchoolInfos::SchoolInfos(UserData *d)
{
    setProperty("isFormFrame", true);
    QGridLayout *BasicLayout = new QGridLayout(this);
    BasicLayout->setMargin(8);
    BasicLayout->setSpacing(4);

    nb_redoublement = new QSpinBox();
    nb_redoublement->setValue(d->repeatedYears());
    nb_redoublement->setMaximumWidth(100);



    QLabel* label = new QLabel(tr("Redoublement"));
    label->setProperty("isFormLabel", true);
    label->setMaximumWidth(150);
    label->setMinimumWidth(150);
    BasicLayout->addWidget(label, 0, 0,Qt::AlignLeft);
    BasicLayout->addWidget(nb_redoublement, 0, 1);

    annee_entree = new QSpinBox();
    annee_entree->setMinimum(1980);
    annee_entree->setValue(2010);
    annee_entree->setMaximum(3000);
    annee_entree->setValue(d->startYear());


                QLabel* label2 = new QLabel(tr("Entry year"));
                label2->setProperty("isFormLabel", true);
                label2->setMaximumWidth(150);
                label2->setMinimumWidth(150);
                BasicLayout->addWidget(label2, 1, 0, Qt::AlignLeft);
                BasicLayout->addWidget(annee_entree, 1, 1);




                annee_quitte = new QSpinBox();
                annee_quitte->setMinimum(1980);
                annee_quitte->setMaximum(2080);
                annee_quitte->setValue(d->leaveYear());
                label = new QLabel(tr("Annee quitte"));
                label->setMaximumWidth(150);
                label->setMinimumWidth(150);
                label->setProperty("isFormLabel", true);
                BasicLayout->addWidget(label, 1, 2);
                BasicLayout->addWidget(annee_quitte, 1, 3);









    BasicLayout->setColumnMinimumWidth(0,150);
    this->setLayout(BasicLayout);
}
