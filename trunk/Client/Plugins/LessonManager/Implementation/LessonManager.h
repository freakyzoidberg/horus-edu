#ifndef			__LESSONMANAGERMODULE_H__
# define		__LESSONMANAGERMODULE_H__

# include		<QObject>
# include		<QXmlStreamWriter>
# include		<QList>
# include		<QWidget>

# include		"../../../../Common/Plugin.h"
# include		"../../../../Common/FileDataPlugin.h"
# include		"../../../../Common/FileData.h"

# include		"ILessonManager.h"

//! LessonManager plugin
/*!

*/
class			LessonManager : public Plugin, public ILessonManager
{
//! The Q_OBJECT and Q_INTERFACES macros
/*! This two macros must be called to compile the plugin properly.
 * The second one take the name of the interface ICLientPlugin
 * in parameters.
 */
Q_OBJECT
Q_INTERFACES(Plugin)
Q_INTERFACES(ILessonManager)

public:
	const QString	pluginName() const ;
	const QString	pluginVersion() const ;

public:
	ILesson*	getLesson(quint32 fileId);
	void		saveLesson(quint32 fileId, ILesson *lesson);
	ILesson*	createNewLesson(quint32 fileId);
	void		displayPage(ILesson::IPage *page, QWidget *widget);
	void		hidePage(ILesson::IPage *page);

private:
	void		writeXmlSection(const QList<ILesson::IElement *> &list, QXmlStreamWriter &xmlWriter);

private:
	QMap<ILesson::IPage *, QWidget *>  displayedPages;
	//QMap<QString, QString>  availableControllers;
	//QMap<QString, ILesson::IElement::>
	FileData *file;
	ILesson::IPage *page;
	QWidget *widget;

private slots:
	void readyDisplayPage();
};

#endif // __LESSONMANAGERTESTMODULE_H__
