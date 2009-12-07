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
#ifndef EDTWIDGET_H
#define EDTWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "../../../../Common/ScheduleData.h"
 #include <QLabel>
#include <QPushButton>
#include <QFrame>
#include "EdtSceneProxyWidget.h"

class EdtWidget : public QWidget
{
    Q_OBJECT

public:
    EdtWidget(PluginManager *pluginManager);

public slots:
    void createScene(TreeData *);

private:
    PluginManager	*_pluginManager;
    EdtSceneProxyWidget *_sceneWidget;
    QScrollArea         *scrollArea;
    QGridLayout         *MainLayout;
    QLabel              *_currentClass;
    QPushButton         *_ok;
    QPushButton         *_save;
    QPushButton         *_reset;
    QPushButton         *_add;
    QPushButton         *_back;
    QFrame              *informationsFrame;

};

#endif // EDTWIDGET_H
