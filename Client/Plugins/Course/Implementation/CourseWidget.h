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
#ifndef __COURSEWIDGET_H__
# define __COURSEWIDGET_H__

# include               <QSplitter>
# include               <QModelIndex>
# include               <QAbstractItemModel>
# include               <QTreeView>

# include               "../../LessonManager/ILessonManager.h"
# include				"../../../../Common/TreeDataPlugin.h"
# include				"../../../../Common/FileDataPlugin.h"
# include				"../../../../Common/FileData.h"
# include               "../../../../Common/UserData.h"

# include				"WhiteBoard.h"
# include				"Items.h"

class                   CourseWidget : public QWidget
{
    Q_OBJECT

public:
    CourseWidget(QWidget *parent, WhiteBoardData *wbd, PluginManager *pluginManager, UserData* user);

private:
    void                buildCategoryTree();

private slots:
    void contextMenu(const QPoint& point);
    void selectionChanged(QModelIndex current, QModelIndex previous);
    void addDocument();
    void addSection();
    void addLesson();

private:
    ILessonManager      *lessonPlugin;
    TreeDataPlugin      *treePlugin;
    WhiteBoardDataPlugin *whiteboardPlugin;
    FileDataPlugin	*filePlugin;
    LessonModel		*categoryModel;
    QTreeView           *categoryView;
    WhiteBoard          *pageWidget;
    quint32             fileIndex;
    FileData            *lessonFile;
    static QIcon        *lessonIcon;
    static QIcon	*sectionIcon;
    static QIcon	*documentIcon;
    QModelIndex		currentIndex;
    QSplitter           splitter;
    UserData*           user;
};

#endif // __COURSEWIDGET_H__
