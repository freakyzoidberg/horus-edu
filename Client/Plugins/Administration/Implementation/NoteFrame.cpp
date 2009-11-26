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
#include "NoteFrame.h"

NoteFrame::NoteFrame(TreeDataPlugin *_tree, UserDataPlugin *user, EventDataPlugin *event)
{
    listEleve = 0;
    tree = _tree;
    users = user->allUser();
    setupUi();
    connect(classList, SIGNAL(currentIndexChanged(int)), this, SLOT(classChanged(int)));
    connect(matiereList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(matiereSelected(QListWidgetItem *)));
    connect(examList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(examSelected(QListWidgetItem *)));
    fillClass(tree);
}

void    NoteFrame::setupUi()
{
    noteLayout = new QHBoxLayout(this);
    leftSide = new QVBoxLayout();
    classList = new QComboBox();
    leftSide->addWidget(classList);
    matiereList  = new QListWidget();
    leftSide->addWidget(matiereList);
    examList = new QListWidget();
    leftSide->addWidget(examList);
    noteLayout->addLayout(leftSide, 1);
}

void    NoteFrame::fillClass(TreeDataPlugin *tree)
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


void    NoteFrame::classChanged(int index)
{
    if (listEleve != 0)
    {
        noteLayout->removeWidget(listEleve);
        listEleve->close();
        listEleve = 0;
    }
    matiereList->clear();
    examList->clear();
    for (int i = 0; i < tree->allDatas().size(); ++i)
    {
        TreeData    *data = qobject_cast<TreeData *>(tree->allDatas().at(i));
        if ((data->type()) == "SUBJECT" && data->parent()->id() == classList->itemData(index))
        {
            QListWidgetItem *tmp = new QListWidgetItem(data->name());
            tmp->setData(Qt::UserRole, data->id());
            matiereList->addItem(tmp);
        }
    }
    id = classList->itemData(index).toInt();
}

void    NoteFrame::matiereSelected(QListWidgetItem *item)
{
    if (listEleve != 0)
    {
        noteLayout->removeWidget(listEleve);
        listEleve->close();
        listEleve = 0;
    }
    examList->clear();
    examList->addItem("Exam 1");
    examList->addItem("Exam 2");
    examList->addItem("Exam 3");
    examList->addItem("Exam 3");
}

void    NoteFrame::examSelected(QListWidgetItem *item)
{
    if (listEleve != 0)
    {
        noteLayout->removeWidget(listEleve);
        listEleve->close();
        listEleve = 0;
    }
    QHash<int, QString> eleves;
    foreach (UserData* user, users)
    {
        if (user->node()->id() == classList->itemData(classList->currentIndex()))
            eleves[user->id()] = user->name();
    }
    qDebug() << eleves.size();
    listEleve = new ElevePanel(eleves);
    noteLayout->addWidget(listEleve, 3);
}
