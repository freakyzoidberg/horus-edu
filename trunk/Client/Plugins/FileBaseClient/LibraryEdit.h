#ifndef LIBRARYEDIT_H
#define LIBRARYEDIT_H

#include <QWidget>
class PluginManager;
class FileData;
class QGridLayout;
class QComboBox;

class LibraryEdit : public QWidget
{
Q_OBJECT
public:
	explicit LibraryEdit(PluginManager* pluginManager, FileData* file);

signals:
	void			exited();

public slots:
	void			exit();
	void			save();
	void			create();
	void			dragEnterEvent(QDragEnterEvent *event);
	void			dropEvent(QDropEvent* event);

private:
	PluginManager*	_pluginManager;
	FileData*		_file;
	bool			_creating;
	QGridLayout*	_formLayout;
	QComboBox*		_grades;
	QComboBox*		_subjects;
};

#endif // LIBRARYEDIT_H
