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
#include "ElevePanel.h"

ElevePanel::ElevePanel(QHash<int, QString> eleves)
{
    setupUi();
    fillStudents(eleves);
    mainLayout->addLayout(bottomLayout);
    connect(okButton, SIGNAL(clicked()), this, SLOT(validateClicked()));
}

void        ElevePanel::setupUi()
{
    mainLayout = new QVBoxLayout(this);
//    scrollArea = new QScrollArea;
//    scrollArea->setBackgroundRole(QPalette::Dark);
//    scrollArea->setLayout(mainLayout);
//
    mainLayout->setAlignment(this, Qt::AlignTop);
    bottomLayout = new QHBoxLayout();
    date = new QDateEdit(QDate::currentDate());
    date->setMaximumWidth(120);
    bottomLayout->addWidget(date);
    coefLabel = new QLabel(tr("Coef"));
    bottomLayout->addWidget(coefLabel);
    coef = new QLineEdit();
    coef->setMaximumWidth(40);
    okButton = new QPushButton(tr("Valider"));
    bottomLayout->addWidget(coef);
    bottomLayout->addWidget(okButton);
}

void        ElevePanel::fillStudents(QHash<int, QString> students)
{
    QHBoxLayout *tmp = new QHBoxLayout();
    QLabel *stuL = new QLabel(tr("Eleves"));
    stuL->setMaximumWidth(120);
    stuL->setMinimumWidth(70);
    tmp->addWidget(stuL);
    QLabel *markL = new QLabel(tr("Notes"));
    tmp->addWidget(markL);
    QLabel *comL = new QLabel(tr("Commentaire"));
    tmp->addWidget(comL);
    mainLayout->addLayout(tmp);
    mainLayout->setAlignment(tmp, Qt::AlignTop);
    QHash<int, QString>::const_iterator it = students.constBegin();
    QList<QWidget*> wdgts;
    QLineEdit *tmpNote;
    QLineEdit *tmpCom;
    while(it != students.constEnd())
    {
        tmp = new QHBoxLayout();
        QLabel *userName = new QLabel(it.value());
        userName->setMaximumWidth(180);
        userName->setMinimumWidth(120);
        tmp->addWidget(userName);
        tmpNote = new QLineEdit();
        tmpNote->setMaximumWidth(30);
        tmp->addWidget(tmpNote);
        tmpCom = new QLineEdit();
        tmp->addWidget(tmpCom);
        wdgts.append(tmpNote);
        wdgts.append(tmpCom);
        hNotes[it.key()] = wdgts;
        mainLayout->addLayout(tmp);
        mainLayout->setAlignment(tmp, Qt::AlignTop);
        wdgts.clear();
        ++it;
    }
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);
}

void    ElevePanel::validateClicked()
{
    QHash<int, QList<QWidget* > >::const_iterator it = hNotes.constBegin();
    while(it != hNotes.constEnd())
    {
        if (((QLineEdit*)it.value()[0])->text() == "" || ((QLineEdit*)it.value()[1])->text() == "")
        {
            QMessageBox msgBox;
            msgBox.setText(tr(""));
            msgBox.setInformativeText(tr("Veuillez remplir tous les champs."));
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.exec();
            break;
        }
        ++it;
    }
}
