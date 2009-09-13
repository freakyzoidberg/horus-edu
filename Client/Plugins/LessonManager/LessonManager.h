#ifndef			__LESSONMANAGERMODULE_H__
# define		__LESSONMANAGERMODULE_H__

# include		<QObject>
# include		<QXmlStreamWriter>
# include		<QList>
# include		<QWidget>

# include		"../../../../Common/Plugin.h"
# include		"../../../../Common/FileDataPlugin.h"
# include		"../../../../Common/FileData.h"

# include               "ILessonManager.h"
# include               "LessonModel.h"

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
Q_INTERFACES(ILessonManager);

public:
        bool canLoad() const;
        void load();
        void unload();

public:
	const QString	pluginName() const ;
	const QString	pluginVersion() const ;

public:
        LessonModel     *getLessonModel();

private:
        LessonModel     *lessonModel;
};

#endif // __LESSONMANAGERTESTMODULE_H__
