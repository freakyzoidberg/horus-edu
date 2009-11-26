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
#ifndef DISPLAYABLEPLUGIN_H
#define DISPLAYABLEPLUGIN_H

#include <QWidget>
#include <QString>
#include <QIcon>

#include "../Common/Plugin.h"

//! Interface optionnal for using the display
/*!
 *  Each plugin implementing this interface will be able to use the display : show and use QWidgets
 */
class DisplayablePlugin : public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)

public:
    //! Pointer to an implementation of the interface IDisplayable
    /*!
     *  This pointer is set by the Client while loading the plugin.
     *  It let plugin access display ressources
     */
    virtual QWidget *getWidget() = 0;

    //! Return the displayable name of the plugin.
    /*!
     *  This name will be displayed in the left menu.
     *  If an empty QString is returned, this plugin will not be displayed in the menu.
     */
    virtual inline const QString getDisplayableName() const { return (QString()); }
	virtual inline QIcon getIcon() const { return (QIcon()); }
	virtual inline int getOrder() const { return (0); }
	virtual inline bool operator<(DisplayablePlugin &right) const { return (this->getOrder() < right.getOrder()); }

signals:
    void switchToWidget(QWidget *widget);
};

Q_DECLARE_INTERFACE(DisplayablePlugin, "net.horus.Client.DisplayablePlugin/1.0");

#endif // DISPLAYABLEPLUGIN_H
