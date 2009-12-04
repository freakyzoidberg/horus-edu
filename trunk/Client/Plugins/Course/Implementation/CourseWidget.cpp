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
#include "CourseWidget.h"

#include <QFileSystemModel>
#include <QTreeView>
#include <QDebug>
#include <QSizePolicy>
#include <QGridLayout>
#include <QMenu>

CourseWidget::CourseWidget(QWidget *parent, WhiteBoardData *wbd, PluginManager *pluginManager, UserData *user) : QWidget(parent), user(user)
{
    QWidget *leftPane;
    QGridLayout* layout;

    layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    lessonPlugin = pluginManager->findPlugin<ILessonManager *>("LessonManager");
    treePlugin = pluginManager->findPlugin<TreeDataPlugin *>();
    whiteboardPlugin = pluginManager->findPlugin<WhiteBoardDataPlugin*>();
    filePlugin = pluginManager->findPlugin<FileDataPlugin*>();
    QList<IDocumentController *> controllersList = pluginManager->findPlugins<IDocumentController *>();
    QHash<QString, IDocumentController *> controllers;
    foreach (IDocumentController *controller, controllersList)
    controllers[controller->getSupportedType()] = controller;
    this->buildCategoryTree();
    this->pageWidget = new WhiteBoard(wbd, controllers, this->categoryModel, user);

    if (user->level() == LEVEL_TEACHER)
    {
        splitter.setHandleWidth(2);
        layout->addWidget(&splitter);
        splitter.show();
        leftPane = new QWidget(this);
        splitter.addWidget(leftPane);
        QGridLayout *lpLayout;
        lpLayout = new QGridLayout(leftPane);
        lpLayout->setMargin(0);
        lpLayout->setSpacing(0);
        lpLayout->addWidget(this->categoryView);
        splitter.addWidget(this->pageWidget);
        splitter.setStretchFactor(0, 0);
        splitter.setStretchFactor(1, 3);
    }
    else
    {
        layout->addWidget(pageWidget);
        layout->setMargin(2);
    }

    if (lessonIcon == NULL)
        lessonIcon = new QIcon(":/LessonIcon.png");
    if (sectionIcon == NULL)
        sectionIcon = new QIcon(":/SectionIcon.png");
    if (documentIcon == NULL)
        documentIcon = new QIcon(":/DocumentIcon.png");
}


void CourseWidget::buildCategoryTree()
{
    this->categoryModel = this->lessonPlugin->getLessonModel();
    if (user->level() == LEVEL_TEACHER)
    {
        this->categoryView = new QTreeView(this);
        this->categoryView->setModel(this->categoryModel);
        this->categoryView->setAnimated(true);
        this->categoryView->setAutoExpandDelay(500);
        //this->categoryView->setRootIsDecorated(false);
        this->categoryView->setHeaderHidden(true);
        this->categoryView->setSelectionMode(QAbstractItemView::SingleSelection);
        this->categoryView->setSelectionBehavior(QAbstractItemView::SelectItems);
        //this->categoryView->setRootIndex(this->categoryModel->index(0, 0, this->categoryView->rootIndex()));
        this->categoryView->setDragEnabled(true);
        this->categoryView->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(this->categoryView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
        QObject::connect(this->categoryView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(selectionChanged(QModelIndex,QModelIndex)));
        this->categoryView->expandAll();
    }
}

void CourseWidget::contextMenu(const QPoint &)
{
    /*
	if (currentIndex.isValid())
	{
            QList<QAction *> actions;
            QObject* obj = static_cast<QObject *>(currentIndex.internalPointer());
            ILesson* lesson = dynamic_cast<ILesson *>(obj);
            ILessonSection* section = dynamic_cast<ILessonSection *>(obj);
            if (lesson || section)
            {
                    QAction *action = new QAction(*sectionIcon, tr("createSection"), NULL);
                    QObject::connect(action, SIGNAL(triggered()), this, SLOT(addSection()));
                    actions.push_back(action);
                    action = new QAction(*documentIcon, tr("createDocument"), NULL);
                    QObject::connect(action, SIGNAL(triggered()), this, SLOT(addDocument()));
                    actions.push_back(action);
            }
            TreeData* treedata = dynamic_cast<TreeData*>(obj);
            if (treedata && treedata->type() == "SUBJECT")
            {
                    QAction *action = new QAction(*lessonIcon, tr("createLesson"), NULL);
                    QObject::connect(action, SIGNAL(triggered()), this, SLOT(addLesson()));
                    actions.push_back(action);
            }
            QMenu::exec(actions, this->categoryView->mapToGlobal(point));
	}
    */
}

void CourseWidget::selectionChanged(QModelIndex current, QModelIndex previous)
{
    currentIndex = current;
}

void CourseWidget::addDocument()
{

}

void CourseWidget::addSection()
{

}

void CourseWidget::addLesson()
{
    categoryModel->createLesson(currentIndex);
}

QIcon		*CourseWidget::lessonIcon = NULL;
QIcon		*CourseWidget::sectionIcon = NULL;
QIcon		*CourseWidget::documentIcon = NULL;
