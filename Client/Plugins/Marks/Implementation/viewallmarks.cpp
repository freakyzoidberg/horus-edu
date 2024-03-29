#include <QTableView>
#include <QHeaderView>
#include "../../../../Common/UserData.h"
#include <QStringList>

#include "viewallmarks.h"

ViewAllMarks::ViewAllMarks(PluginManager *pluginManager, QTabWidget *mainView)
{
	QStringList labels;

	labels.append(tr("Matiere"));
	labels.append(tr("Examen"));
	labels.append(tr("Note"));
	labels.append(tr("Commentaire"));
	_parent = mainView;
	_markData = NULL;
	_pluginManager = pluginManager;
	_infosLabel = new QLabel();
	td = pluginManager->findPlugin<TreeDataPlugin *>();

	mainWidget = new QTableWidget();
	mainWidget->insertColumn(0);
	mainWidget->insertColumn(1);
	mainWidget->insertColumn(2);
	mainWidget->insertColumn(3);
	mainWidget->setHorizontalHeaderLabels(labels);
	mainWidget->horizontalHeader()->setStretchLastSection(true);

	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);

	QLabel *infoTitle = new QLabel(tr("Informations:"));
	infoTitle->setProperty("isTitle", true);
	infoTitle->setProperty("isRound", true);
	QLabel *infos = new QLabel(tr("Liste de vos resultats."));

	informationsFrame = new QFrame(this);
	informationsFrame->setMinimumWidth(200);

	informationsLayout = new QVBoxLayout(informationsFrame);
	informationsLayout->setSpacing(0);
	informationsLayout->setMargin(0);
	informationsLayout->addWidget(infoTitle);
	RightLayout->addWidget(informationsFrame);
	RightLayout->addWidget(_infosLabel);
//	QLabel *actionTitle = new QLabel(tr("Actions:"));
//	actionTitle->setProperty("isTitle", true);
//	actionTitle->setProperty("isRound", true);
	del = new QPushButton(QIcon(":/Marks/DelTimeTable.png"), tr("Supprimer la note"));
	edit = new QPushButton(QIcon(":/Marks/EditTimeTable.png"), tr("Voir les etudiants."));
	ok = new QPushButton(QIcon(":/Marks/ok.png"), tr("Ok"));
	save = new QPushButton(QIcon(":/Marks/save.png"), tr("Enregistrer"));
	reset = new QPushButton(QIcon(":/Marks/reset.png"), tr("Reinitiliaser."));
	back = new QPushButton(QIcon(":/Marks/back.png"), tr("Annuler"));
	_add = new QPushButton(QIcon(":/Marks/AddTimeTable.png"), tr("Ajouter un examen"));

	RightLayout->addWidget(infos);
	RightLayout->addWidget(edit);
	RightLayout->addWidget(del);
	RightLayout->addWidget(ok);
	RightLayout->addWidget(save);
	RightLayout->addWidget(reset);
	RightLayout->addWidget(back);
	RightLayout->addWidget(_add);
	RightLayout->addWidget(new QWidget(), 1);

	ok->setVisible(false);
	save->setVisible(false);
	_add->setVisible(false);
	reset->setVisible(false);
	back->setVisible(false);
	edit->setVisible(false);
	del->setVisible(false);


/*	connect(_add, SIGNAL(clicked()), this, SLOT(addExam()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveExam()));
	connect(back, SIGNAL(clicked()), this, SLOT(fallback()));

	connect(_examsList->_examsList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(examSelected(QListWidgetItem *)));
	connect(_examsList->_examsList, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
			this, SLOT(viewStudentList(QListWidgetItem *)));
	connect(_sList->_sList, SIGNAL(itemClicked(QListWidgetItem *)),
			this, SLOT(studentSelection(QListWidgetItem *)));
	connect(del, SIGNAL(clicked()), this, SLOT(removeMark()));
	connect(edit, SIGNAL(clicked()), this, SLOT(seeStudents())); */

	if (pluginManager->currentUser()->level() >= LEVEL_TEACHER)
	{
		MainLayout->addWidget(mainWidget);
		MainLayout->addLayout(RightLayout);
		initGradesList(NULL);
		MainLayout->setStretch(0, 1);
	}
	else
	{
		this->_allS = new AllStudents(_pluginManager);
		_allS->fillList();
		connect(_allS->sList(), SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(initGradesL(QListWidgetItem *)));

		MainLayout->addWidget(_allS);
		MainLayout->addWidget(mainWidget);
		MainLayout->addLayout(RightLayout);
		MainLayout->setStretch(1, 1);
	}
	this->setLayout(MainLayout);
}

void	ViewAllMarks::initGradesL(QListWidgetItem *item)
{
	initGradesList(item);
}

void	ViewAllMarks::initGradesList(QListWidgetItem *item)
{

	QStringList labels;

	labels.append(tr("Matiere"));
	labels.append(tr("Examen"));
	labels.append(tr("Note"));
	labels.append(tr("Commentaire"));

	UserDataPlugin	*udp = _pluginManager->findPlugin<UserDataPlugin *>();
	UserData *user;
	int row = 0;

	int nbrow = mainWidget->rowCount();
	for (int i = 0; i < nbrow; ++i)
		mainWidget->removeRow(i);
	mainWidget->rowCount();
	mainWidget->clearContents();
	mainWidget->clear();

	if (item == NULL)
		user = _pluginManager->currentUser();
	else
		user = udp->user(item->data(Qt::UserRole).toInt());
	ExamsDataPlugin	*edp = _pluginManager->findPlugin<ExamsDataPlugin *>();
	MarksDataPlugin	*mdp = _pluginManager->findPlugin<MarksDataPlugin *>();


	for (int i = 0 ;i < mdp->allDatas().size(); ++i)
	{
		MarksData	*mark = qobject_cast<MarksData *>(mdp->allDatas().at(i));
		if (mark->student() == user->id())
		{
			for (int j = 0; j < edp->allDatas().size(); ++j)
			{

				ExamsData *tmp = qobject_cast<ExamsData *>(edp->allDatas().at(j));
				if (tmp->id() == mark->exam()->id())
				{
					mainWidget->insertRow(row);

					QTableWidgetItem *tmpitem;
					tmpitem = new QTableWidgetItem(tmp->subject()->name());
					mainWidget->setItem(row, 0, tmpitem);
					tmpitem = new QTableWidgetItem(tmp->date().toString());
					mainWidget->setItem(row, 1, tmpitem);
					tmpitem = new QTableWidgetItem(mark->result());
					mainWidget->setItem(row, 2, tmpitem);
					tmpitem = new QTableWidgetItem(mark->comment());
					mainWidget->setItem(row, 3, tmpitem);
					++row;
				}
			}
		}
	}
	mainWidget->setHorizontalHeaderLabels(labels);
	mainWidget->horizontalHeader()->setStretchLastSection(true);
	mainWidget->resizeColumnsToContents();
}
