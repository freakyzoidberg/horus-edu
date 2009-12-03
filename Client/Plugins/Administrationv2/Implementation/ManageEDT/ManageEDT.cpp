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
#include "ManageEDT.h"
#include <QDebug>
#include <QMessageBox>
#include "EdtScene.h"
#include <QGraphicsView>
#include <QTableWidget>
ManageEDT::ManageEDT(TreeDataPlugin *treeplugin, ScheduleDataPlugin *scheduleplugin)
{
    SD = scheduleplugin;
    TD = treeplugin;
    MainLayout = new QHBoxLayout();
    MainLayout->setSpacing(0);
    MainLayout->setMargin(2);
    //EDTScene *scene = new EDTScene();


    QTableWidget *tview = new QTableWidget(12, 7);
    tview->setMinimumSize(733, 388);
    QStringList dWeek;
    dWeek   << tr("Lundi")
            << tr("Mardi")
            << tr("Mercredi")
            << tr("Jeudi")
            << tr("Vendredi")
            << tr("Samedi")
            << tr("Dimanche");
    tview->setHorizontalHeaderLabels(dWeek);
    QStringList hDay;
    hDay    << tr("8h")
            << tr("9h")
            << tr("10h")
            << tr("11h")
            << tr("12h")
            << tr("13h")
            << tr("14h")
            << tr("15h")
            << tr("16h")
            << tr("17h")
            << tr("18h")
            << tr("19h");
    tview->setVerticalHeaderLabels(hDay);
    for (int x = 0; x < 11; x++)
        for(int y = 0; y < 7; y++)
        {
            QTableWidgetItem *item = new QTableWidgetItem(0);
            tview->setItem(x, y, item);
        }
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsProxyWidget *proxy = scene->addWidget(tview);
    QGraphicsView *gview = new QGraphicsView(scene);
    MainLayout->addWidget(gview);
    this->setLayout(MainLayout);
}
