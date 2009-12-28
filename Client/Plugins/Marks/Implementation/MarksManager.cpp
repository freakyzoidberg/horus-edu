#include "MarksManager.h"
#include "../../../../Common/TreeData.h"
#include <QLabel>

MarksManager::MarksManager(PluginManager *pm)
{
	_pm = pm;

	infos = NULL;
		td = pm->findPlugin<TreeDataPlugin *>();
	//	scheduleForm = 0;
	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);

	_classList = new ClassList(pm);

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

	MainLayout->addWidget(_classList);
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
	//connect(AdmClassList->ClassList, SIGNAL(itemClicked(QListWidgetItem *)),
		//	this, SLOT(classSelected(QListWidgetItem *)));
	connect(_classList->Classlist, SIGNAL(itemClicked(QListWidgetItem *)),
				this, SLOT(subjectSelected(QListWidgetItem *)));

	this->setLayout(MainLayout);
}


void	MarksManager::subjectSelected(QListWidgetItem *item)
{
	if (infos)
		delete infos;
	quint32 subjectId = item->data(Qt::UserRole).toInt();

	infos = new InfoPanel(td->node(subjectId)->parent()->name());
	this->informationsLayout->addWidget(infos);
	infos->show();
}
