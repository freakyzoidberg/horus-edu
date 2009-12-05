#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "ManageEdt.h"

ManageEdt::ManageEdt(PluginManager *pluginManager)
{
	MainLayout = new QHBoxLayout();
	MainLayout->setSpacing(0);
	MainLayout->setMargin(2);

	QVBoxLayout *RightLayout = new QVBoxLayout();
	RightLayout->setSpacing(2);
	MainLayout->addWidget(new QWidget());

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

	RightLayout->addWidget(actionTitle);
	RightLayout->addWidget(new QWidget(this), 1);
	MainLayout->addLayout(RightLayout);
	//MainLayout->setColumnMinimumWidth(0,150);
	MainLayout->setStretch(0, 1);
	this->setLayout(MainLayout);
}
