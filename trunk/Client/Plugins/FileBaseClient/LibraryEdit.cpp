#include "LibraryEdit.h"
#include "../../../Common/FileData.h"
#include "../../../Common/TreeData.h"
#include <QPushButton>
#include <QFormLayout>
#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

LibraryEdit::LibraryEdit(PluginManager* pluginManager, FileData* file)
{
	_file = file;
	_creating = false;
	if ( ! _file)
	{
		_creating = true;
		_file = pluginManager->findPlugin<FileDataPlugin*>()->createFile(pluginManager->findPlugin<TreeDataPlugin*>()->rootNode());
	}

	QLabel* label;
	QLineEdit* line;
	QTextEdit* text;
	QPushButton* button;

	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setSpacing(0);
	layout->setMargin(0);


	QFrame* formFrame = new QFrame();
	formFrame->setProperty("isFormFrame", true);
	layout->addWidget(formFrame, 1);
	_formLayout = new QGridLayout(formFrame);
	_formLayout->setRowStretch(10, 10);


	label = new QLabel(tr("Personnal informations"), this);
	label->setProperty("isFormTitle", true);
	_formLayout->addWidget(label, 0, 0, 1, 2);

	label = new QLabel(tr("Name"), this);
	label->setProperty("isFormLabel", true);
	_formLayout->addWidget(label, 1, 0);

	line = new QLineEdit(_file->name(), this);
	_formLayout->addWidget(line, 1, 1);

	label = new QLabel(tr("Mime Type"), this);
	label->setProperty("isFormLabel", true);
	_formLayout->addWidget(label, 2, 0);

	line = new QLineEdit(_file->mimeType(), this);
	_formLayout->addWidget(line, 2, 1);

	label = new QLabel(tr("Key Words"), this);
	label->setProperty("isFormLabel", true);
	_formLayout->addWidget(label, 3, 0);

	text = new QTextEdit(_file->keyWords(), this);
	_formLayout->addWidget(text, 3, 1);


	QVBoxLayout* rightLayout = new QVBoxLayout;
	layout->addLayout(rightLayout);

	label = new QLabel(tr("Actions:"), this);
	label->setProperty("isTitle", true);
	label->setProperty("isRound", true);
	label->setMinimumWidth(200);
	rightLayout->addWidget(label);

	button = new QPushButton(tr("Return"), this);
	connect(button, SIGNAL(clicked()), this, SLOT(exit()));
	rightLayout->addWidget(button);

	button = new QPushButton(tr((_creating ? "Create" : "Save")), this);
	connect(button, SIGNAL(clicked()), this, SLOT(save()));
	rightLayout->addWidget(button);

	rightLayout->addWidget(new QWidget(this), 1);
}

void LibraryEdit::exit()
{
	emit exited();
}

void LibraryEdit::save()
{
	_file->setName(static_cast<QLineEdit*>(_formLayout->itemAtPosition(1, 1)->widget())->text());
	_file->setMimeType(static_cast<QLineEdit*>(_formLayout->itemAtPosition(2, 1)->widget())->text());
	_file->setKeyWords(static_cast<QTextEdit*>(_formLayout->itemAtPosition(3, 1)->widget())->document()->toPlainText());


	if (_creating)
		_file->create();
	else
		_file->save();
	emit exited();
}
