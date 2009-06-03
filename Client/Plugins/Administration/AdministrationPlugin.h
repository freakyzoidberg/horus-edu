#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <QEvent>
#include <QtPlugin>
#include <QObject>
#include "../../INetworkPlugin.h"
#include "../../IClientPlugin.h"

class Administration : public IClientPlugin, public INetworkPlugin
{
    Q_OBJECT
    Q_INTERFACES(INetworkPlugin)
    Q_INTERFACES(IClientPlugin)
    public:
        Administration();
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

        void recvPacket(const PluginPacket&);
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

#endif // ADMINISTRATION_H
