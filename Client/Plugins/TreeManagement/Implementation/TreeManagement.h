#ifndef TREEMANAGEMENT_H
#define TREEMANAGEMENT_H

#include "TreeManagement_global.h"
#include "../../IClientPlugin.h"
#include "../../INetworkPlugin.h"
#include "../ITreePlugin.h"
#include "Tree.h"
#include "TreeModel.h"

class TREEMANAGEMENTSHARED_EXPORT TreeManagement : public IClientPlugin, public INetworkPlugin, public ITreePlugin
{
  Q_OBJECT
  Q_INTERFACES(IClientPlugin)
  Q_INTERFACES(INetworkPlugin)
  Q_INTERFACES(ITreePlugin)

public:
    TreeManagement();
    //! The name of the plugin
    /*!
     *  This method provide the name of the plugin.
     *  Each plugin must have an unique name.
     *  \return the name of the plugin
     */
    inline const QByteArray    getName() const { return "TreeManagement"; }
    //! The version of the plugin
    /*!
     *  This function provide the version of the plugin.
     *  The method is used in dependencies.
     *  \return the version of the plugin
     */
    inline const QByteArray    getVersion() const { return "0.1"; }
    //! The plugins conflicting with this plugin
    /*!
     *  This method provide a list of plugins which can't be loaded with this plugin
     *  \return The list of plugins
     */
    inline QStringList         getPluginsConflicts() const { return QStringList(); }
    //! The plugins required with this plugin
    /*!
     *  This method provide a list of plugins which must be loaded with this plugin
     *  \return The list of plugins
     */
    inline QStringList         getPluginsRequired() const { return QStringList(); }
    //! The plugins recommended with this plugin
    /*!
     *  This method provide a list of plugins which may be loaded with this plugin
     *  \return The list of plugins
     */
    inline QStringList         getPluginsRecommended() const { return QStringList(); }

    void recvPacket(const PluginPacket&);

    inline ITree* getNodeById(int id) { return Tree::getNodeById(id); }

    inline QAbstractItemModel* getTreeModel() { return new TreeModel(); }

    //! Surcharge of the method event
    /*!
     *  Each plugin must manage events that it will receive.
     *  \param event the event received
     *  \return the accept status of the event
     */
    bool                event(QEvent*);
};

#endif // TREEMANAGEMENT_H
