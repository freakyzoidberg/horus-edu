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
#ifndef ITEMS_H
#define ITEMS_H

#include <QWidget>
#include <QPushButton>
#include <QDockWidget>
#include <QSizeGrip>
#include <QMouseEvent>
#include <QGridLayout>

#include "WhiteBoard.h"

class Items : public QWidget
{
    Q_OBJECT
public:
    Items(QWidget *parent, WhiteBoard *, ILesson* lesson, int id, QString, QString);
    ~Items();

    bool            getIsDocked();
    void            setMainWidget(QWidget *);
    QWidget         *getMainWidget();
    inline ILesson* getLesson() const { return lesson; }

public slots:
    void            moveToDock();
    void            restore();
    int             getId();
    bool            deleteWidgets();

protected:
    void            mousePressEvent(QMouseEvent *event);
    void            mouseMoveEvent(QMouseEvent *event);
    void            mouseReleaseEvent(QMouseEvent *event);

private:
    WhiteBoard      *board;
    QPushButton     *small;
    QWidget         *mainWidget;
    QPushButton     *openItem, *closeItem;
    int             id;
    QString         title;
    QString         type;
    bool            isDocked;
    bool            isMoving;
    bool            isResizing;
    int             X, Y, saveX, saveY;
    QGridLayout     *_layout;
    ILesson*        lesson;
};

#endif // ITEMS_H
