#ifndef TESTMODULE_H
#define TESTMODULE_H

#include <QObject>
#include <QEvent>
#include <QStringList>

#include "../../IClientPlugin.h"
#include "../../INetworkPlugin.h"

#include "PluginNetwork.h"

//!  Test plugin
/*!
  This plugin wwas written to show how to write Horus plugins.
  It does nothing, just implement the different interfaces of
  Horus API. All the plugins must implement the API.

  The .pro file used to compile the plugin testPlugin is:
    TEMPLATE = lib
    SOURCES +=  testmodule.cpp \
                PluginNetwork.cpp
    HEADERS +=  testmodule.h \
                PluginNetwork.h
    INCLUDEPATH  += .
    DESTDIR = .
    TARGET = $$qtLibraryTarget(testModule)
  This is the basic. You must adapt it in function of your need.

  Furthermore, one of the .ccp files of your plugin must contain the macro
  Q_EXPORT_PLUGIN2(testModule, testPlugin)
  In that case, "testModule" is the name of the library created by the compilation
  and "testPlugin" the name of the class implementing the interface
  IClientPlugin.

  The class testPlugin inheritates from IClientPlugin, an interface from Horus API.
*/


class testPlugin : public IClientPlugin
{
 //! The Q_OBJECT and Q_INTERFACES macros
 /*! This two macros must be called to compile the plugin properly.
    The second one take the name of the interface ICLientPlugin
    in parameters.
 */

 Q_OBJECT
 Q_INTERFACES(IClientPlugin)

public:
    //! The constructor.
    /*
      The constructor set the mod* (modRequired, modName, etc) and the exports
      member variables of the plugin.

      It also instanciate the member variable of type PluginNetwork (member variable pNetwork)
      (see IPluginNetwork.h from the API and PluginNetwork.h from
        the plugin for more precision).
    */
    testPlugin();

    //! The destructor
    /*
        It frees the member variable pNetwork.
    */
    ~testPlugin();

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

    //! Network access
    /*!
       Pointer to a PluginNetwork object, used to send packet through the network
    */
    PluginNetwork       *pNetwork;;
};


#endif // TESTMODULE_H
