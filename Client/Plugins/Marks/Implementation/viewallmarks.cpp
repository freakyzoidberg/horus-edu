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
	del = new QPushButton(QIcon(":/DelTimeTable.png"), tr("Supprimer la note"));
	edit = new QPushButton(QIcon(":/EditTimeTable.png"), tr("Voir les etudiants."));
	ok = new QPushButton(QIcon(":/ok.png"), tr("Ok"));
	save = new QPushButton(QIcon(":/save.png"), tr("Enregistrer"));
	reset = new QPushButton(QIcon(":/reset.png"), tr("Reset"));
	back = new QPushButton(QIcon(":/back.png"), tr("Annuler"));
	_add = new QPushButton(QIcon(":/AddTimeTable.png"), tr("Ajouter un examen"));

	RightLayout->addWidget(infos);
	RightLayout->addWidget(edit);
	RightLayout->addWidget(del);
	RightLayout->addWidget(ok);
	RightLayout->addWidget(save);
	RightLayout->addWidget(reset);
	RightLayout->addWidget(back);
	RightLayout->addWidget(_add);
	RightLayout->addWidget(new QWidget(), 1);
	MainLayout->addWidget(mainWidget);
	MainLayout->addLayout(RightLayout);
	MainLayout->setStretch(0, 1);

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
	initGradesList();
	this->setLayout(MainLayout);
}

void	ViewAllMarks::initGradesList()
{
	UserData		*user = _pluginManager->currentUser();
	ExamsDataPlugin	*edp = _pluginManager->findPlugin<ExamsDataPlugin *>();
	MarksDataPlugin	*mdp = _pluginManager->findPlugin<MarksDataPlugin *>();

	int row = 0;
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
	mainWidget->resizeColumnsToContents();
}
