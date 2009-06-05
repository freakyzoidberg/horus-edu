#ifndef LESSONMANAGERMODULE_H
#define LESSONMANAGERMODULE_H

#include <QObject>
#include <QEvent>
#include <QStringList>
#include <QtXml/QXmlStreamWriter>
#include <QList>

#include "../../IClientPlugin.h"
#include "../../IFilePlugin.h"
#include "ILessonManager.h"

//!  LessonManager plugin
/*!

*/
class LessonManager : public IClientPlugin, public IFilePlugin, public ILessonManager
{
 //! The Q_OBJECT and Q_INTERFACES macros
 /*! This two macros must be called to compile the plugin properly.
    The second one take the name of the interface ICLientPlugin
    in parameters.
 */

 Q_OBJECT
 Q_INTERFACES(IClientPlugin)
 Q_INTERFACES(IFilePlugin)
 Q_INTERFACES(ILessonManager)

public:
    //! The constructor.
    /*!
      The constructor set the mod* (modRequired, modName, etc) and the exports
      member variables of the plugin.

      It also instanciate the member variable of type PluginNetwork (member variable pNetwork)
      (see IPluginNetwork.h from the API and PluginNetwork.h from
        the plugin for more precision).
    */
    LessonManager();

    //! The destructor
    /*!
        It frees the member variable pNetwork.
    */
    ~LessonManager();

public:
    //! Set the private member variable modName.
    /*!
      \param name the name of the plugin.
    */
     void setModName(const QByteArray name);

     //! Set the private member variable modVersion.
    /*!
      \param version the version of the plugin.
    */
     void setModVersion(const QByteArray version);

     //! Set the private member variable modConflicts.
    /*!
      \param conflicts conflicts between different plugins version.
    */
     void setModConflicts(const QString conflicts);

     //! Set the private member variable modRequiered.
    /*!
      \param modRequiered : plugins requiered to use this plugin
    */
     void setModRequired(const QString modRequiered);

     //! Set the private member variable modRecommended.
    /*!
      \param modRecommended : plugins recommended to use this plugin
    */
     void setModRecommended(const QString modRecommended);

     //! Set the private member variable exports.
    /*!
      \param exports : the exports
    */
     void setExports(const QString exports);

  public:
     //! return the name of the plugin
     /*!
        \return the variable modName
     */
     const QByteArray       getName() const;

     //! return the version of the plugin
     /*!
       \return the variable modVersion
     */
     const QByteArray       getVersion() const;

    //! return the conflicst between the plugins
     /*!
        \return the variable modConflicts
     */
     QStringList            getPluginsConflicts() const;

     //!return the list of the requiered plugins to use this one
     /*!
       \return the variable modRequiered
     */
     QStringList            getPluginsRequired() const;

     //!return the list of the recommended plugin to use this one
     /*!
       \return the variable modRecommended
     */
     QStringList            getPluginsRecommended() const;

     //!return the list of the xports
     /*!
       \return the variable exports
     */
     QStringList            getExports() const;

     //! overload of the method event from the class QEvent
    /*!
        \param event the event received by the plugin
        \return a boolean indicating if the event was successefully handled (true)
    */
    bool                    event(QEvent * event);

    //! method if the plugin received a LoadPluginEvent
    /*!
      \param event the event received by the plugin
      \return a boolean indicating if the event was successefully handled (true)
    */
    bool                    eventHandlerLoad(QEvent *event);

    //! method if the plugin received a UnoadPluginEvent
    /*!
      \param event the event received by the plugin
      \return a boolean indicating if the event was successefully handled (true)
    */
    bool                    eventHandlerUnload(QEvent *event);



    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/



    ILesson*    getLesson(quint32 fileId);
    void        saveLesson(quint32 fileId, ILesson *lesson);
    ILesson*    createNewLesson(quint32 fileId);

    void        displayPage(ILesson::IPage *page, QWidget *widget);
    void        hideCurrentPage();

 private:
    void        writeXmlSection(const QList<ILesson::IElement *>& list, QXmlStreamWriter& xmlWriter);

 private:
    //QMap<QString, >

 private:
    //! the name of the plugin
    QByteArray          modName;

    //! the version of the plugin
    QByteArray          modVersion;

    //! conflicts between plugins
    /*!
      The list contains the name of the plugin which are in conflicts
      with this one.
    */
    QStringList         modConflicts;

    //! plugin requiered
    /*!
      The list contains the name of the plugins required to use this one
    */
    QStringList         modRequired;

    //! plugin recommended
    /*!
      The list contains the name of the recommended plugins to use this one
    */
    QStringList         modRecommended;

    //! exports
    /*!
      The list contains the name of the exports
    */
    QStringList         exports;
};


#endif // LESSONMANAGERTESTMODULE_H
