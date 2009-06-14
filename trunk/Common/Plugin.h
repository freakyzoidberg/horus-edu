#ifndef PLUGIN_H
#define PLUGIN_H

class Plugin : public QObject
{
public:
    //! The name of the plugin
    /*!
     *  This method provide the name of the plugin.
     *  Each plugin must have an unique name.
     *  \return the name of the plugin
     */
    virtual const QString             pluginName() const = 0;
    //! The version of the plugin
    /*!
     *  This function provide the version of the plugin.
     *  The method is used in dependencies.
     *  \return the version of the plugin
     */
    virtual const QString             pluginVersion() const = 0;
    //! The plugins conflicting with this plugin
    /*!
     *  This method provide a list of plugins which can't be loaded with this plugin
     *  \return The list of plugins
     */
    virtual inline const QStringList  pluginsConflict() const { return QStringList(); }
    //! The plugins required with this plugin
    /*!
     *  This method provide a list of plugins which must be loaded with this plugin
     *  \return The list of plugins
     */
    virtual inline const QStringList  pluginsRequired() const { return QStringList(); }
    //! The plugins recommended with this plugin
    /*!
     *  This method provide a list of plugins which may be loaded with this plugin
     *  \return The list of plugins
     */
    virtual inline const QStringList  pluginsRecommended() const { return QStringList(); }
    //! Overload of the event() method.
    /*!
     *  Each plugin can manage events that it will receive.
     *  \param event the event received
     *  \return the accept status of the event
     */
    virtual inline bool              event(QEvent*) { return false; }
    //! A function for accessing to another plugin
    /*!
     *  This function return the instance of plugin from his name.
     *  A plugin can only be instancieted once, so each name is unique.
     *  It is destinated for plugins willing to contacts other plugins
     *  \param name the name of the desired plugin
     *  \return a pointer to the instance of the desired plugin or NULL if not found
     */
    Plugin*                          findPlugin(const QString name) const;
};

Q_DECLARE_INTERFACE(Plugin, "net.horus.Plugin/1.0");

#endif // PLUGIN_H
