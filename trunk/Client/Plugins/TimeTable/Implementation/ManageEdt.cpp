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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QVariant>

#include "ManageEdt.h"

ManageEdt::ManageEdt(PluginManager *pluginManager, MainView *parent)
{
	infos = NULL;
        sd = pluginManager->findPlugin<ScheduleDataPlugin *>();
        td = pluginManager->findPlugin<TreeDataPlugin *>();
        scheduleForm = 0;

	this->parent = parent;
	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);

	AdmClassList = new AdmClassListSelection(pluginManager);

	QLabel *infoTitle = new QLabel(tr("Informations:"));
	infoTitle->setProperty("isTitle", true);
	infoTitle->setProperty("isRound", true);
	informationsFrame = new QFrame(this);
	informationsFrame->setMinimumWidth(200);

	informationsLayout = new QVBoxLayout(informationsFrame);
	informationsLayout->setSpacing(0);
	informationsLayout->setMargin(0);
	informationsLayout->addWidget(infoTitle);
	RightLayout->addWidget(informationsFrame);
	QLabel *actionTitle = new QLabel(tr("Actions:"));
	actionTitle->setProperty("isTitle", true);
	actionTitle->setProperty("isRound", true);

	del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Delete this edt"));
	edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Edit this edt"));
	ok = new QPushButton(QIcon(":/ok.png"), tr("Ok"));
	save = new QPushButton(QIcon(":/save.png"), tr("Apply"));
	reset = new QPushButton(QIcon(":/reset.png"), tr("Reset"));
	back = new QPushButton(QIcon(":/back.png"), tr("Cancel"));
	add = new QPushButton(QIcon(":/AddTimeTable.png"), tr("Add"));

	RightLayout->addWidget(actionTitle);
	RightLayout->addWidget(edit);
	RightLayout->addWidget(del);
	RightLayout->addWidget(ok);
	RightLayout->addWidget(save);
	RightLayout->addWidget(reset);
	RightLayout->addWidget(back);
	RightLayout->addWidget(add);
	RightLayout->addWidget(new QWidget(this), 1);

	MainLayout->addWidget(AdmClassList);
	MainLayout->addLayout(RightLayout);
	MainLayout->setStretch(0, 1);

	ok->setVisible(false);
	save->setVisible(false);
	add->setVisible(false);
	reset->setVisible(false);
	back->setVisible(false);
	edit->setVisible(false);
	del->setVisible(false);

        connect(add, SIGNAL(clicked()), this, SLOT(goadd()));
        connect(edit, SIGNAL(clicked()), this, SLOT(goedit()));
        connect(del, SIGNAL(clicked()), this, SLOT(godelete()));
        //connect(save, SIGNAL(clicked()), this, SLOT(gosave()));
        connect(ok, SIGNAL(clicked()), this, SLOT(gook()));
        connect(reset, SIGNAL(clicked()), this, SLOT(goreset()));
		connect(back, SIGNAL(clicked()), this, SLOT(fallback()));
	connect(AdmClassList->ClassList, SIGNAL(itemClicked(QListWidgetItem *)),
	this, SLOT(classSelected(QListWidgetItem *)));

	this->setLayout(MainLayout);
}

void	ManageEdt::classSelected(QListWidgetItem *selectedItem)
{
        TreeData	*node = td->node(selectedItem->data(Qt::UserRole).toInt());
		bool		edt = false;

        updateVisible(4);

        if (infos)
        {
                delete infos;
                infos = NULL;
        }
        if (sd->schedule(node) != 0)
            edt = true;
		infos = new InfoPanel(edt);
        parent->getEdt()->createScene(node);
        if (edt == false)
		{
            updateVisible(2);
			parent->setTabEnabled(0, false);
			parent->setTabEnabled(1, false);
		}
        else
        {
			parent->setTabEnabled(0, true);
			parent->setTabEnabled(1, true);
			updateVisible(1);
        }
        this->informationsLayout->addWidget(infos);
}

void	ManageEdt::fallback()
{
	AdmClassList->setVisible(true);
	if (infos)
	{
		delete infos;
		infos = NULL;
	}
	if (scheduleForm)
	{
		delete scheduleForm;
		scheduleForm = NULL;
	}
	//MainLayout->removeWidget();
	MainLayout->insertWidget(0, AdmClassList);
	MainLayout->setStretch(0, 1);

		parent->setTabEnabled(0, false);
			parent->setTabEnabled(1, false);
	 ok->setVisible(false);
	del->setVisible(false);
	edit->setVisible(false);
	add->setVisible(false);
	back->setVisible(false);
	reset->setVisible(false);
}

void ManageEdt::goadd()
{

    if (AdmClassList->ClassList->selectedItems().count() == 1)
    {
        if (scheduleForm)
        {
            delete scheduleForm;
			scheduleForm = 0;
        }
        scheduleForm = new EditSchedule(sd, td, 0, 0);
		MainLayout->removeWidget(AdmClassList);
		MainLayout->insertWidget(0, scheduleForm);
		MainLayout->setStretch(0, 1);
        AdmClassList->setVisible(false);
        updateVisible(0);
		parent->setTabEnabled(0, false);
		parent->setTabEnabled(1, false);
    }
}

void ManageEdt::goreset()
{

}

void ManageEdt::gook()
{
    if (scheduleForm)
    {
        ScheduleData *edt = sd->newSchedule(td->node(AdmClassList->ClassList->selectedItems().first()->data(Qt::UserRole).toInt()));
        edt->setStartDate(scheduleForm->getStart());
        edt->setEndDate(scheduleForm->getStart());
        edt->create();
    }

    delete scheduleForm;
	scheduleForm = NULL;
	//MainLayout->removeWidget();
	MainLayout->insertWidget(0, AdmClassList);
	MainLayout->setStretch(0, 1);
    scheduleForm = 0;
    updateClasses();
    updateVisible(1);
}

void ManageEdt::godelete()
{
    ScheduleData *edt = sd->schedule(td->node(AdmClassList->ClassList->selectedItems().first()->data(Qt::UserRole).toInt()));
    edt->remove();
    updateVisible(2);
	parent->setTabEnabled(0, false);
	parent->setTabEnabled(1, false);
}

void ManageEdt::goedit()
{
    updateVisible(5);
    if (AdmClassList->ClassList->selectedItems().count() == 1)
    {
        if (scheduleForm)
        {
            delete scheduleForm;
            scheduleForm = 0;
        }
        scheduleForm = new EditSchedule(sd, td,AdmClassList->ClassList->selectedItems().first()->data(Qt::UserRole).toInt(), 1);
        MainLayout->insertWidget(0, scheduleForm);
        AdmClassList->setVisible(false);
    }

    delete scheduleForm;
    scheduleForm = 0;
    updateClasses();
    updateVisible(1);
}

void ManageEdt::updateClasses()
{
    AdmClassList->setVisible(true);
}

void ManageEdt::updateVisible(int type)
{
    if (type == 0)
    {
        ok->setVisible(true);
        del->setVisible(false);
        edit->setVisible(false);
        add->setVisible(false);
        back->setVisible(true);
        reset->setVisible(true);
    }
    else if (type == 1)
    {
        ok->setVisible(false);
        save->setVisible(false);
        del->setVisible(true);
        edit->setVisible(true);
		if (infos)
			delete infos;
		infos = new InfoPanel(true);
		this->informationsLayout->addWidget(infos);
		infos->setVisible(true);
        add->setVisible(false);
        back->setVisible(false);
        reset->setVisible(false);
    }
    else if (type == 2)
    {
        ok->setVisible(false);
        del->setVisible(false);
        save->setVisible(false);
		if (infos)
			delete infos;
		infos = new InfoPanel(false);
		this->informationsLayout->addWidget(infos);
        edit->setVisible(false);
        add->setVisible(true);
        back->setVisible(false);
        reset->setVisible(false);
    }
    else if (type == 3)
    {
        ok->setVisible(false);
        save->setVisible(false);
        del->setVisible(false);
        edit->setVisible(false);
        add->setVisible(false);
        back->setVisible(false);
        reset->setVisible(false);
    }
    else if (type == 4)
    {
        ok->setVisible(false);
        save->setVisible(true);
        del->setVisible(false);
        edit->setVisible(false);
        add->setVisible(false);
        back->setVisible(true);
        reset->setVisible(true);
    }

}
