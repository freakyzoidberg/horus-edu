#ifndef LIBRARYEDIT_H
#define LIBRARYEDIT_H

#include <QWidget>
class PluginManager;
class FileData;
class QGridLayout;

class LibraryEdit : public QWidget
{
Q_OBJECT
public:
	explicit LibraryEdit(PluginManager* pluginManager, FileData* file);

signals:
	void		exited();

public slots:
	void		exit();
	void		save();
private:
	FileData*	_file;
	bool		_creating;
	QGridLayout*_formLayout;
};

#endif // LIBRARYEDIT_H
