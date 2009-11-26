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
#include "AbsenceFrame.h"
#include <qDebug>
AbsenceFrame::AbsenceFrame(TreeDataPlugin *tree, UserDataPlugin *_user, EventDataPlugin *event)
{
    user = _user;
    setupUi();
    fillClass(tree);
    connect(userName, SIGNAL(textChanged( const QString &)), this , SLOT(nameChanged(QString)));
    connect(classList, SIGNAL(currentIndexChanged(int)), this, SLOT(classChanged(int)));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    connect(dateAbsence, SIGNAL(dateChanged(const QDate &)), this, SLOT(dChanged(const QDate &)));
    connect(allCourse, SIGNAL(stateChanged(int)), this, SLOT(allChecked(int)));
    fillCourse(event);
    proxyModel = new QSortFilterProxyModel();
    userList->setModel(new UserPerClass(user->allUser(), -10, this));
}

void    AbsenceFrame::fillClass(TreeDataPlugin *tree)
{
    for (int i = 0; i < tree->allDatas().size(); ++i)
    {
        TreeData    *data = qobject_cast<TreeData *>(tree->allDatas().at(i));
        if ((data->type()) == "GRADE")
        {
            classList->addItem(data->name(), data->id());
        }
    }
}

void    AbsenceFrame::fillCourse(EventDataPlugin *event)
{
    courList.append(new CourPanel("Mathematiques"));
    courList.append(new CourPanel("Physique"));
    courList.append(new CourPanel("Histoire"));
    courList.append(new CourPanel("Anglais"));

    for (int i = 0; i < courList.size(); i++)
    {
        rightSide->addWidget(courList.at(i), i + 1, 0);
    }
    absLayout->addLayout(rightSide);
    absLayout->setAlignment(rightSide, Qt::AlignTop);
    absLayout->setStretch(0, 1);
    absLayout->setStretch(1, 3);
    rightSide->addLayout(buttonLayout->layout(), 5, 0);
}

void    AbsenceFrame::setupUi()
{
    absLayout = new QHBoxLayout(this);
    rightSide = new QGridLayout();
    leftSide = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();
    userName = new QLineEdit();
    leftSide->addWidget(userName);
    classList = new QComboBox();
    leftSide->addWidget(classList);
    userList = new QListView();
    leftSide->addWidget(userList);
    absLayout->addLayout(leftSide);
    dateAbsence = new QDateEdit();
    dateAbsence->setMaximumSize(100, 30);
    dateAbsence->setDate(QDate::currentDate());
    rightSide->addWidget(dateAbsence);
    rightSide->setSpacing(0);
    allCourse = new QCheckBox(tr("Check All"));
    okButton = new QPushButton(tr("Valider"));
    buttonLayout->addWidget(allCourse);
    buttonLayout->addWidget(okButton);
}

void    AbsenceFrame::dChanged(const QDate &date)
{
    for (int i = 0; i < courList.size(); i++)
    {
        rightSide->removeWidget(courList.at(i));
        courList[i]->close();
    }
    courList[0] = new CourPanel("Grec");
    courList[1] = new CourPanel("Francais");
    courList[2] = new CourPanel("Chinois");
    courList[3] = new CourPanel("Anglais");

    for (int i = 0; i < courList.size(); i++)
    {
        rightSide->addWidget(courList.at(i), i + 1, 0);
    }
}

void    AbsenceFrame::allChecked(int state)
{
    for (int i = 0; i < courList.size(); i++)
    {
        if (state == 2)
            courList[i]->absenceCheck->setChecked(true);
        else
            courList[i]->absenceCheck->setChecked(false);
    }
}

void    AbsenceFrame::nameChanged(const QString &text)
{
    //apply filter soon
}

void    AbsenceFrame::classChanged(int index)
{
    userList->setModel(new UserPerClass(user->allUser(), classList->itemData(index).toInt(), this));
}

void    AbsenceFrame::okClicked()
{
    //sendData soon
}
