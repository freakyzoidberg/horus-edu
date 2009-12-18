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
#include <QDragEnterEvent>
#include <QUrl>

LibraryEdit::LibraryEdit(PluginManager* pluginManager, FileData* file)
{
	_file = file;
	_pluginManager = pluginManager;

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

	line = new QLineEdit((_file?_file->name():""), this);
	_formLayout->addWidget(line, 1, 1);

	label = new QLabel(tr("Mime Type"), this);
	label->setProperty("isFormLabel", true);
	_formLayout->addWidget(label, 2, 0);

	line = new QLineEdit((_file?_file->mimeType():""), this);
	_formLayout->addWidget(line, 2, 1);

	label = new QLabel(tr("Key Words"), this);
	label->setProperty("isFormLabel", true);
	_formLayout->addWidget(label, 3, 0);

	text = new QTextEdit((_file?_file->keyWords():""), this);
	_formLayout->addWidget(text, 3, 1);



	label = new QLabel(tr("Visibility"), this);
	label->setProperty("isFormLabel", true);
	_formLayout->addWidget(label, 4, 0, 2, 1);

	_grades = new QComboBox(this);
	_grades->addItem(tr("Every Classes"), 0);
//	foreach (TreeData* node, treeDataPlugin->grades())
//		_grades->addItem(node->icon(), node->name(), node->id());
//	connect(_grades, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));
	_formLayout->addWidget(_grades, 4, 1);

	_subjects = new QComboBox(this);
	_subjects->addItem(tr("Every Subjects"));
//	_subjects->addItems(treeDataPlugin->subjects());
//	connect(_subjects, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxChanged(int)));
	_formLayout->addWidget(_subjects, 5, 1);




	label = new QLabel(tr("File path"), this);
	label->setProperty("isFormLabel", true);
	_formLayout->addWidget(label, 6, 0, 2, 1);

	label = new QLabel((_file?_file->fileName():""), this);
	_formLayout->addWidget(label, 6, 1);

	label = new QLabel(tr("You can drop a file here."), this);
	_formLayout->addWidget(label, 7, 1);

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

	if (_file)
	{
		button = new QPushButton(tr("Save"), this);
		connect(button, SIGNAL(clicked()), this, SLOT(save()));
	}
	else
	{
		button = new QPushButton(tr("Create"), this);
		connect(button, SIGNAL(clicked()), this, SLOT(create()));

	}
	rightLayout->addWidget(button);

	rightLayout->addWidget(new QWidget(this), 1);
}

void LibraryEdit::exit()
{
	emit exited();
}

void LibraryEdit::create()
{
//	_file = _pluginManager->findPlugin<FileDataPlugin*>()->createFile();
	emit exited();
}

void LibraryEdit::save()
{
	_file->setName(static_cast<QLineEdit*>(_formLayout->itemAtPosition(1, 1)->widget())->text());
	_file->setMimeType(static_cast<QLineEdit*>(_formLayout->itemAtPosition(2, 1)->widget())->text());
	_file->setKeyWords(static_cast<QTextEdit*>(_formLayout->itemAtPosition(3, 1)->widget())->document()->toPlainText());
	_file->save();
	emit exited();
}

void LibraryEdit::dragEnterEvent(QDragEnterEvent *event)
{
	if ( ! event->mimeData()->hasFormat(("text/uri-list")))
		return;
	if (event->mimeData()->urls().count() > 1)
		return;
	if ( ! QFile(event->mimeData()->urls().first().path()).exists())
		return;

	event->acceptProposedAction();
}

void LibraryEdit::dropEvent(QDropEvent* event)
{
	if ( ! event->mimeData()->hasFormat(("text/uri-list")))
		return;
	if (event->mimeData()->urls().count() > 1)
		return;
	if ( ! QFile(event->mimeData()->urls().first().path()).exists())
		return;

	TreeDataPlugin* treeDataPlugin = _pluginManager->findPlugin<TreeDataPlugin*>();
	TreeData* node = treeDataPlugin->node(_grades->itemData(_grades->currentIndex()).toUInt());
	QString subject = _subjects->currentText();

	if (node != treeDataPlugin->rootNode() && subject != tr("All"))
	{
		foreach (Data* data, treeDataPlugin->allDatas())
		{
			TreeData* n = static_cast<TreeData*>(data);
			if (n->isDescendantOf(node) && n->isInSubject(subject))
			{
				node = n;
				break;
			}
		}
	}

	FileData* file = _pluginManager->findPlugin<FileDataPlugin*>()->createFile(node, event->mimeData()->urls().first().path());

//	emit editFile(file);
	event->acceptProposedAction();
}
