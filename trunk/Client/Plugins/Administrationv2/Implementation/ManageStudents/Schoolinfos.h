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
#ifndef SCHOOLINFOS_H
#define SCHOOLINFOS_H

#include <QFrame>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include "../../../../../Common/UserData.h"
class SchoolInfos : public QFrame
{
	Q_OBJECT

public:
        SchoolInfos();
		SchoolInfos(UserData *d);
        QString     getMotif() { return motif->toPlainText(); }
        QString     getMoyenne() { return moyenne->text(); }
        QString     getComment() { return comment->toPlainText(); }
        int         getNb_red() { return nb_redoublement->value(); }
        int         getStartYear() { return annee_entree->value(); }
         int         getLeftYear() { return annee_quitte->value(); }
        //QString     getRaison() { return raisons_redoublement->text(); }
    private:
       // QLineEdit *raisons_redoublement;
        QSpinBox *nb_redoublement;
         QSpinBox *annee_entree;
        QTextEdit *motif;
        QLineEdit *moyenne;
        QTextEdit *comment;
        QSpinBox *annee_quitte;
};

#endif // SCHOOLINFOS_H
