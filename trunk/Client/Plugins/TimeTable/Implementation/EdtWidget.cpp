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
#include "EdtWidget.h"
#include <QVBoxLayout>
# include <QDebug>
EdtWidget::EdtWidget(PluginManager *pluginManager) : _pluginManager(pluginManager)
{
    _currentClass = 0;
    _sceneWidget = 0;
    MainLayout = new QHBoxLayout();
    MainLayout->setSpacing(0);
    MainLayout->setMargin(2);
    scrollArea = new QScrollArea();
    id_item_edition = -1;
    _form = 0;
    _TD = 0;
    if (pluginManager->currentUser()->level() == LEVEL_STUDENT)
    {
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, pluginManager->currentUser()->studentClass(),760,560);
    _sceneWidget->setMinimumSize(760,580);
    _sceneWidget->setMaximumSize(760,580);

    scrollArea->setWidget(_sceneWidget);


    scrollArea->setAlignment(Qt::AlignCenter);
    MainLayout->insertWidget(0,scrollArea);
    MainLayout->setStretch(0, 10000);

    }
    else if (pluginManager->currentUser()->level() == LEVEL_TEACHER)
    {
    _sceneWidget = new EdtSceneProxyWidget(_pluginManager,760,560);
    _sceneWidget->setMinimumSize(760,580);
    _sceneWidget->setMaximumSize(760,580);

    scrollArea->setWidget(_sceneWidget);


    scrollArea->setAlignment(Qt::AlignCenter);
    MainLayout->insertWidget(0,scrollArea);
    MainLayout->setStretch(0, 10000);

    }
    else if (pluginManager->currentUser()->level() <= LEVEL_ADMINISTRATOR)
    {

        QVBoxLayout *RightLayout = new QVBoxLayout();
        RightLayout->setSpacing(2);

        QLabel *infoTitle = new QLabel(tr("Informations:"));
        infoTitle->setProperty("isTitle", true);
        infoTitle->setProperty("isRound", true);
        informationsFrame = new QFrame(this);
        informationsFrame->setMinimumWidth(200);


        QVBoxLayout *informationsLayout = new QVBoxLayout(informationsFrame);
        informationsLayout->setSpacing(0);
        informationsLayout->setMargin(0);
        informationsLayout->addWidget(infoTitle);
        RightLayout->addWidget(informationsFrame);

        QLabel *actionTitle = new QLabel(tr("Actions:"));
        actionTitle->setProperty("isTitle", true);
        actionTitle->setProperty("isRound", true);

        //_del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Delete this edt"));
        //_edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Edit this edt"));
        _ok = new QPushButton(QIcon(":/ok.png"), tr("Ok"));
        _save = new QPushButton(QIcon(":/save.png"), tr("Apply"));
        _reset = new QPushButton(QIcon(":/reset.png"), tr("Reset"));
        _back = new QPushButton(QIcon(":/back.png"), tr("Cancel"));
        _add = new QPushButton(QIcon(":/AddTimeTable.png"), tr("Add"));
        _edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Edit"));
        _del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Delete"));

        RightLayout->addWidget(actionTitle);
        //RightLayout->addWidget(edit);
        //RightLayout->addWidget(del);
        RightLayout->addWidget(_ok);
        RightLayout->addWidget(_save);
        RightLayout->addWidget(_reset);
        RightLayout->addWidget(_back);
        RightLayout->addWidget(_add);
        RightLayout->addWidget(_edit);
        RightLayout->addWidget(_del);
        RightLayout->addWidget(new QWidget(this), 1);
        MainLayout->insertStretch(0,1);
        MainLayout->addLayout(RightLayout);

        _ok->hide();
        _save->hide();
        _reset->hide();
        _back->hide();
        _edit->hide();
        _del->hide();


        connect(this->_add, SIGNAL(clicked()),this, SLOT(goadd()));
        connect(this->_back, SIGNAL(clicked()),this, SLOT(goback()));
        connect(this->_save, SIGNAL(clicked()),this, SLOT(gosave()));
        connect(this->_ok, SIGNAL(clicked()),this, SLOT(gook()));
        connect(this->_reset, SIGNAL(clicked()),this, SLOT(goreset()));
        connect(this->_edit, SIGNAL(clicked()),this, SLOT(goedit()));
         connect(this->_del, SIGNAL(clicked()),this, SLOT(godel()));
    }
        else
    {
    _sceneWidget = NULL;
    }

    this->setLayout(MainLayout);
}


void EdtWidget::createScene(TreeData *td)
{
    _TD = td;

    if (_sceneWidget)
        delete _sceneWidget;

    if (scrollArea)
        delete scrollArea;

    if (_form)
        delete _form;
    _form = 0;
    id_item_edition = -1;


    _ok->hide();
    _save->hide();
    _reset->hide();
    _back->hide();
    _edit->hide();
    _del->hide();
    _add->show();

    _sceneWidget = new EdtSceneProxyWidget(_pluginManager, td,760,560);
    _sceneWidget->setMinimumSize(760,580);
    _sceneWidget->setMaximumSize(760,580);

    connect(_sceneWidget->scene(), SIGNAL(eventItemEditionRequired(int)),this, SLOT(showItemEdition(int)));

    scrollArea = new QScrollArea();
    scrollArea->setWidget(_sceneWidget);
    scrollArea->setAlignment(Qt::AlignCenter);

    //scrollArea->setMaximumSize(765,585);
    MainLayout->insertWidget(0,scrollArea);
    MainLayout->setStretch(0, 10000);
  
}



void EdtWidget::goadd()
{
    scrollArea->hide();
    _add->hide();
    _ok->show();
    _save->show();
    _reset->show();
    _back->show();
    _edit->hide();
    _del->hide();
    if (_form)
        delete _form;
_form = new EditScheduleEvent(_pluginManager);
MainLayout->insertWidget(0,_form,10000,Qt::AlignTop);
}

void EdtWidget::gosave()
{
    saveEDT();
}

void EdtWidget::gook()
{

    ScheduleData *sd = _pluginManager->findPlugin<ScheduleDataPlugin* >()->schedule(_TD);
    sd->addEvent(new ScheduleItem(sd->id(), _form->getDay(), _form->getName(), _form->getStart(), _form->getEnd(), _form->getDetail(), _form->getStartDate(), _form->getEndDate(), _form->getForce(), _form->getModulo(), _form->getTeacher(), "White"));
    sd->save();
    if (saveEDT())
        goback();
}

void EdtWidget::goreset()
{

    // if (!_form)
    //  return;
    // _form->name().clear();
    // ...
}

void EdtWidget::goback()
{

    if (_form)
        delete _form;
    _form = 0;
    createScene(_TD);

    _add->show();
    _ok->hide();
    _save->hide();
    _reset->hide();
    _back->hide();
    _edit->hide();
    _del->hide();
}



void EdtWidget::showItemEdition(int id)
{
    id_item_edition = id;
    _edit->show();
    _del->show();
}

void EdtWidget::goedit()
{
    scrollArea->hide();
    _add->hide();
    _ok->show();
    _save->show();
    _reset->show();
    _back->show();
    _edit->hide();
    _del->hide();
    if (_form)
        delete _form;
    _form = new EditScheduleEvent(_pluginManager); // devrait passer par constructeur pour edition
    MainLayout->insertWidget(0,_form,10000,Qt::AlignTop);
}


void EdtWidget::godel()
{

    _add->show();
    _ok->hide();
    _save->hide();
    _reset->hide();
    _back->hide();
    _edit->hide();
    _del->hide();

    deleteEventFromEdt(id_item_edition);
    createScene(_TD);
}


bool                EdtWidget::saveEDT()
{
    // reccupere les infos du form
    // cree / update le schedule event
    // update la data
    // save la data
    return true;
}

bool                EdtWidget::deleteEventFromEdt(int id)
{
    // supprime schedule event de la data
    // save la data
    return true;
}
