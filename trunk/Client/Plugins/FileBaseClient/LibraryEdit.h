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
	LibraryEdit(PluginManager* pluginManager, FileData* file = 0);
	LibraryEdit(PluginManager* pluginManager, const QString filename);

signals:
	void			exited();

public slots:
	void			exit();
	void			save();
	void			browse();
	void			dragEnterEvent(QDragEnterEvent *event);
	void			dropEvent(QDropEvent* event);
	void			gradeChanged(int);

private:
	void			init();
	PluginManager*	_pluginManager;
	FileData*		_file;
	bool			_creating;
	QGridLayout*	_formLayout;
	QComboBox*		_grades;
	QComboBox*		_subjects;
};

#endif // LIBRARYEDIT_H
